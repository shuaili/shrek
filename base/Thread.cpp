#include <base/Thread.h>
#include <sys/syscall.h>

using namespace std;
using namespace std::tr1;
namespace shrek {

namespace ThreadState {
__thread pid_t t_cachedTid = 0;
__thread const char* t_threadName = "main";

pid_t tid() {
    if(t_cachedTid == 0) {
        t_cachedTid = ::syscall(SYS_gettid);
    }
    return t_cachedTid;
}

bool isMainThread() {
    return tid() == getpid();
}

const char* name() {
    return t_threadName;
}
}

Thread::Thread(const string& name) { 
    _name = name;
    _func = NULL;
    _start = false;
    _stop = false;
}

Thread::~Thread() { 
}

void* Thread::hook(void* arg) {
    Thread* t = static_cast<Thread*>(arg);
    t->_tid = ThreadState::tid();
    ThreadState::t_threadName = t->_name.c_str();
    while(!t->_stop) {
        ScopedLock lock(t->_cond);
        while(!t->_func & !t->_stop) { t->_cond.wait(); }
        if(t->_stop) { return NULL; }
        t->_func();
        t->_func = NULL;
        t->_cond.signal();
    }
    return NULL;
}

void Thread::start() {
    assert(!_start);
    int ret = pthread_create(&_pid, NULL, &hook, this);
    assert(ret == 0);
    _start = true;
}

void Thread::stop() {
    ScopedLock lock(_cond);
    _stop = true;
    _cond.broadcast();
}

void Thread::run(Func func, bool block) {
    ScopedLock lock(_cond);
    while(_func) { 
        if(!block) return;
        _cond.wait(); 
    }
    _func = func;
    _cond.signal();
}

int Thread::join() {
    if(!_stop) { stop(); } 
    return pthread_join(_pid, NULL);
}

}

