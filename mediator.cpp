#include <iostream>
#include <string>

using namespace std;
class FilSelectionDialog;

class Widget{
    public:
        Widget(FilSelectionDialog* mediator,string& name){
            mediator_ = mediator;
            name_ = name;
        }
        virtual void Changed();
        virtual void UpdateWidget() = 0;
        virtual void QueryWidget() = 0;
    protected:
        string name_;
    private:
        FilSelectionDialog* mediator_;
};

class List:public Widget{
    public:
        List(FilSelectionDialog)
};

