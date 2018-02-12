#include <iostream>
#include <string>
#include <string.h>
#include <map>
/* class Thousand; */
// class Hundred;
// class Ten;
// class One;


// class RNInterpreter{
// public:
// RNInterpreter();
// RNInterpreter(int){}
// int interpret(char*);
// virtual void interpret(char* input,int &total){
// int index;
// index = 0;
// }
// };

class Context;
class BooleanExp{
    public:
        BooleanExp(){}
        virtual bool Evaluate(Context&)=0;
        virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
        virtual BooleanExp* Copy() const  = 0;
};


class VariableExp:public BooleanExp{
    public:
        VariableExp(const char* );
        virtual ~VariableExp(){}
        virtual bool Evaluate(Context&);
        virtual BooleanExp* Replace(const char*,BooleanExp&);
        virtual BooleanExp* Copy()const;
        std::string GetName(){return std::string(name_);}
    private:
        char* name_;
};
class Context{
    public:
        bool Lookup(const char* name)const{
            // const std::string& s = std::string(name);
            // return map[s];
            return map.at(std::string(name));
        }
        void Assign(VariableExp* exp,bool b){
            map[exp->GetName()] =b;
        }
    private:
        std::map<const std::string,bool>map;

};
VariableExp::VariableExp(const char* name){
    name_ = strdup(name);
}

bool VariableExp::Evaluate(Context& aContext){
    return aContext.Lookup(name_);
}

BooleanExp* VariableExp::Copy()const {
    return new VariableExp(name_);
}

BooleanExp* VariableExp::Replace(const char* name,BooleanExp& exp){
    if(strcmp(name,name_)==0){
        return exp.Copy();
    }else{
        return new VariableExp(name_);
    }
}

class AndExp:public BooleanExp{
    public:
        AndExp(BooleanExp* ,BooleanExp*);
        virtual ~AndExp(){}
        virtual bool Evaluate(Context&);
        virtual BooleanExp* Replace(const char* ,BooleanExp&);
        virtual BooleanExp* Copy()const;
    private:
        BooleanExp* operand1_;
        BooleanExp* operand2_;
};

class Constant:public BooleanExp{
    public:
        Constant(bool b):value_(b){
        }
        virtual bool Evaluate(Context&){
            return value_;
        }
        virtual BooleanExp* Replace(const char*, BooleanExp&){
        }
        virtual BooleanExp* Copy() const{
        }
    private:
        const bool value_;

};

AndExp::AndExp(BooleanExp* op1,BooleanExp* op2){
    operand1_ = op1;
    operand2_ = op2;
}

bool AndExp::Evaluate(Context& aContext){
    return operand1_->Evaluate(aContext) && operand2_->Evaluate(aContext);
}

BooleanExp* AndExp::Copy()const{
    return new AndExp(operand1_->Copy(),operand2_->Copy());
}

BooleanExp* AndExp::Replace(const char* name,BooleanExp& exp){
    return new AndExp(operand1_->Replace(name,exp),operand2_->Replace(name,exp));
}

class NotExp:public BooleanExp{
    public:
        NotExp(BooleanExp* op){
            op_ = op;
        }
        virtual ~NotExp(){}
        virtual bool Evaluate(Context& aContext){
            return op_->Evaluate(aContext);
        }
        virtual BooleanExp* Replace(const char*,BooleanExp&){}
        virtual BooleanExp* Copy()const{}
    private:
        BooleanExp* op_;

};

int main(){
    BooleanExp* expression;
    Context context;
    VariableExp* x = new VariableExp("X");
    VariableExp* y  = new VariableExp("Y");
    expression = new AndExp(
            new AndExp(new Constant(true),x),
            new AndExp(y,new NotExp(x))
            );

    context.Assign(x,true);
    context.Assign(y,true);
    bool result  = expression->Evaluate(context);
    std::cout<<result<<std::endl;

}

