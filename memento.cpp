#include <iostream>

using namespace std;
class Number;

class Memento{
    public:
        Memento(int val){
            state_ = val;
        }

    private:
        friend class Number;
        int state_;
};

class Number{
    public:
        Number(int value){
            value_ = value;
        }
        void Dubble(){
            value_*=2;
        }
        void Half(){
            value_/=2;
        }
        int GetValue(){
            return value_;
        }
        Memento* CreateMemento(){
            return new Memento(value_);
        }
        void ReinstateMemento(Memento* mem){
            value_ = mem->state_;
        }

    private:
        int value_;
};

class Command{
    public:
        typedef void(Number::*Action)();
        Command(Number* receiver,Action action){
            receiver_ = receiver;
            action_ = action;
        }
        virtual void Execute(){
            mementoList_[num_commands_] = receiver_->CreateMemento();
            commandList_[num_commands_] = this;
            if(num_commands_>high_water_){
                high_water_ = num_commands_;
            }
            num_commands_++;
            (receiver_->*action_)();
        }

        static void Undo(){
            if(num_commands_==0){
                cout<<" Attempt to run off the end!"<<endl;
                return ;
            }
            commandList_[num_commands_-1]->receiver_->ReinstateMemento(mementoList_[num_commands_-1]);
            num_commands_--;
        }

        void static Redo(){
            if(num_commands_>high_water_){
                cout<<"*** Attempt to run off the end!! ***"<<endl;
                return;
            }
            // make object do certain sth
            (commandList_[num_commands_]->receiver_->*(commandList_[num_commands_]->action_))();
            num_commands_++;
        }

    protected:
        Number* receiver_;
        Action action_;
        static Command* commandList_[20];
        static Memento* mementoList_[20];
        static int num_commands_;
        static int high_water_;
};

// initialize privacy member
Command* Command::commandList_[];
Memento* Command::mementoList_[];
int Command::num_commands_;
int Command::high_water_;

int main(){
    int i;
    cout<<"Interge: "<<endl;
    cin>>i;
    Number *object = new Number(i);
    Command* commands[3];
    commands[1] = new Command(object, &Number::Dubble);
    commands[2] = new Command(object,&Number::Half);
    cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    cin>>i;
    while(i){
        if(i==3){
            Command::Undo();
        }else if(i==4){
            Command::Redo();
        }else{
            commands[i]->Execute();
        }
        cout<<"  "<<object->GetValue()<<endl;
        cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
        cin>>i;
    }
}


