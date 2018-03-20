#include<stdio.h>
#include<stdlib.h>
struct TreeNode{
	int val;
	struct TreeNode * left;
	struct TreeNode * right;
	struct TreeNode * next;
	struct TreeNode * up;
	int balance;
};

struct Tree{
	struct TreeNode * root;
};

void treePrintNode(struct TreeNode * cur);
void treeAdd(struct Tree * tree,int n);
struct TreeNode * TreeParent(struct TreeNode * cur,int x);
struct TreeNode * Search(struct TreeNode * cur,int x);
void TreePrnL2R(struct TreeNode * cur,int x);
void treeNext(struct TreeNode * cur);
void PrnBeautiful(struct TreeNode * cur);

int main(){
	struct Tree tree;
	struct TreeNode * mem = NULL;
	FILE * f;
	char fname[]="test.txt";
	int n,x;
	tree.root = NULL;
	f=fopen(fname,"r");
	while(fscanf(f,"%d",&n)==1){
		treeAdd(&tree,n);
	}
	/* treePrintNode(tree.root);
	scanf("%d",&n);
	mem=TreeParent(tree.root,n);
	if(mem!=NULL){printf("<%d>\n",mem->val);}
	printf("\n");
	scanf("%d",&x);
	printf("\n");
	TreePrnL2R(tree.root,x); */
	treeNext(tree.root);
	PrnBeautiful(tree.root);
	
}

//указатель на родителя
void treeAdd(struct Tree * tree,int n){
	struct TreeNode * cur = tree->root;
	struct TreeNode ** curAddr = &tree->root;
	struct TreeNode * node = malloc(sizeof(struct TreeNode));
	node->left = NULL;
	node->right = NULL;
	node->up = NULL;
	node->val = n;
	while(cur!=NULL){
		if(cur->val<=n){
			//right
			curAddr=&cur->right;
			node->up=cur;
			cur=cur->right;
		}
		else{
			//left
			curAddr=&cur->left;
			node->up=cur;
			cur=cur->left;
		}
	}
	*curAddr=node;
}

//печать дерева
void treePrintNode(struct TreeNode * cur){
	if(cur==NULL){
		return;
	}
	treePrintNode(cur->left);
	printf("%d",cur->val);
	if(cur->up!=0){printf(" <- %2d\n",cur->up->val);}
	else{printf("\n");}
	treePrintNode(cur->right);
	return;
}

//печать дерева в виде дерева
void PrnBeautiful(struct TreeNode * root){
	struct TreeNode * tmp;
	struct TreeNode * cur;
	int n=0,max=0,i;
	cur=root;
	if(cur==NULL){
		return;
	}
	while(cur!=NULL){
		tmp=cur;
		while(tmp!=NULL){
			printf("%02d ",tmp->val);
			tmp=tmp->next;
		}
		printf("\n");
		while(n==0){
			if(cur->left!=NULL){
				cur=cur->left;
				n++;
			}
			else if(cur->right!=NULL){
				cur=cur->right;
				n++;
			}
			else{
				cur=cur->next;
				if(cur==NULL){n++;}
			}
		}
		n=0;
		max++;
	}
	printf("%d\n",max);
	
	cur=root;
	while(cur!=NULL){
		tmp=cur;
		for(i=0;i<=max;i++){
				printf("  ");
			}
		max--;
		while(tmp!=NULL){
			printf("%02d  ",tmp->val);
			tmp=tmp->next;
		}
		printf("\n");
		while(n==0){
			if(cur->left!=NULL){
				cur=cur->left;
				n++;
			}
			else if(cur->right!=NULL){
				cur=cur->right;
				n++;
			}
			else{
				cur=cur->next;
				if(cur==NULL){n++;}
			}
		}
		n=0;
	}
	return;
}

//настройка указателей на следующий в уровне
void treeNext(struct TreeNode * cur){
	while(cur!=NULL){
		struct TreeNode * tmp=cur;
		struct TreeNode * prev=NULL;
		while(tmp!=NULL){
			if(tmp->left!=NULL){
				if(prev!=NULL){prev->next=tmp->left;}
				prev=tmp->left;
			}
			if(tmp->right!=NULL){
				if(prev!=NULL){prev->next=tmp->right;}
				prev=tmp->right;
			}
			tmp=tmp->next;
		}
		if(cur->left!=NULL){cur=cur->left;}
		else if(cur->right!=NULL){cur=cur->right;}
		else{cur=cur->next;}
	}
}

//поиск родителя
struct TreeNode * TreeParent(struct TreeNode * cur,int x){
	if((cur==NULL)||(x==cur->val)){
		return NULL;
	}
	while((cur!=NULL)&&(cur->val!=x)){
		if(x>=cur->val){
			cur=cur->right;
		}
		else{
			cur=cur->left;
		}
	}
	if(cur!=NULL){return cur->up;}
	else{return NULL;}
}

//поиск
struct TreeNode * Search(struct TreeNode * cur,int x){
	if((cur==NULL)||(x==cur->val)){
		return NULL;
	}
	while((cur!=NULL)&&(cur->val!=x)){
		if(x>=cur->val){
			cur=cur->right;
		}
		else{
			cur=cur->left;
		}
	}
	if(cur!=NULL){return cur;}
	else{return NULL;}
}

//печать ветки с выбранного листа
void TreePrnL2R(struct TreeNode * cur,int x){
	struct TreeNode * tmp;
	if(cur==NULL){return;}
	tmp=Search(cur,x);
	if(tmp!=NULL){
		while(tmp!=cur){
			printf("%d\n",tmp->val);
			tmp=tmp->up;
		}
		printf("%d\n",tmp->val);
	}
}