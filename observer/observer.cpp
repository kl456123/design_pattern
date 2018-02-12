#include<iostream>
#include <vector>

using namespace std;
class Observer{
    public:
        virtual void Update(int value)=0;
};


class Subject{
    int m_value;
    vector<Observer*> m_views;
    public:
    void Attach(Observer* obs){
        m_views.push_back(obs);
    }
    void SetVal(int value){
        m_value= value;
        Notify();
    }

    void Notify(){
        for(int i=0;i<m_views.size();i++){
            m_views[i]->Update(m_value);
        }
    }
};


class DivObserver:public Observer{
    int m_div;
    public:
    DivObserver(Subject* model,int div){
        model->Attach(this);
        m_div = div;
    }

    void Update(int v){
        cout<<v<<" div"<<m_div<<" is "<<v/m_div<<endl;
    }
};

class ModObserver:public Observer{
    int m_mod;
    public:
    ModObserver(Subject* model,int mod){
        model->Attach(this);
        m_mod = mod;
    }
    void Update(int v){
        cout<< v <<" mod "<<m_mod<<" is "<<v%m_mod<<endl;
    }
};

int main(){
    Subject subj;
    DivObserver divObs1(&subj,4);
    DivObserver divObs2(&subj,3);
    ModObserver modObv3(&subj,3);
    subj.SetVal(14);
    return 0;
}
