#include <iostream>
#include <vector>

using namespace std;

/* class Node{ */
// public:
// Node(int v){
// m_val = v;
// m_next = 0;
// }
// void AddNode(Node* n){
// if(m_next){
// m_next->AddNode(n);
// }else{
// m_next = n;
// }
// }
// void Traverse(){
// cout<<m_val<<"  ";
// if(m_next){
// m_next->Traverse();
// }else{
// cout<<endl;
// }
// }
// void RemoveNode(int v){
// if(m_next){
// if(m_next->m_val==v){
// m_next= m_next->m_next;
// }else{
// m_next->RemoveNode(v);
// }
// }else{
// cout<<"not exist"<<endl;
// }
// }
// private:
// int m_val;
// Node* m_next;
// };

class Node{
    public:
        Node(int v){
            m_val = v;
        }

        int GetVal(){
            return m_val;
        }
    private:
        int m_val;
};

class List{
    public:
        void AddNode(Node* n){
            m_arr.push_back(n);
        }
        void Traverse(){
            for(int i=0;i<m_arr.size();i++){
                cout<<m_arr[i]->GetVal()<<" ";
            }
            cout<<endl;
        }
        void RemoveNode(int v){
            for(vector<Node*>::iterator it=m_arr.begin();it!=m_arr.end();it++){
                if((*it)->GetVal()==v){
                    m_arr.erase(it);
                    break;
                }
            }
        }
    private:
        vector<Node*> m_arr;
};

int main(){
    List lst;
    Node one(11);
    Node two(22),thr(33),fou(44);
    lst.AddNode(&two);
    lst.AddNode(&thr);
    lst.AddNode(&fou);
    lst.Traverse();
    lst.RemoveNode(44);
    lst.Traverse();
    lst.RemoveNode(22);
    lst.Traverse();
    lst.RemoveNode(11);
    lst.Traverse();
    lst.RemoveNode(23);

}
