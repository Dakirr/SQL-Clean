#ifndef CREATE_COLLUMN_H
#define CREATE_COLLUMN_H
#include "../GetValueSt/GetValueSt.h"
#include "../../Collumn/Collumn.h"

class CreateCollumnSt: public Statement {
    private:
    public:
    CreateCollumnSt(Token* T);
    void apply();
};

#endif