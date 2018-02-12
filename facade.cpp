#include<iostream>
#include <vector>
class istream;
class Token;
class Scanner{
    public:
        Scanner(istream&);
        virtual ~Scanner();
        virtual Token& Scan();
    private:
        istream& inputStream_;
};

class ProgramNodeBuilder;
class Parser{
    public:
        Parser();
        virtual ~Parser();
        virtual void Parse(Scanner& , ProgramNodeBuilder&);
};

class ProgramNode;
class ProgramNodeBuilder{
    public:
        ProgramNodeBuilder();
        virtual ProgramNode* NewVariable(const char* variableName)const;
        virtual ProgramNode* NewAssignment(ProgramNode* variable,ProgramNode* expression)const;
        virtual ProgramNode* NewReturnStatement(ProgramNode* value)const;
        virtual ProgramNode* NewCondition(ProgramNode* condition,ProgramNode* truePart,
                ProgramNode* falsePart)const;
        //...
        ProgramNode* GetRootNode();
    private:
        ProgramNode* node_;
};
class StatementNode;
class ExpressionNode;
class BytecodeStream;
class CodeGenerator{
    public:
        virtual void Visit(ExpressionNode*);
        virtual void Visit(StatementNode*);
        //...
    protected:
        CodeGenerator(BytecodeStream&);
    protected:
        BytecodeStream* output_;
};
class RISCCodeGenerator:public CodeGenerator{
    public:
        RISCCodeGenerator(BytecodeStream&);
};
// composite

class ProgramNode{
    public:
        virtual void GetSourcePosition(int& line,int& index);
        //child manipulation
        virtual void Add(ProgramNode*);
        virtual void Remove(ProgramNode*);
        virtual void Traverse(CodeGenerator&);
    protected:
        ProgramNode();
};

class StatementNode: public ProgramNode{};
class ExpressionNode:public ProgramNode{
    public:
        virtual void Traverse(CodeGenerator&);
    private:
        std::vector<ProgramNode*> children_;

};
class ListIterator{
    public:
        ListIterator(std::vector<ProgramNode*>);
};
void ExpressionNode::Traverse(CodeGenerator& cg){
    // visit this first
    cg.Visit(this);
    ListIterator i(children_);
    for(i.First();!IsDone();i.Next()){
        i.CurrentItem()->Traverse(cg);
    }

}

// facade class
class Compiler{
    public:
        Compiler();
        virtual void Compile(istream& ,BytecodeStream&);
};

void Compiler::Compile(istream& input,BytecodeStream& output){
    // lex analysis
    Scanner scanner(input);
    ProgramNodeBuilder builder;

    // semantic analysis
    Parser parser;
    parser.Parse(scanner,builder);

    // target-code generation
    // constructor
    RISCCodeGenerator generator(output);
    ProgramNode* parseTree = builder.GetRootNode();
    // generate code with traversing parseTree
    parseTree->Traverse(generator);
}



