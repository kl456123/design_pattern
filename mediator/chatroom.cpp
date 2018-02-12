#include <iostream>
#include <string>
#include <map>

using namespace std;

class User;
class ChatRoom{
    public:
        ChatRoom();
        virtual ~ChatRoom();
        static void ShowMessage(User* user,string message);
        static void SendPrivacyMessage(User* sender,string message,User* receiver);
        static void ReceivePrivacyMessage(User* receiver,string& info);
        static string GenerateInfo(string message);
    private:
        static map<string,string>mailbox_;
};




class User{
    public:
        User(string name);
        virtual ~User(){}
        virtual void SendMessage(string message);
        virtual void ReceiveMessage();
        virtual string GetName();
        virtual string GetPrivacyInfo();
    protected:
        string name_;
        string mailinfo_;
};


string GenerateInfo(User* user,string message){
    return "[" + user->GetName()+"]: "+message;
}

void ChatRoom::ShowMessage(User* user,string message){
    cout<<::GenerateInfo(user,message)<<endl;
}

void ChatRoom::ReceivePrivacyMessage(User* receiver,string& info){
    if(mailbox_.find(receiver->GetName())!=mailbox_.end()){
        info = mailbox_[receiver->GetName()];
    }
}

void ChatRoom::SendPrivacyMessage(User* sender,string message,User* receiver){
    mailbox_[receiver->GetName()] = ::GenerateInfo(sender,message);
}

User::User(string name){
    name_ = name;
}
string User::GetName(){
    return name_;
}
string User::GetPrivacyInfo(){
    return this->mailinfo_;
}

void User::SendMessage(string message){
    ChatRoom::ShowMessage(this,message);
}
void User::ReceiveMessage(){
    ChatRoom::ReceivePrivacyMessage(this,mailinfo_);
}

class SuperUser:public User{
    public:
        SuperUser(string name);
        void AddSuperName();
};

SuperUser::SuperUser(string name):User(name){
    AddSuperName();
}

void SuperUser::AddSuperName(){
    name_ = "SuperUser "+name_;
}

map<string,string>ChatRoom::mailbox_;
int main(){

    User* robert = new User("Robert");
    User* john = new SuperUser("John");
    User* mike = new SuperUser("Mike");

    robert->SendMessage("Hi! John!");
    john->SendMessage("Hello! Robert!");
    ChatRoom::SendPrivacyMessage(mike,"privacy message",john);
    john->ReceiveMessage();
    john->SendMessage(john->GetPrivacyInfo());

}
