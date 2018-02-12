#include <iostream>
#include <vector>
using namespace std;
/* class Receiver; */
// class Actions{
// public:
// Actions(Receiver* receiver){
// }
// void Run(){
// cout<<""
// }
// protected:
// Receiver* receiver_;
/* }; */
class Receiver{
    public:
        Receiver(){}
        virtual ~Receiver(){}
        void Actions(){
            cout<<"receiver action "<<endl;
        }
        void Run(){
            cout<<"receiver run "<<endl;
        }
};

typedef void (Receiver::*Action)();

// Abstract class
class Command{
    public:
        // bind object and method to construct a full command
        Command(Receiver* receiver,Action method){
            receiver_ = receiver;
            method_ = method;
        }
        void execute(){
            (receiver_->*method_)();
        }
    protected:
        Receiver* receiver_;
        Action method_;
};


class ConcreteCommand:public Command{
    public:
        ConcreteCommand(Receiver* receiver,Action method)
            :Command(receiver,method){
            }
};

class Invoker{
    public:
        Invoker(){
            cmd_idx_= 0;
        }
        void AddCommand(Command* command){
            commands_.push_back(command);
        }
        void CallOneCommand(){
            cout<<"Invoker calling "<<endl;
            commands_[cmd_idx_]->execute();
        }
        void CallAllCommands(){
            while(!IsDone()){
                CallOneCommand();
                Next();
            }

        }
        /* void Run(){ */
            // while(!IsDone()){

            // }
        /* } */
        void Next(){
            cmd_idx_++;
        }
        bool IsDone(){
            return cmd_idx_>=commands_.size();
        }
    protected:
        vector<Command*> commands_;
        int cmd_idx_;
};

int main(){
    Receiver* receiver = new Receiver();
    Command* command = new ConcreteCommand(receiver,&Receiver::Actions);
    Invoker* invoker = new Invoker();
    invoker->AddCommand(command);
    invoker->CallAllCommands();
    return 0;
}
