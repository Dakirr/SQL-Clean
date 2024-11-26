#ifndef COLLUMN_H
#define COLLUMN_H

#include "../GenericObject/GenericObject.h"
#include <vector>
#include <algorithm>

class Collumn {
public:
	std::string name;
	std::vector<GenericObject> cells;
	ObjectType type;
	bool is_key, is_unique, is_autoincrement;
	int ID;
	GenericObject def;

	Collumn() = default;

	Collumn(std::string name, ObjectType type, bool is_key = 0, bool is_unique = 0, bool is_autoincrement = 0, GenericObject def = GenericObject());

	bool check_unique(GenericObject value, bool fatal = true);

	bool check_autoincrement();
    
    bool check_default();
    
	void add(GenericObject value);

	template <typename T>
	void add(T value) {
		this->add(GenericObject(value, this->type));
	}

	void add();

	void del(int i = -1);

	void nullify(int i);

	std::string debug_flags();

    std::vector<int> find (GenericObject value);
    
    std::vector<GenericObject> get (std::vector<int> indexes);

	Collumn operator= (Collumn other);

	bool operator== (Collumn other);

	void DEBUG_PRINT();
};

Collumn copy (Collumn* C);

#endif
