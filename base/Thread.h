#ifndef SHREK_THREAD_H
#define SHREK_THREAD_H

#include <common/Common.h>
#include <pthread.h>
#include <base/Lock.h>

namespace shrek {

class Thread
{
public:
    Thread(const std::string& name = std::string());
    ~Thread();
private:
    Thread(const Thread &);
    Thread& operator=(const Thread &);
public:
    typedef std::tr1::function<void()> Func;
    void start();
    void stop();
    void run(Func func, bool block = true);
    int join();
private:
    static void* hook(void*);
    Func _func;
    pthread_t _pid;
    pid_t _tid;
    std::string _name;
    ThreadCond _cond;
    bool _start;
    bool _stop;
};

SHREK_TYPEDEF_PTR(Thread);

namespace ThreadState {
pid_t tid();
bool isMainThread();
const char* name();
}

}

#endif //SHREK_THREAD_H
