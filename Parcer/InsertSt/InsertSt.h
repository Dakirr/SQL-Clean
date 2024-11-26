#ifndef INSERT_ST_H
#define INSERT_ST_H
#include "../Statement.h"
#include "../Global/Global.h"
class InsertSt: public Statement {
    public:
    InsertSt(Token *T);
    void apply();
};


#endif