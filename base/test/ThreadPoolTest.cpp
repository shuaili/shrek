#include <base/Thread.h>
#include <base/ThreadPool.h>
#include <vector>
using namespace std;
using namespace shrek;
void foo() {
//    while(true)
 {
    cout<<"----------"<<endl;
    cout<<"I'm foo"<<endl;
    cout<<"tid:"<<ThreadState::tid()<<endl;
    cout<<"name:"<<ThreadState::name()<<endl;
    cout<<"isMainThread:"<<ThreadState::isMainThread()<<endl;
    }
}

int main() {
//    foo();
    char subfix[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'} ;
    string name = "xiaobao";
    ThreadPool pool(10);
    pool.start();
    for(int i = 0; i < 10; ++i) {
        pool.run(foo);
    }
    sleep(2);
    pool.stop();

    return 0;
}
