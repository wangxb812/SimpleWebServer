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
};

