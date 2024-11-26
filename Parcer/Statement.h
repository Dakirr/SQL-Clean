#ifndef STATEMENT_H
#define STATEMENT_H
#include "Tokenizer.h"

class Output {
    public:
    void* object;
    std::string out;
    Output (void* ob, std::string ou): object(ob), out(ou) {};
    Output (void* ob): object(ob), out() {};
    Output (std::string ou): object(), out(ou) {};
    Output (): object(), out() {};
    Output operator= (Output other);
    template <typename T>
    T* get(T x) {
        return (T*) object;
    };
};

class Statement {
    protected:
    bool is_applied;
    std::vector<Statement> arg_st;
    Token* args;
    Output result;
    public:
       
    virtual void apply() = 0;
    Output& get();
};


#endif