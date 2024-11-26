#include "GenericObject.h"
#include <string>
GenericObject::GenericObject(int x, ObjectType t): type(t) {
    if (t.type_name == int_type) {
        this->value = (void*) new int(x);
    } else if (t.type_name == bool_type) {
        this->value = (void*) new bool(x);
    } else if (t.type_name == null_type) {
        this->value = 0;
        this->type = ObjectType(null_type);
    } else {
        error("tried to cast boolean/integer value " + std::to_string(x) + " to " + t.type_str(), "Value");
    }
}

GenericObject::GenericObject(std::string S, ObjectType t) {
    //std::cerr << "Hello there, " + S + " " + t.type_str() + "\n";
    if (t.type_name == str_type) {
        if (S.size() > t.length) {
            error("the string \'" + S + "\' is too long for the type \'" + t.type_str() +"\'", "Value");
        }
        this->value = (void*) new std::string(S);
        this->type = t;
    } else if (t.type_name == byte_type) {
        if ((S.size() > 1) && S[0] == '0' && S[1] == 'x') {
            int l = (S.size() + (S.size()%2) - 2)/2;
            char* x = new char[l];
            if (S.size() % 2 == 1) {
                for (int i = l-1; i > -1; i--) {
                    char a = S[2 + 2*i];
                    char b = S[1 + 2*i];
                    if (std::isdigit(a)) {
                        a = a - '0';
                    } else {
                        a = a - 'a' + 10;
                    }

                    if (std::isdigit(b)) {
                        b = b - '0';
                    } else {
                        if (b != 'x') {
                            b = b - 'a' + 10;
                        } else b = 0;
                    } 
                    x[i] = (a + 16*b); 
                    //std::cerr << "x[" << i << "] = " << (int) (x[i]) << ", a = " <<  S[2 + 2*i] << ", b = " << S[1 + 2*i] << "\n";
                }
            } else {
                for (int i = l-1; i > -1; i--) {
                    char a = S[3 + 2*i];
                    char b = S[2 + 2*i];
                    if (std::isdigit(a)) {
                        a = a - '0';
                    } else {
                        a = a - 'a' + 10;
                    }

                    if (std::isdigit(b)) {
                        b = b - '0';
                    } else {
                        if (b != 'x') {
                            b = b - 'a' + 10;
                        } else b = 0;
                    } 
                    x[i] = (a + 16*b); 
                    //std::cerr << "x[" << i << "] = " << (int) (x[i]) << ", a = " <<  S[3 + 2*i] << ", b = " << S[2 + 2*i] << "\n";
                }
            }
            
            
            this->value = x;
            if (t.length < l) {
                error("the byte sequence \'" + S + "\' is too long for the type \'" + t.type_str() +"\'", "Value");
            }
            this->type = t;
        } else {
            char* x = new char[S.size()];
            for (int i = 0; i < S.size(); i++) {
                x[i] = S[i];
            }
            if (t.length < S.size()) {
                error("the byte sequence \'" + S + "\' is too long for the type \'" + t.type_str() +"\'", "Value");
            }
            this->value = x;
            this->type = t;
        }
    } else if (t.type_name == null_type) {
            this->value = 0;
            this->type = ObjectType(null_type);
    } else {
        error("tried to cast string/byte value \"" + S + "\" to " + t.type_str(), "Value");
    }
}

GenericObject::GenericObject(ObjectType t): type(t) {
		switch (t.type_name) {
		case null_type:
			this->value = nullptr;
			break;
		case int_type:
			this->value = (void*) new int();
			break;

		case bool_type:
			this->value = (void*) new bool(0);
			break;

		case str_type:
			this->value = (void*) new std::string();
			break;

		case byte_type:
			this->value = (void*) new int[t.length];
            for (int i = 0; i < t.length; i++) {
                ((int*) this->value)[i] = 0;
            }
        	//memset(this->value, 0, type.length);
			break;

		default:
			error("unknown type " + std::to_string(this->type.type_name) + " used in \"GenericObject(ObjectType t)\"", "Type");
		}
	}

GenericObject::GenericObject(): value() {
		type.type_name = null_type;
		this->value = nullptr;
}

std::string GenericObject::get_string() {
    return *((std::string*) value);
}

int GenericObject::get_int() {
    return *((int*) value);
}

std::string GenericObject::get_byte() {
    std::stringstream ss;
    ss << "0x";
    for (int i = 0; i < type.length; i++) {
        int x = ((char*) value)[i];
        x = x&255;
        ss << std::hex << x;
    }
    return ss.str();
}

std::string GenericObject::get_byte_dbg() {
    std::stringstream ss;
    for (int i = 0; i < type.length-1; i++) {
        char y = ((char*) value)[i];
        ss << (int) y + (y > 0 ? 0 : 256);
        ss << ",";
    }
    char y = ((char*) value)[type.length - 1];
    ss << (int) (y) + (y > 0 ? 0 : 256);
    return ss.str();
}

bool GenericObject::get_bool() {
    return *((bool *) this->value);
}

std::string GenericObject::to_str() {
    switch (this->type.type_name) {
    case null_type:
        return "NULL";
        break;
    case int_type:
        return std::to_string(this->get_int());
        break;
    case str_type:
        return "\"" + this->get_string() + "\"";
        break;
    case bool_type:
        return this->get_bool() ? "true" : "false";
        break;
    case byte_type:
        return this->get_byte();
        break;
    default:
        error("unknown type " + std::to_string(this->type.type_name) + " used in \"to_str\"", "Type");
    }
}

std::string GenericObject::to_str_dbg() {
    switch (this->type.type_name) {
    case null_type:
        return "0";
        break;
    case int_type:
        return std::to_string(this->get_int());
        break;
    case str_type:
        return this->get_string();
        break;
    case bool_type:
        return std::to_string(this->get_bool());
        break;
    case byte_type:
        return this->get_byte_dbg();
        break;
    default:
        error("unknown type " + std::to_string(this->type.type_name) + " used in \"to_str_dbg\"", "Type");
    }
}

std::string GenericObject::debug_info() {
    switch (this->type.type_name) {
    case null_type:
        return "NULL";
        break;
    case int_type:
        return std::to_string(this->get_int()) + " (" + this->type.type_str() + ")";
        break;
    case bool_type:
        return std::to_string(this->get_bool()) + " (" + this->type.type_str() + ")";
        break;
    case str_type:
        return "\"" + this->get_string() + "\"(" + this->type.type_str() + ")";
        break;
    case byte_type:
        return this->get_byte() + " (" + this->type.type_str() + ")";

        break;
    default:
        error("unknown type " + std::to_string(this->type.type_name) + " used in \"debug_info\"", "Type");
    }
}

void GenericObject::print(std::ostream& os) {
    os << this->to_str();
}

GenericObject GenericObject::operator= (GenericObject other) {
    //std::cerr << "\noperator= entered ";
    this->value = other.value;
    this->type = other.type;
    return  *this;
}; 

bool GenericObject::is_null () {
    return this->type.type_name == null_type;
}

GenericObject create_object(std::string S, ObjectType type_p_length) {
    ObjectTypeName type = type_p_length.type_name;
    GenericObject ret;
    switch (type)
    {
    case int_type:
        ret = GenericObject(std::stoi(S), type_p_length);
        break;
    case bool_type:
        if (S == "true") {
            ret = GenericObject(true, type_p_length);
        } else if (S == "false") {
            ret = GenericObject(false, type_p_length);
        } else {
            error("tried to cast " + S + " to bool", "Value");
        }
        break;
    case null_type:
        if (S == "null") {
            ret = GenericObject(0, type_p_length);
        } else {
            error("tried to cast " + S + " to NULL", "Value");
        }
        break;
    case str_type:
        ret = GenericObject(S, type_p_length);
        break;
    case byte_type:
        ret = GenericObject(S, type_p_length);
        break;
    default:
        error("unknown type: " + std::to_string(type), "Type");
        break;
    }
    return ret;
};

GenericObject GenericObject::operator+(GenericObject& other) {
    if (this->type.type_name != other.type.type_name) {
        error("tried to add the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type"); 
    } 
    switch (this->type.type_name) {
        case (int_type):
            return GenericObject(this->get_int() + other.get_int(), ObjectType(int_type));
            break;
        case (str_type):
            return GenericObject(this->get_string() + other.get_string(), ObjectType(str_type, (this->get_string() + other.get_string()).size()));
            break;
        default:
            error("tried to add the objects of types " + this->type.type_str(), "Type");
    }
};

GenericObject GenericObject::operator-(GenericObject& other) {
    if (this->type.type_name != int_type || other.type.type_name != int_type) {
        error("tried to substract the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type"); 
    } 
    return GenericObject(this->get_int() - other.get_int(), ObjectType(int_type));    
};

GenericObject GenericObject::operator*(GenericObject& other) {
    if (this->type.type_name != int_type || other.type.type_name != int_type) {
        error("tried to multiply the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type"); 
    } 
    return GenericObject(this->get_int() * other.get_int(), ObjectType(int_type));
};
GenericObject GenericObject::operator/(GenericObject& other) {
    if (this->type.type_name != int_type || other.type.type_name != int_type) {
        error("tried to divide the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type"); 
    } 
    return GenericObject(this->get_int() / other.get_int(), ObjectType(int_type));
};
GenericObject GenericObject::operator%(GenericObject& other) {
    if (this->type.type_name != int_type || other.type.type_name != int_type) {
        error("tried to divide the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type"); 
    } 
    return GenericObject(this->get_int() % other.get_int(), ObjectType(int_type));
};

bool GenericObject::operator>(GenericObject& other) {
    if (this->type.type_name != other.type.type_name) {
        error("tried to compare two object of types " + this->type.type_str() + " and " + other.type.type_str(), "Type"); 
    } else {
        switch (this->type.type_name)
        {
        case int_type:
            return (this->get_int() > other.get_int()); 
            break;
        case str_type:
            return (this->get_string() > other.get_string()); 
            break;
        case byte_type:
            //std::cerr << this->get_byte() << " " << other.get_byte();
            return (this->get_byte() > other.get_byte());
            break;
        case bool_type:
            return (this->get_bool() > other.get_bool()); 
            break;
        default:
            break;
        }
    }
};

bool GenericObject::operator<(GenericObject& other) {
    return (other > *this);
};
bool GenericObject::operator>=(GenericObject& other) {
    return (!(*this < other));
};
bool GenericObject::operator<=(GenericObject& other) {
    return (!(*this > other));
};
bool GenericObject::operator== (GenericObject other) {
    if (this->type != other.type) {
        return false;
    } else {
        switch (this->type.type_name)
        {
        case int_type:
            return (this->get_int() == other.get_int());
            break;
        case str_type:
            return (this->get_string() == other.get_string());
            break;
        case byte_type:
            return (this->get_byte() == other.get_byte());
            break;
        case bool_type:
            return (this->get_bool() == other.get_bool());
            break;
        default:
            error("tried to compare " + this->type.type_str(), "Type");
            break;
        }
    }
};

bool GenericObject::operator!= (GenericObject other) {
    return !(*this == other);
};

GenericObject GenericObject::operator&& (GenericObject other) {
    if (this->type.type_name != bool_type || other.type.type_name != bool_type) {
        error("tried to use operator && to the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type");
    }
    return (this->get_bool() && other.get_bool(), ObjectType(bool_type));
};

GenericObject GenericObject::operator|| (GenericObject other) {
    if (this->type.type_name != bool_type || other.type.type_name != bool_type) {
        error("tried to use operator || to the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type");
    }
    return (this->get_bool() || other.get_bool(), ObjectType(bool_type));
};

GenericObject GenericObject::operator! () {
    if (this->type.type_name != bool_type) {
        error("tried to use operator ! to the objects of types " + this->type.type_str(), "Type");
    }
    return (!this->get_bool(), ObjectType(bool_type));
};

GenericObject GenericObject::operator^ (GenericObject other) {
    if (this->type.type_name != bool_type ^ other.type.type_name != bool_type) {
        error("tried to use operator ^^ to the objects of types " + this->type.type_str() + " and " + other.type.type_str(), "Type");
    }
    return (this->get_bool() ^ other.get_bool(), ObjectType(bool_type));
};

bool GenericObject::operator&& (bool other) {
    if (this->type.type_name != bool_type) {
        error("tried to use operator && to the objects of types " + this->type.type_str() + " and bool", "Type");
    }
    return (this->get_bool() && other);
};
bool GenericObject::operator|| (bool other) {
    if (this->type.type_name != bool_type) {
        error("tried to use operator || to the objects of types " + this->type.type_str() + " and bool", "Type");
    }
    return (this->get_bool() || other);
};
bool GenericObject::operator^ (bool other) {
    if (this->type.type_name != bool_type) {
        error("tried to use operator ^^ to the objects of types " + this->type.type_str() + " and bool", "Type");
    }
    return (this->get_bool() ^ other);
};

GenericObject::GenericObject(GenericObject x, ObjectType t) {
    this->value = x.value;
    this->type = t;
};
