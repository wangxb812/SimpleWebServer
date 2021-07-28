#include "header.h"
#include <semaphore.h>
#include <exception>
//�ź���
class sem
{
public:
	sem()
	{
		if (sem_init(&m_sem, 0, 0) != 0)
		{
			throw exception();
		}
	}
	~sem()
	{
		sem_destroy(&m_sem);
	}
	sem(int num)
	{
		if (sem_init(&m_sem, 0, num) != 0)
		{
			throw exception();
		}
	}
	bool wait() { return sem_wait(&m_sem)==0; }
	bool post() { return sem_post(&m_sem) == 0; }

private:
	sem_t m_sem;
};
//������
class locker
{
public:
	locker()
	{
		if (pthread_mutex_init(&m_mutex, NULL) != 0)
			throw exception();
	}
	~locker()
	{
		pthread_mutex_destroy(&m_mutex);
	}
	bool lock()
	{
		return pthread_mutex_lock(&m_mutex)==0;
	}
	bool unlock()
	{
		return pthread_mutex_unlock(&m_mutex) == 0;
	}
	pthread_mutex_t* get()
	{
		return &m_mutex;
	}

private:
	pthread_mutex_t m_mutex;
};
class cond
{
public:
	cond()
	{
		if (pthread_cond_init(&m_cond, NULL) != 0)
			throw exception();
	}
	~cond() {
		pthread_cond_destroy(&m_cond);
	}
	bool wait()
	{

	}

private:
	pthread_cond_t m_cond;
};
