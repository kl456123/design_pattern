#include <iostream>
#include <cstring>

using namespace std;

class Person;

class Command{
    Person* object_;
    void (Person::* method_)();
    public:
    Command(Person *obj = 0,void(Person::* meth)() = 0){
        object_ = obj;
        method_ = meth;
    }
    void execute(){
        (object_->*method_)();
    }
};

class Person{
    string name_;
    Command cmd_;
    public:
    Person(string n, Command c):cmd_(c){
        name_ = n;
    }
    void Talk(){
        cout<< name_<<" is talking "<<endl;
        cmd_.execute();
    }
    void PassOn(){
        cout<<name_<<" is passing on "<<endl;
        cmd_.execute();
    }
    void Gossip(){
        cout<<name_<<" is gossiping "<<endl;
        cmd_.execute();
    }
    void Listen(){
        cout<<name_<<" is listening "<<endl;
    }
};

int main(){
    Person wilma("Wilma",Command());
    Person betty("Betty",Command(&wilma,&Person::Listen));
    Person barney("Barney",Command(&betty,&Person::Gossip));
    Person fred("Fred",Command(&barney,&Person::PassOn));

    fred.Talk();
    return 0;
}
