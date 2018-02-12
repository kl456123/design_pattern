#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>

using namespace std;
class Base{
    Base* next;
    public:
    Base(){
        next = 0 ;
    }
    void SetNext(Base* n){
        next = n;
    }
    void Add(Base* n){
        if(next){
            next->Add(n);
        }else{
            next = n;
        }
    }

    virtual void Handle(int i){
        next->Handle(i);
    }
};

class Handler1:public Base{
    public:
        void Handle(int i){
            if(rand()%3){
                cout<<"H1 passed "<<i<<" ";
                Base::Handle(i);
            }else{
                cout<<"H1 handled "<<i<<" ";
            }
        }
};

class Handler2:public Base{
    public:
        void Handle(int i){
            if(rand()%3){
                cout<<"H2 passed "<<i<<" ";
                Base::Handle(i);
            }else{
                cout<<"H2 handled "<<i<<" ";
            }
        }
};

class Handler3:public Base{
    public:
        void Handle(int i){
            if(rand()%3){
                cout<<"H3 passed "<<i<<" ";
                Base::Handle(i);
            }else{
                cout<<"H3 handled "<<i<<" ";
            }
        }
};

int main(){
    srand(time(0));
    Handler1 root;
    Handler2 two;
    Handler3 thr;
    root.Add(&two);
    root.Add(&thr);
    thr.SetNext(&root);
    for(int i = 1;i<10;i++){
        root.Handle(i);
        cout<<'\n';
    }
}


