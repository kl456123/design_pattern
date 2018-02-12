/* class HelpHandler{ */
// public:
// HelpHandler(HelpHandler* s):successor_(s){}
// virtual void HandleHelp();
// private:
// HelpHandler* successor_;
// };


// void HelpHandler::HandleHelp(){
// if(successor_){
// successor_->HandleHelp();
// }
// };
// enum Kind{Help,Print,Preview};
// class Request{
// public:
// Kind GetKind(){}
// };
// class HelpRequest:public Request{};
// class PrintRequest:public Request{};

// class Handler{public:
// void HandleRequest(Request*);
// };


// void Handler::HandleRequest(Request* theRequest){
// switch(theRequest->GetKind()){
// case Help:
// HandleHelp((HelpRequest*)theRequest);
// break;
// case Print:
// HandlePrint((PrintRequest*)theRequest);
// break;
// default:
// break;
// }
// }

// class ExtendedHandler:public Handler{
// public:
// virtual void HandleRequest(Request* theRequest);
// // ...
// };
// // forwarding mode
// void ExtendedHandler::HandleRequest(Request* theRequest){
// switch(theRequest->GetKind()){
// case Preview:
// break;
// default:
// Handler::HandleRequest(theRequest);
// }
// }


typedef int Topic;
const Topic NO_HELP_TOPIC = -1;

class HelpHandler{
    public:
        HelpHandler(HelpHandler* = 0, Topic = NO_HELP_TOPIC);
        virtual bool HasHelp();
        virtual void SetHandler(HelpHandler*, Topic);
        virtual void HandleHelp();
    private:
        HelpHandler* successor_;
        Topic topic_;
};
HelpHandler::HelpHandler(HelpHandler* h, Topic t):successor_(h),topic_(t){}
bool HelpHandler::HasHelp(){
    return topic_!= NO_HELP_TOPIC;
}
void HelpHandler::HandleHelp(){
    if(successor_!=0){
        successor_->HandleHelp();
    }
}

class Widget:public HelpHandler{
    protected:
        Widget(Widget* parent,Topic NO_HELP_TOPIC);
    private:
        Widget* parent_;
};

Widget::Widget(Widget* w, Topic t):HelpHandler(w,t){
    parent_ = w;
}

class Button:public Widget{
    public:
        Button(Widget* d,Topic t = NO_HELP_TOPIC);
        virtual void HandleHelp();
};

Button::Button(Widget* h, Topic t):Widget(h,t){}
void Button::HandleHelp(){
    if(HasHelp()){
        // offer help on the button
    }else{
        HelpHandler::HandleHelp();
    }
}
