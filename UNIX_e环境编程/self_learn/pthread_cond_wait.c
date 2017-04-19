/*************************************************************************
    > File Name: pthread_cond_wait.cpp
    > Author: ZY
    > Created Time: 2017年04月19日 星期三 10时01分42秒
 ************************************************************************/

/*
条件变量是利用线程间共享的全局变量进行同步的一种机制，
主要包括两个动作：
一个线程等待"条件变量的条件成立"而挂起；
另一个线程使"条件成立"（给出条件成立信号）。
为了防止竞争，条件变量的使用总是和一个互斥锁结合在一起
*/


#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/*初始化互斥锁*/
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;//init cond

void *thread1(void*);
void *thread2(void*);

int i = 1; //global

int main(void){
    pthread_t t_a;
    pthread_t t_b;//two thread

    pthread_create(&t_a,NULL,thread2,(void*)NULL);
    pthread_create(&t_b,NULL,thread1,(void*)NULL);//Create thread

    pthread_join(t_b,NULL);//wait a_b thread end
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
   exit(0);
}

void *thread1(void *junk){
    for(i = 1;i<= 9; i++){
        pthread_mutex_lock(&mutex); //互斥锁
        printf("call thread1 \n");
        if(i%5 == 0)
            pthread_cond_signal(&cond); //send sianal to t_b
        else
            printf("thread1: %d\n",i);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void *thread2(void*junk){
    while(i < 9)
    {
        pthread_mutex_lock(&mutex);
        printf("call thread2 \n");
           // if(i%5 != 0)//开始条件为真  进入pthread_cond_wait 挂起!!!!!!!! 
				pthread_cond_wait(&cond,&mutex); //wait
        printf("thread2  waiting  ok  .......: %d\n",i);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}














