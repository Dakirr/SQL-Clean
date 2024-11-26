#ifndef GETTYPEST_H
#define GETTYPEST_H
#include "../Statement.h"
#include "../../ObjectType/ObjectType.h"

class GetTypeSt: public Statement {
    public:
    GetTypeSt(Token* T);

    void apply();
};
#endif