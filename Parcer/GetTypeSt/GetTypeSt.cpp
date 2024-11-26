#include "GetTypeSt.h"

GetTypeSt::GetTypeSt(Token* T) {
    this->is_applied = false;
    this->args = T;
};

void GetTypeSt::apply() {
    this->is_applied = true;
    if (this->args->cat != TYPE) {
        error("waited for the type description statement, got \'" + this->args->value +"\'", "Parser");
    }
    ObjectType* ret;
    if (this->args->value == "bytes") {
        if (this->args->right->cat != TYPE) {
            error("waited for the type length after expression \'" + this->args->value + "\'", "Parser");
        }
        ret = new ObjectType(byte_type, std::stoi(this->args->right->value));
    } else if (this->args->value == "string") {
        if (this->args->right->cat != TYPE) {
            error("waited for the type length after expression \'" + this->args->value + "\'", "Parser");
        }
        ret = new ObjectType(str_type, std::stoi(this->args->right->value));
    } else if (this->args->value == "int32") {
        ret = new ObjectType(int_type);
    } else if (this->args->value == "bool") {
        ret = new ObjectType(bool_type);
    } else {
        error("unknown type: " + this->args->value, "Type");
    };
    this->result = Output((void*) ret, "ObjectType");
};