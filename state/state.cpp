#include <iostream>

using namespace std;

class Machine;
class State{
    public:
        virtual void On(Machine* m){
            cout<<" already ON\n";
        }
        virtual void Off(Machine* m){
            cout<<" already OFF\n";
        }
};

class OFF:public State{
    public:
        OFF(){
            cout<<" OFF-ctor";
        }
        virtual ~OFF(){
            cout<<" dtor-OFF\n";
        }
        void On(Machine* m);

};


class Machine{
    class State* current;
    public:
    Machine(){
        current = new OFF();
        cout<<endl;
    }
    void SetCurrent(State* s){
        current = s;
    }
    void On();
    void Off();
};


class ON:public State{
    public:
        ON(){
            cout<<" ON-ctor";
        }
        virtual ~ON(){
            cout<<" dtor-ON\n";
        }
        void Off(Machine* m){
            cout<<" going from NO to OFF";
            m->SetCurrent(new OFF());
            delete this;
        }
};


void Machine::On(){
    current->On(this);
}

void Machine::Off(){
    current->Off(this);
}

void OFF::On(Machine* m)
{
    cout<<" going from OFF to ON";
    m->SetCurrent(new ON());
    delete this;
}
int main(){
    void(Machine::*ptrs[])() = {&Machine::Off,&Machine::On};

    Machine fsm;
    int num;
    while(1){
        cout<<"Enter 0/1";
        cin>>num;
        (fsm.*ptrs[num])();
    }
}
