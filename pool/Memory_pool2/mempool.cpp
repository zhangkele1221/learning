/*************************************************************************
    > File Name: mempool.cpp
    > Author: ZY
    > Created Time: 2017年05月02日 星期二 21时53分53秒
 ************************************************************************/

#include<iostream>

using namespace std;

//模板参数ObjectSize代表实际申请的对象的大小  NumofObjects代表每个内存快能容纳对象个数
template<int ObjectSize,int NumofObjects=20>
class  MemPool{
private:
	const int MemBlockSize;//每个内存快的大小
	const int ItemSize;//每个内存节点的大小
	struct _FreeNode{
		_FreeNode*pNext;
		char data[ObjectSize];
	};
	struct _MemBlock{
		_MemBlock*pNext;
		_FreeNode data[NumofObjects];
	};
	_MemBlock* pMemBlockHeader;
	_FreeNode* pFreeNodeHeader;
public:
	MemPool():ItemSize(ObjectSize+sizeof(_FreeNode*)),
		MemBlockSize(sizeof(_MemBlock*)+NumofObjects*(ObjectSize+sizeof(_FreeNode*))){
		pMemBlockHeader=NULL;
		pFreeNodeHeader=NULL;
	}

	~MemPool(){
		_MemBlock *ptr;
		while(pMemBlockHeader){
			ptr=pMemBlockHeader->pNext;
			delete pMemBlockHeader;
			pMemBlockHeader = ptr;
		}
	}
	void* malloc();
	void free(void*);
};

template <int ObjectSize,int NumofObjects>
void* MemPool<ObjectSize,NumofObjects>::malloc(){ //没有参数
	if(pFreeNodeHeader==NULL){
		_MemBlock*pNewBlock=new _MemBlock;
		pNewBlock->data[0].pNext=NULL;
		for(int i =1;i<NumofObjects;i++)   //连续分配FreeNoode节点
			pNewBlock->data[i].pNext=&pNewBlock->data[i-1];
		pFreeNodeHeader=&pNewBlock->data[NumofObjects-1];//最后分配的节点当头节点
		pNewBlock->pNext=pMemBlockHeader;//块节点指针 向后排列
		pMemBlockHeader=pNewBlock;
	}
	void *pFreeNode = pFreeNodeHeader;
	pFreeNodeHeader = pFreeNodeHeader->pNext;//向下移动遍历
	return  pFreeNode;
}

template <int ObjectSize,int NumofObjects>
void MemPool<ObjectSize,NumofObjects>::free(void *p){
	_FreeNode* pNode=(_FreeNode*)p;
	pNode->pNext= pFreeNodeHeader;
	pFreeNodeHeader=pNode;
}




class ActualClass{
	static int count;
	int num[10];
public:
	ActualClass(){
		count++;
		for(int i=0;i<10;i++)
			num[i]=count+i;
	}
	void show(){
		cout<<this<<":";
		for(int i=0;i<10;i++){
			cout<<num[i]<<" ";
		}
		cout<<endl;
	}

void* operator new(size_t size);
void operator delete(void *p);

};

class theMemoryPool{
	static MemPool<sizeof(ActualClass),2 > mp;
	friend class ActualClass;
};

void *ActualClass::operator new(size_t size){
	return theMemoryPool::mp.malloc();
}

void ActualClass::operator delete(void*p){
	theMemoryPool::mp.free(p);
}

MemPool<sizeof(ActualClass),2> theMemoryPool::mp;
int ActualClass::count;

int main(){
	ActualClass *p1 = new ActualClass;
	p1->show();
	ActualClass *p2 = new ActualClass;
	p2->show();
	delete p1;
	p1 = new ActualClass;
	p1->show();
	ActualClass *p3 = new ActualClass;
	p3->show();
	delete p1;
	delete p2;
	delete p3;
}



