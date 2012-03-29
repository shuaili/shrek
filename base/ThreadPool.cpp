#include <base/ThreadPool.h>

using namespace std;
using namespace std::tr1;
namespace shrek {

ThreadPool::ThreadPool(int num) { 
    _threads.resize(num);
    _running = false;
}

ThreadPool::~ThreadPool() { 
}

void ThreadPool::threadHook() {
    Thread::Func func;
    while(_running) {
        {
            ScopedLock lock(_cond);
            while(_task.empty() && _running) { _cond.wait(); }
            if(!_running) { break; }
            if(_task.empty()) { continue; }
            func = _task.front();
            _task.pop_front();
        }
        func();
    }
}

void ThreadPool::start() {
    assert(!_running);
    _running = true;
    for(int i = 0; i < _threads.size(); ++i) {
        Thread* t = new Thread;
        t->run(bind(&ThreadPool::threadHook, this));
        _threads[i] = t;
    }

}

void ThreadPool::run(Thread::Func func) {
    if(_threads.empty()) {
        func();
    }
    ScopedLock lock(_cond);
    _task.push_back(func);
    _cond.signal();
}

void ThreadPool::stop() {
    _running = false;
    _cond.broadcast();
    for(int i = 0; i < _threads.size(); ++i) {
        _threads[i]->join();
    }
}

}

