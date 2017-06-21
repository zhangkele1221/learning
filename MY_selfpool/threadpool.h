/*************************************************************************
    > File Name: threadpool.h
    > Author: ZY
    > Created Time: 2017年06月20日 星期二 15时14分49秒
 ************************************************************************/

#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#ifdef  __cplusplus
/*对于 c++ 编译器  指定用c的语法编译 */
extern "C"{
#endif

#define MAX_THREADS  64
#define MAX_QUEUE    65536


/*简化变量的定义 */
typedef struct threadpool_t   threadpool_t;

typedef struct {
    void (*function)(void *);
    void *argument;
} threadpool_task_t;


struct threadpool_t {
  pthread_mutex_t lock;
  pthread_cond_t notify;
  pthread_t *threads;
  threadpool_task_t *queue;
  int thread_count;
  int queue_size;
  int head;
  int tail;
  int count;
  int shutdown;
  int started;
};

/*定义错误码*/
typedef enum {
	threadpool_invalid			= -1,
	threadpool_lock_failure		= -2,
	threadpool_queue_full		= -3,
	threadpool_shutdown			= -4,
	threadpool_thread_failure	= -5
} threadpool_error_t;


typedef enum {
	threadpool_graceful	= 1
} threadpool_destroy_flags_t;

/* 以下是线程池三个对外 API */

//创建线程池，有thread_count 个线程，容纳 queue_size 个的任务队列，flags 参数没有使用
threadpool_t *threadpool_create(int thread_count,int queue_size,int flags);

//添加任务到线程池, pool 为线程池指针 routine 为函数指针，arg 为函数参数 flags 未使用
int threadpool_add(threadpool_t *pool,void (*routine)(void*),void *arg,int flags);

//销毁线程池  flags可以用来知道那个关闭的方式
int threadpool_destroy(threadpool_t*pool,int flags);


#ifdef __cplusplus
}
#endif


#endif  /*_THREADPOOL_H_*/
















