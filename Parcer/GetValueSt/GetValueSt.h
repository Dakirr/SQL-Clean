#ifndef GETVALUEST_H
#define GETVALUEST_H
#include "../GetTypeSt/GetTypeSt.h"
#include "../../GenericObject/GenericObject.h"

class GetValueSt: public Statement {
    private:
    ObjectType type;
    public:
    GetValueSt(Token* T, GetTypeSt S);
    GetValueSt(Token* T, Output S);
    GetValueSt(Token* T, ObjectType S);
    void apply();
};
#endif