#include <iostream>

using namespace std;
class StackIter;
class Stack{
    int items[10];
    int sp;
    public:
    friend class StackIter;
    Stack(){
        sp = -1;
    }
    void Push(int in){
        items[++sp] = in;
    }
    int Pop(){
        return items[sp--];
    }
    bool isEmpty(){
        return (sp == -1);
    }
    StackIter* CreateIterator()const;
};

class StackIter{
    const Stack* stk;
    int index;
    public:
    StackIter(const Stack* s){
        stk = s;
    }
    void First(){
        index = 0;
    }
    void Next(){
        index ++;
    }
    bool IsDone(){
        return index == stk->sp+1;
    }
    int CurrentItem(){
        return stk->items[index];
    }
};

StackIter* Stack::CreateIterator()const{
    return new StackIter(this);
}

bool operator==(const Stack&l,const Stack&r){
    StackIter* s1 = l.CreateIterator();
    StackIter* s2 = r.CreateIterator();
    for(s1->First(),s2->First();!s1->IsDone()&&!s2->IsDone();s1->Next(),s2->Next()){
        if(s1->CurrentItem()!=s2->CurrentItem()){
            break;
        }
    }
    bool ans = s1->IsDone()&& s2->IsDone();
    delete s1;
    delete s2;
    return ans;
}

int main(){
    Stack s1;
    for (int i = 1; i < 5; i++)
        s1.Push(i);
    Stack s2(s1), s3(s1), s4(s1), s5(s1);
    s3.Pop();
    s5.Pop();
    s4.Push(2);
    s5.Push(9);
    cout << "1 == 2 is " << (s1 == s2) << endl;
    cout << "1 == 3 is " << (s1 == s3) << endl;
    cout << "1 == 4 is " << (s1 == s4) << endl;
    cout << "1 == 5 is " << (s1 == s5) << endl;
}
