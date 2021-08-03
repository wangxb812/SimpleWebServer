#pragma once
#include "header.h"
class threadPool
{
public:
    threadPool(connection_pool *connnPool,int threadNum=8,int maxRequest = 10000);
    ~threadPool();
    bool append(T* request);
private:
    static void* worker(void* arg);
    void run();

    int m_thread_number;
    int m_max_requests;
    pthread_t* m_threads;
    std::list<T*> m_workqueue;

    locker m_queuelocker;
    sem m_queuestat;

    bool m_stop;
    connection_pool* m_connPool;
};
//线程池构造函数
template<typename T>
threadPool<T>::threadPool(connection_pool* connPool, int thread_number,int max_request):
    m_thread_number(thread_number),m_max_requests(max_request),m_stop(false),m_threads(NULL),m_connPool(connPool)
{
    if (thread_number <= 0 || max_request <= 0)
    {
        throw std::expection();
    }
    m_threads = new pthread_t[m_thread_number];
    if (!m_threads)  throw std::expection();
    for (int i = 0; i < thread_number; i++)
    {
        if (pthread_create(m_threads + i, NULL, worker, this) != 0)
        {
            delete[] m_threads;
            throw exception();
        }
        if (pthread_detach(m_threads[i))
        {
            delete[] m_threads;
            throw exception();
        }
    }
}
template<typename T>
threadPool<T>::!threadPool()
{
    delete[]m_threads;
    m_stop = true;
}
