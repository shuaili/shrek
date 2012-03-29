#ifndef SHREK_THREADPOOL_H
#define SHREK_THREADPOOL_H

#include <common/Common.h>
#include <base/Thread.h>
#include <vector>
#include <deque>
namespace shrek {

class ThreadPool
{
public:
    ThreadPool(int32_t num = 0);
    ~ThreadPool();
private:
    ThreadPool(const ThreadPool &);
    ThreadPool& operator=(const ThreadPool &);
public:
    void start();
    void run(Thread::Func func);
    void stop();
private:
    void threadHook();
    std::vector<Thread*> _threads;
    std::deque<Thread::Func> _task;
    bool _running;
    ThreadCond _cond;
};

}

#endif //SHREK_THREADPOOL_H
