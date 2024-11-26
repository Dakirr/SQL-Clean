#include "Collumn.h"

Collumn::Collumn(std::string name, ObjectType type, bool is_key, bool is_unique, bool is_autoincrement, GenericObject def) {
    this->cells = std::vector<GenericObject>();
    this->type = type;
    this->name = name;
    this->is_key = is_key;
    this->is_unique = is_unique;
    this->is_autoincrement = is_autoincrement;
    this->def = GenericObject(def, type);
    this->ID = 0;
    if (this->is_autoincrement && (this->type.type_name != int_type)) {
        error("creation of the autoincrement collumn \'" + this->name + "\' with non-int type " + this->type.type_str(), "Autoincrement");
    }
}

bool Collumn::check_unique(GenericObject value, bool fatal) {
    if ((this->is_unique || this->is_key)) {
        bool flg = false;
        for (int i = 0; i < this->cells.size(); i++) {
            if (this->cells[i] == value) {
                flg = true;
            }
        }
        if (fatal && flg) {
            error("addition of existing value " + value.to_str() + " to unique collumn \'" + this->name + "\'", "Value");
        }
        if (flg) {
            return false;
        }
        return true;
    } else {
        return true;
    }
}

bool Collumn::check_autoincrement() {
    return (this->is_autoincrement);
}

bool Collumn::check_default() {
    return (this->type.type_name == this->def.type.type_name);
}

void Collumn::add(GenericObject value) {
    if (this->type.type_name == value.type.type_name) {
        if (this->type.type_name != str_type && this->type.type_name != byte_type) {
            check_unique(value);
            this->cells.push_back(value);
            if (check_autoincrement()) {
                this->ID = value.get_int();
            }
        } else if (this->type.type_name == str_type && this->type.length >= value.get_string().size()) {
            check_unique(value);
            value.type.length = this->type.length;
            this->cells.push_back(value);
            if (check_autoincrement()) {
                this->ID = value.get_int();
            }
        } else if (this->type.type_name == byte_type && this->type.length == value.type.length) {
            check_unique(value);
            this->cells.push_back(value);
            if (check_autoincrement()) {
                this->ID = value.get_int();
            }
        } else {
            error("incorrect sized object " + value.debug_info() + " with length "\
                    + std::to_string(value.get_string().size()) + " for collumn \"" \
                    + this->name + "\" with type " + this->type.type_str(), "Type");
        }
    } else {
        error("wrong type " + value.type.type_str() + " for collumn \'" + this->name + "\' with type " + this->type.type_str(), "Type");
    }
}


void Collumn::add() {
    if (check_autoincrement()) {
        this->add(GenericObject(this->ID, this->type));
        ID += 1;
        return;
    }
    if (check_default()) {
        this->add(this->def);    
        return;
    }
    
    error("there is no default value for non-autoincrement collumn \'" + this->name + "\'", "Value", 0);
    this->add(GenericObject(this->type));
}

void Collumn::del(int i) {
    if (i < 0) {
        this->cells.pop_back();
    } else {
        this->cells.erase(this->cells.begin() + i);
    }
}

std::string Collumn::debug_flags() {
    return std::to_string(this->is_key) + ";" + std::to_string(this->is_unique) + ";" + std::to_string(this->is_autoincrement) + ";";
}

std::vector<GenericObject> Collumn::get (std::vector<int> indexes) {
    std::vector<GenericObject> ret;
    for (int i = 0; i < indexes.size(); i++) {
        ret.push_back(this->cells[indexes[i]]);
    }
    return ret;
}

Collumn copy (Collumn* C) {
    return Collumn(C->name, C->type, C->is_key, C->is_unique, C->is_autoincrement, C->def);
}

Collumn Collumn::operator= (Collumn other) {
    //std::cerr << "\noperator= of collumn entered";
    this->cells = other.cells;
    this->name = other.name;
    this->type = other.type;
    this->is_key = other.is_key;
    this->is_unique = other.is_unique;
    this->is_autoincrement = other.is_autoincrement;
    this->ID = other.ID;
    return *this;
}

bool Collumn::operator== (Collumn other) {
    bool are_equal = (this->name == other.name) && (this->type == other.type);
    are_equal = (are_equal && (this->is_key == other.is_key) && (this->is_unique == other.is_unique) && (this->is_autoincrement == other.is_autoincrement));
    are_equal = are_equal && (this->def == other.def);
    if (this->cells.size() != other.cells.size()) {
        return false;
    } else {
        for (int i = 0; i < other.cells.size(); i++) {
            are_equal = are_equal && (this->cells[i] == other.cells[i]);
        }
    }
    return are_equal;
}

void Collumn::DEBUG_PRINT() {
    std::cerr << "\n" << this->name << " [";
    for (int i = 0; i < this->cells.size(); i++) {
        std::cerr << this->cells[i].to_str() << ", ";
    }
    std::cerr << "]\n";
}