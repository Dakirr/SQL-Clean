#include "CreateTableSt.h"

CreateTableSt::CreateTableSt(Token* T) {
    this->args = T;
};
void CreateTableSt::apply() {
    Token* cur = this->args;
    // if (cur->right->value != "create" || cur->right->right->value != "table") {
    //     error("wrong command: called CreateTable, should be " + this->args->value, "Implementation");
    // }
    //print(cur);
    //cur = cur->right;
    if (cur->cat != ID) {
        error("expected a name of table in the statement \'" + this->args->value + ", got " + cur->value, "Syntax");
    }
    std::string name = cur->value;
    Table* T = new Table(name);
    cur = cur->right;
    if (cur->cat == BR) {
        Token* cur_br = prepare(cur->value);
        cur_br = cur_br->right;
        //print(cur_br);
        //std::cerr << "want to enter with ";
        //print(cur_br);
        T->add_collumn(*(CreateCollumnSt(cur_br).get().get(Collumn())));
        //T->print();
        cur_br = cur_br->right;
        while (cur_br->cat != HEAD) {
            //std::cerr << "###########################################again \n";
            //print(cur_br);
            if (cur_br->cat == SYNT && cur_br->value == "," && (cur_br->right->cat == ID || cur_br->right->cat == CBR)) {
                cur_br = cur_br->right;
                Collumn* x;
                CreateCollumnSt St = CreateCollumnSt(cur_br);
                St.apply();
                x = St.get().get(Collumn());
                T->add_collumn(*x);

                //
                // x = new Collumn();  
                // x = CreateCollumnSt(cur_br).get()->get(Collumn()) 
            
            }
            cur_br = cur_br->right;
        }
        this->result = Output(T); 
        std::cout << "Table created: \n";
        T->print();
    }

};