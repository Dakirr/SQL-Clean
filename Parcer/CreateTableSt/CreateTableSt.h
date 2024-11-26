#ifndef CREATE_H
#define CREATE_H
#include "../../Table/Table.h"
#include "../CreateCollumnSt/CreateCollumnSt.h"

class CreateTableSt: public Statement {
    private:
    public:
    CreateTableSt(Token* T);
    void apply();
};
#endif