#include <iostream>

using namespace std;

class Color{
    public:
        virtual void Accept(class Visitor*) = 0;
};

class Red:public Color{
    public:
        void Accept(Visitor*);
        void Eye(){
            cout<<"Red::eye";
        }
};

class Blu:public Color{
    public:
        void Accept(Visitor*);
        void Sky(){
            cout<<"Blu::sky";
        }
};

class Visitor{
    public:
        virtual void Visit(Red*)=0;
        virtual void Visit(Blu*)=0;
};

class CountVisitor:public Visitor{
    public:
        CountVisitor(){
            m_num_red = m_num_blu = 0;
        }

        void Visit(Red*){
            ++m_num_red;
        }
        void Visit(Blu*){
            ++m_num_blu;
        }
        void ReportNum(){
            cout<<"Reds "<<m_num_red<<", Blus "<<m_num_blu<<endl;
        }
    private:
        int m_num_red,m_num_blu;
};

class CallVisitor:public Visitor{
    public:
        void Visit(Red* r){
            r->Eye();
        }
        void Visit(Blu* b){
            b->Sky();
        }
};

void Red::Accept(Visitor* v){
    v->Visit(this);
}

void Blu::Accept(Visitor* v){
    v->Visit(this);
}

int main(){
    Color* set[] = {new Red,new Blu,new Blu,new Red,new Red,0};

    CountVisitor count_operation;
    CallVisitor call_operation;
    for(int i=0;set[i];i++){
        set[i]->Accept(&count_operation);
        set[i]->Accept(&call_operation);
    }
    count_operation.ReportNum();

}

