#include "CreateCollumnSt.h"

CreateCollumnSt::CreateCollumnSt(Token* S) {
    this->args = S;
}

void CreateCollumnSt::apply() {
    this->is_applied = true;

    Token* cur = this->args;
    bool flags[3] = {0};
    if (cur->cat == CBR) {
        Token* flag_cur = prepare(cur->value);
        flag_cur = flag_cur->right;
        while (true) {
            if (flag_cur->value == "key") {
                flags[0] = true;
            } else if (flag_cur->value == "unique") {
                flags[1] = true;
            } else if (flag_cur->value == "autoincrement") {
                flags[2] = true;
            } else {
                error("unknown collumn flag: \'" + flag_cur->value + "\'", "Flag");
            }
            if (flag_cur->right->cat == SYNT && flag_cur->right->right->cat == ID) {
                flag_cur = flag_cur->right->right;
            } else {
                break;
            }
        }
    cur = cur->right;
    } 
    
    std::string name;
    if (cur->cat != ID) {
        error("expected a name of collumn in statement " + cur->value, "Syntax");
    } else {
        name = cur->value;
    }
    cur = cur->right;
    if (cur->cat != SYNT) {
        error("expected \':\' after the name of collumn in statement " + cur->value, "Syntax");
    }
    cur = cur->right;
    ObjectType type;
    if (cur->cat != TYPE) {
        error("expected a type of collumn in statement " + cur->value, "Syntax");
    } else {
        type = *((GetTypeSt(cur).get()).get(ObjectType()));
    }
    cur = cur->right;
    if (cur->cat == TYPE) {
        cur = cur->right;
    }
    GenericObject default_value = GenericObject();
    if (cur->cat == OP) {
        cur = cur->right;
        default_value = *((GetValueSt(cur, type).get()).get(GenericObject()));
    }
    Collumn* ret = new Collumn(name, type, flags[0], flags[1], flags[2], default_value);
    //ret->DEBUG_PRINT();
    this->result = Output(ret);
}