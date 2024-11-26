#include "Statement.h"


Output Output::operator= (Output other) {
    this->out = other.out;
    this->object = other.object;
    return this;
};

Output& Statement::get() {
    if (!is_applied) {
        this->apply();
        this->is_applied = true;
    }
    return result;
}

