#include "InsertSt.h"

InsertSt::InsertSt(Token *T) {
    this->args = T;
};

void InsertSt::apply() {
    Token* cur = this->args;
    if (cur->cat != BR) {
        error("expected \'(\' in insert statement, got " + cur->value, "Syntax");
    }
    Token* cur_to = cur->right->right;
    Table T;
    if (cur_to->cat != ID) {
        error("expected table name as an insert argument, got " + cur_to->value, "Syntax");
    }

    if (!Tables.count(cur_to->value)) {
        error("table " + cur->value + " not found", "Index");    
    }


    T = Tables[cur_to->value];
    Token* cur_br = prepare(cur->value);
    cur_br = cur_br->right;
    //std::cerr << (cur_br->cat == SYNT || cur_br->cat == STR || cur_br->cat == LOG || cur_br->cat == NONE || cur_br->cat == NUM || cur_br->cat == BYTE);
    if (cur_br->cat == ID) {
        std::map<std::string, GenericObject> row;
        while (cur_br->cat != HEAD) {
            if (cur_br->cat == SYNT) {
                cur_br = cur_br->right;
            } else if (cur_br->cat == ID){
                //std::cerr << "Here: " << create_object(cur_br->right->right->value, T.collumns[cur_br->value].type).get_string();
                row[cur_br->value] = create_object(cur_br->right->right->value, T.collumns[cur_br->value].type);
                cur_br = cur_br->right->right->right;
            } else {
                error("expected the name of collumn to insert, got " + cur_br->value, "Syntax");
            }
        }
        T.add_row(row);
        Tables[cur_to->value] = T;
    } else if (cur_br->cat == SYNT || cur_br->cat == STR || cur_br->cat == LOG || cur_br->cat == NONE || cur_br->cat == NUM || cur_br->cat == BYTE) {
        std::map<std::string, GenericObject> row;
        //GenericObject ret (T.collumns[T.collumn_names[0]].type);
        int i = 1;
        int l = T.collumn_names.size();
        while (cur_br->cat != HEAD) {
            if (cur_br->cat == SYNT) {
                i++;
            } else if (cur_br->cat == STR || cur_br->cat == LOG || cur_br->cat == NONE || cur_br->cat == NUM || cur_br->cat == BYTE) {
                row[T.collumn_names[i]] = create_object(cur_br->value, T.collumns[T.collumn_names[i]].type);
            } else {
                error("expected either a value or a comma, got " + cur_br->value + " instead", "Syntax");
            }
            cur_br = cur_br->right;
            //print(cur_br);
        }
        //error("add row for vector is not implemented yet", "W.I.P.");
        T.add_row(row);
        Tables[cur_to->value] = T;
    }
    std::cout << "Row added: \n";
    T.print();
    //if (cur_br->right != )
    //print(cur_br); 
};