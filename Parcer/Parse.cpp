#include "Parse.h"

Output parse(std::string S) {
    Token* T = prepare(S);
    print(T);
    Token* cur = T;
    cur = cur->right;
    while (cur->cat != HEAD) {
        if (cur->cat == KEY) {
            if (cur->value == "create") {
                cur = cur->right;
                if (cur->cat != KEY) {
                    error("expected table/ordered index/unordered index after create, got " + cur->value, "Syntax");
                } else {
                    if (cur->value == "table") {
                        CreateTableSt CTS (cur->right);
                        Table* T;
                        T = CTS.get().get(Table("x"));
                        Tables[T->name] = (*T);
                    } else if (cur->value == "ordered") {
                        error("ordered index is not implemented yet", "W.I.P.", 0);
                    } else if (cur->value == "unordered") {
                        error("unordered index is not implemented yet", "W.I.P.", 0);
                    } else {
                        error("expected table/ordered index/unordered index after create, got " + cur->value, "Syntax");
                    } 
                }
            } else if (cur->value == "insert") {
                InsertSt IS (cur->right);
                IS.apply();

            }
        }
        cur = cur->right;
    }
    //print(T);
    return Output("");
}