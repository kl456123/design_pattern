#include <iostream>
#include <vector>

using namespace std;

class Subject{
    vector<class Observer*> views;
    int value;
    public:
    void Attach(Observer* obs){
        views.push_back(obs);
    }
    void SetVal(int val){
        value = val;
        Notify();
    }
    int GetVal(){
        return value;
    }
    void Notify();
};

class Observer{

};
