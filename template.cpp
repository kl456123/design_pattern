#include <iostream>

using namespace std;

class Base{
    void A(){
        cout<<"A  ";
    }
    void C(){
        cout<<"C  ";
    }
    void E(){
        cout<<"E  ";
    }

    virtual void Ph1() = 0;
    virtual void Ph2() = 0;
    public:
    void Execute(){
        A();
        Ph1();
        C();
        Ph2();
        E();
    }
};


class One:public Base{
    void Ph1(){
        cout<<"B ";
    }
    void Ph2(){
        cout<<"D ";
    }
};

class Two:public Base{
    void Ph1(){
        cout<<"2 ";
   }
    void Ph2(){
        cout<<"4 ";
    }
};

int main(){
    Base* array[] = {
        new One(),new Two()
    };
    for(int i =0;i<2;i++){
        array[i]->Execute();
        cout<<endl;
    }
}

