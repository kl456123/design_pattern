#include <iostream>
#include <cstddef>
using namespace std;


// Abstract class
//
class Handler{
    protected:
        Handler* next_;
    public:
        Handler(){
            next_ = nullptr;
        }
        virtual ~Handler(){}
        virtual void Request(int value) = 0;
        void SetNextHandler(Handler* nextInLine){
            next_ = nextInLine;
        }
        void AddNextHandler(Handler* nextInLine){
            if(next_){
                next_->AddNextHandler(nextInLine);
            }else{
                next_ = nextInLine;
            }
        }
        void Clean(){
            if(next_){
                next_->Clean();
            }
            delete next_;
        }
};


class SpecialHandler:public Handler{
    private:
        int limit_;
        int ID_;
    public:
        SpecialHandler(int theLimit,int theID){
            limit_ = theLimit;
            ID_ = theID;
        }
        void Request(int value){ if(value<limit_){ cout<<"Handler "
                <<ID_
                <<" handled the request with a limit of "
                <<limit_<< endl;
        }else if(next_!= NULL){ next_->Request(value);
        }else{
            // the last
            cout<<"Sorry, I am the last handler ("
                <<ID_
                <<") and I couldn't even handle that request."
                <<endl;
        }
        }
};

class HandlerFactory{
    public:
        HandlerFactory(){
            num_handler_ = 0;
        }
        Handler* MakeHandler(int theLimit){
            num_handler_ ++;
            return new SpecialHandler(theLimit,num_handler_);
        }
    private:
        int num_handler_;
};
int main(){
    HandlerFactory* handler_factory = new HandlerFactory();
    Handler* h1 = handler_factory->MakeHandler(10);
    Handler* h2 = handler_factory->MakeHandler(20);
    Handler* h3 = handler_factory->MakeHandler(30);

    // chain up together
    h1->AddNextHandler(h2);
    h1->AddNextHandler(h3);

    h1->Request(40);

    h1->Request(18);
    h1->Clean();
}
