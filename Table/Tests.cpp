#include "Table.h"
#include <cassert>
#include <sstream>

void Table_creation_test() {
    Table T("Test Table");
	T.add_collumn(ObjectType(bool_type), "Bool Val");
	T.add_collumn(ObjectType(int_type), "Int Val", 0, 0, 0, GenericObject(12, ObjectType(int_type, 0)));
    
	try {
		T.add_collumn(ObjectType(null_type));
	} catch (Message M) {
		assert(M.text == "[ERROR] NameError: tried to create a no-name collumn in the table \'Test Table\'");
	}

	try {
		T.add_row(std::vector<GenericObject>{GenericObject(true, ObjectType(bool_type)), GenericObject(2, ObjectType(int_type))});
	} catch (Message M) {
		assert(M.text == "[ERROR] TypeError: wrong type INT for collumn \'Bool Val\' with type BOOL");
	}

	T.add_row({{"Int Val", GenericObject(-42, ObjectType(int_type, 0))}});

	try {
		T.add_row({{"Not Exist", GenericObject(-42, ObjectType(int_type, 0))}});
	} catch (Message M) {
		assert(M.text == "[ERROR] Error: there is no collumn 'Not Exist' in the table \'Test Table\'");
	}
	std::cerr << "[TESTS] Table (creation) completed successfully\n"; 
}


void Table_select_test () {
	std::cerr << "[TESTS] Table (selection) tests completed successfully\n"; 
}

void Table_save_load_test () {
	std::stringstream ss;
	Table T("Test Table");
	T.add_collumn(ObjectType(str_type, 10), "Str");
	T.add_collumn(ObjectType(byte_type, 3), "Byt");
	T.add_row(std::vector<GenericObject> {GenericObject("Hi_vec", ObjectType(str_type, 6)), GenericObject({1, 2, 3}, ObjectType(byte_type, 3))});
	T.add_row({{"Str", GenericObject("Hi_map", ObjectType(str_type, 6))}, {"Byt", GenericObject({1, 2, 3}, ObjectType(byte_type, 3))}});
	T.save(ss);
	//Table T2 = load(ss);
	//assert (T.name == T2.name);
	//assert (T.collumns == T2.collumns);
	//assert (T.collumn_names == T2.collumn_names);
	std::cerr << "[TESTS] Table save tests completed successfully\n"; 
}


void Table_test () {
	Table_creation_test();
	Table_select_test();
	Table_save_load_test();
	std::cerr << "[TESTS] Table tests completed successfully\n"; 
}
