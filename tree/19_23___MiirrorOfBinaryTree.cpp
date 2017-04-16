/**********************************************
 > File Name: 19_MiirrorOfBinaryTree.cpp
 > Author: ZY
 > Created Time: 2017年03月27日 星期一 10时50分58秒
*******************************************/


#include<iostream>
#include<deque>
#include<stdio.h>

using namespace std;


struct BinaryTreeNode
{
	int  m_nValue;
	BinaryTreeNode*  m_pLeft;
	BinaryTreeNode*  m_pRight;
};

//前序遍历递归
void preorder(BinaryTreeNode *T)
{
	if(T == NULL)
		return;
	cout<<T->m_nValue<<endl;
	preorder(T);
}


//19 二叉树的镜像
void MirrorOfBinaryTree(BinaryTreeNode *pNode)
{
	if(pNode ==NULL)
		return ;
	if(pNode->m_pLeft == NULL  &&  pNode->m_pRight == NULL)
		return;
	/*上面全是边界情况*/

	//交换左右子树
	BinaryTreeNode *pTemp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = pTemp;

	//左递归
	if(pNode->m_pLeft)
		MirrorOfBinaryTree(pNode->m_pLeft);
	//右递归
	if(pNode->m_pRight)
		MirrorOfBinaryTree(pNode->m_pRight);

}

//23 从上往下打印二叉树   即层序遍历
void PrinttFromTopToBottom(BinaryTreeNode* pTreeRoot) 
{
	if(pTreeRoot == NULL)
		return ;
	
   deque<BinaryTreeNode *> dequeTreeNode;//创建一个双端口队列容器 里面放二叉树节点

	dequeTreeNode.push_back(pTreeRoot); //从队列后面 放入根部节点

	//层序遍列
	while(dequeTreeNode.size())
	{
		BinaryTreeNode *pNode = dequeTreeNode.front();
		dequeTreeNode.pop_front();

		printf("%d", pNode->m_nValue);
		
		if(pNode->m_pLeft)
			dequeTreeNode.push_back(pNode->m_pLeft);
	
		if(pNode->m_pRight)
			dequeTreeNode.push_back(pNode->m_pRight);
	
	}

}


//24  二叉搜索树的后序便列
//  用来判断一个数组中的数字 是不是按照 后序遍历的如果是 true 不是false
bool VerifSquenceOfBST(int sequence[], int length)
{
	//对数组进行有效性判断
	if(sequence == NULL ||  length <=0)
		return false;
	
	int root = sequence[length-1];//后续便列则最后的一个元素必为根

	//在二叉搜索树中 左子节点小于根节点
	int i = 0;
	for(;i<length-1; i++)
	{
		if(sequence[i] > root)
			break;
	}

	//在二叉收缩树中 右子节点大于根部节点
	int j = i;
	for(;j<length-1; j++)
	{
		if(sequence[j] < root)
			return false;
	}

	//递归调用咯 (判断左子树咯) 是不是二差收缩树了
	bool left = ture;
	if(i>0)
		left = VerifSquenceOfBST(sequence,i);//注意参数变化 

	//同上
	bool right= true;
	if(i < length -1)
		right = VerifSquenceOfBST(sequence +i, length-i-1);

	return(left && right);

}





