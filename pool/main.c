/**********************************************
 > File Name: main.c
 > Author: ZY
 > Created Time: 2017年04月07日 星期五 21时39分30秒
*******************************************/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"thread_pool.h"


void *mytask(void *arg)
{
  printf("thread 0x%0x is working on task %d\n",(int)pthread_self(),*(int*)arg);
  sleep(1);
  free(arg);
  return NULL;
}

int main(void)
{
	threadpool_t pool;
	threadpool_init(&pool,3);

	int i;
	for(i=0; i<10;i++)
	{	
		int *arg = (int*)malloc(sizeof(int));
		*arg = i;
		threadpool_add_task(&pool,mytask, arg);
	}
	sleep(15);  //最后要注释这一行  休眠为了帮助调试这里
	threadpool_destroy(&pool);
	
	return 0;
}

