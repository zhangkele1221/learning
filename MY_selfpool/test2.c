/*************************************************************************
    > File Name: test2.c
    > Author: ZY
    > Created Time: 2017年06月21日 星期三 09时35分43秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include "threadpool.h"

#define THREAD 4
#define SIZE   8192

threadpool_t *pool;
int left;
pthread_mutex_t lock;

int error;

void dummy_task(void *arg) {
    usleep(100);
    pthread_mutex_lock(&lock);
    left--;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
    int i;

    pthread_mutex_init(&lock, NULL);

    /* Testing immediate shutdown */
	//即立刻关闭线程池   不管里面的任务队列还有没有未完成的任务 立刻关闭   看left
    left = SIZE;
    pool = threadpool_create(THREAD, SIZE, 0);
    for(i = 0; i < SIZE; i++) {
        assert(threadpool_add(pool, &dummy_task, NULL, 0) == 0);
    }
    assert(threadpool_destroy(pool, 0) == 0);
	//自己添加一个打印测试 看看线程池的任务队列里面还有多少任务未完成
	printf("%d tasks lasted is no finishing\n",pool->count);
    assert(left > 0);

    /* Testing graceful shutdown */
	//即优雅的关闭线程池   一定要等到线程池里面的任务队列完成已经有的任务 完成后关闭 看left
    left = SIZE;
    pool = threadpool_create(THREAD, SIZE, 0);
    for(i = 0; i < SIZE; i++) {
        assert(threadpool_add(pool, &dummy_task, NULL, 0) == 0);
    }
    assert(threadpool_destroy(pool, threadpool_graceful) == 0);
	//自己添加一个打印测试 看看线程池的任务队列里面还有多少任务未完成
	printf("%d tasks lasted is no finishing\n",pool->count);
    assert(left == 0);

    pthread_mutex_destroy(&lock);

    return 0;
}



















