#ifndef OBJECT_TYPE_H
#define OBJECT_TYPE_H

#include "../Common/Error/Error.h"

typedef enum {
	null_type,
	int_type,
	bool_type,
	byte_type,
	str_type,
} ObjectTypeName;

class ObjectType {
public:
	ObjectTypeName type_name;
	int length;

	ObjectType(ObjectTypeName type_name, int length = 0);

	ObjectType();

	ObjectType(const ObjectType& other);

	void operator=(ObjectType other);

	bool operator==(ObjectType other);

	bool operator!=(ObjectType other);

	std::string type_str();

	std::string type_dbg();
};

#endif