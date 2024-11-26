#include "GetValueSt.h"

GetValueSt::GetValueSt(Token* T, GetTypeSt S) {
    this->is_applied = false;
    this->args = T;
    this->type = *(S.get()).get(ObjectType());
};

GetValueSt::GetValueSt(Token* T, Output S) {
    this->is_applied = false;
    this->args = T;
    this->type = *(S.get(ObjectType()));
};

GetValueSt::GetValueSt(Token* T, ObjectType S) {
    this->is_applied = false;
    this->args = T;
    this->type = S;
};

void GetValueSt::apply () {
    if (valueable.find(this->args->cat) == valueable.end()) {
        error(this->args->value + " is not a correct value", "Value");
    }
    this->is_applied = true;
    GenericObject* G = new GenericObject;
    *G = create_object(this->args->value, this->type);
    this->result = Output((void*) G, "GenericObject");    
}

     

