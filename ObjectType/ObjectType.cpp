#include "ObjectType.h"

ObjectType::ObjectType(ObjectTypeName type_name, int length) {
    this->type_name = type_name;
    this->length = length;
}

ObjectType::ObjectType() {
    this->type_name = null_type;
    this->length = 0;
}

ObjectType::ObjectType(const ObjectType& other) {
    this->type_name = other.type_name;
    this->length = other.length;
}

void ObjectType::operator=(ObjectType other) {
    this->type_name = other.type_name;
    this->length = other.length;
}

bool ObjectType::operator==(ObjectType other) {
    if (this->type_name == other.type_name) {
        if (this->type_name == int_type || this->type_name == bool_type) {
            return true;
        } else if (this->type_name == null_type) {
            return false;
        } else if (this->type_name == str_type || this->type_name == byte_type) {
            return (this->length == other.length);
        } else {
            error("invalid type: " + std::to_string(this->type_name), "Type");
        }
    } 
    return false;
}

bool ObjectType::operator!=(ObjectType other) {
    return !(this->operator==(other));
}

std::string ObjectType::type_str() {
    switch (this->type_name) {
	case null_type:
		return "NULL";
	case int_type:
		return "INT";
	case bool_type:
		return "BOOL";
	case str_type:
		return "STR[" + std::to_string(this->length) + "]";
	case byte_type:
		return "BYTE[" + std::to_string(this->length) + "]";
	default:
		error("unknown type " + std::to_string(this->type_name) + " used in \"type_str\"", "Type");
	}
}

std::string ObjectType::type_dbg() {
    switch (this->type_name) {
	case null_type:
		return std::to_string(this->type_name) + ";0;";
	case int_type:
		return std::to_string(this->type_name) + ";0;";
	case bool_type:
		return std::to_string(this->type_name) + ";0;";
	case str_type:
		return std::to_string(this->type_name) + ";" + std::to_string(this->length) + ";";
	case byte_type:
		return std::to_string(this->type_name) + ";" + std::to_string(this->length) + ";";
	default:
		error("unknown type " + std::to_string(this->type_name) + " used in \"type_dbg\"", "Type");
	}
}
