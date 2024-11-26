#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include "../ObjectType/ObjectType.h"
#include <sstream>
#include <cstring>
#include <iostream>

class GenericObject {
public:
	ObjectType type;
	void* value;

	GenericObject(GenericObject x, ObjectType t);
	GenericObject(int x, ObjectType t);

	//GenericObject(bool x, ObjectType t);

	GenericObject(std::string x, ObjectType t);

	// template <typename T>
	// GenericObject(T v, ObjectType t): type(t) {
	// 	error("unknown variable in GenericObject creation", "Value");
	// };

	
	GenericObject(ObjectType t);

	GenericObject();

	std::string get_string();

	int get_int();

	std::string get_byte();

	std::string get_byte_dbg();

	bool get_bool();

	GenericObject operator= (GenericObject other);

	//GenericObject operator= (GenericObject& other);


	bool is_null ();

	std::string to_str();

	std::string to_str_dbg();

	std::string debug_info();

	void print(std::ostream& os = std::cout);
	
	GenericObject operator+(GenericObject& other);
	GenericObject operator-(GenericObject& other);
	GenericObject operator*(GenericObject& other);
	GenericObject operator/(GenericObject& other);
	GenericObject operator%(GenericObject& other);

	bool operator>(GenericObject& other);
	bool operator<(GenericObject& other);
	bool operator>=(GenericObject& other);
	bool operator<=(GenericObject& other);
	bool operator== (GenericObject other);
	bool operator!= (GenericObject other);

	GenericObject operator&& (GenericObject other);
	GenericObject operator|| (GenericObject other);
	GenericObject operator! ();
	GenericObject operator^ (GenericObject other);

	bool operator&& (bool other);
	bool operator|| (bool other);
	bool operator^ (bool other);
};

GenericObject create_object(std::string S, ObjectType type);
#endif