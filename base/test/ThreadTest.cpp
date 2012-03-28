#include <base/Thread.h>
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
    vector<Thread*> ts;
    for(int i = 0; i < 10; ++i) {
        Thread* t = new Thread(name + subfix[i]);
        t->start();
        t->run(foo);
        ts.push_back(t);
    }
    for(int i = 0; i < 10; ++i) {
        ts[i]->stop();
        ts[i]->join();
    }

    return 0;
}
