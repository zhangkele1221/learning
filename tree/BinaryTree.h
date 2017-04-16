/**********************************************
 > File Name: BinaryTree.h
 > Author: ZY
 > Created Time: 2017年03月27日 星期一 11时14分47秒
*******************************************/


#include<iostream>
using namespace std;

typedef struct node
{
	char data;
	struct node* leftchild;
	struct node* rightchild;
}BiTreeNode,*BiTree;

//前序遍列递归
void  Preorder(BiTree T)
{
	if(T==NULL)
		return ;
	cout<<T->data<<endl;
	Preorder(T->leftchild);
	Preorder(T->rightchild);
}

//前序创建二叉树 也要前序输入
void CreatBiTree(BiTree &T)
{
	char c;
	cin>>c;
	if('#'==c)
		T=NULL;
	else
	{
		T=new BiTreeNode;
		T->data = c;
		CreatBiTree(T->leftchild);
		CreatBiTree(T->rightchild);
	}

}

















