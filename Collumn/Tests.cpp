#include "Collumn.h"
#include "../Common/Error/Error.h"
#include <cassert>
#include <iostream>

void Collumn_test() {
    Collumn Constr1 ("Int_Collumn_Unique", ObjectType(int_type, 0), false, true);
    Collumn Constr2 ("Bool_Collumn_Key", ObjectType(bool_type), true);
    Collumn Constr3 ("Bool_Collumn_Unique", ObjectType(bool_type), false, true);
    Collumn Constr4 ("Int_Collumn_Auto", ObjectType(int_type), false, false, true);
    Collumn Constr5 ("Byte_Collumn_Default", ObjectType(byte_type, 4), false, false, false, GenericObject({0, 15, 2, 13}, ObjectType(byte_type, 4)));
    Collumn Constr6 ("Byte_Collumn_Unique", ObjectType(byte_type, 4), false, false, false);
    
    try {
        Collumn ConstrErr1 ("Str_Collumn_Auto", ObjectType(str_type, 3), false, false, true);
    } catch (Message M) {
        assert(M.text == "[ERROR] AutoincrementError: creation of the autoincrement collumn \'Str_Collumn_Auto\' with non-int type STR[3]");
    }

    try {
        Constr6.add(GenericObject(42, ObjectType(int_type)));
    } catch (Message M) {
        assert(M.text == "[ERROR] TypeError: wrong type INT for collumn \'Byte_Collumn_Unique\' with type BYTE[4]");
    }

    Constr1.add(GenericObject(42, ObjectType(int_type)));
    try {
        Constr1.add(GenericObject(42, ObjectType(int_type)));
    } catch (Message M) {
        assert(M.text == "[ERROR] ValueError: addition of existing value 42 to unique collumn \'Int_Collumn_Unique\'");
    }

    assert(Constr1.get(std::vector<int>(1))[0] == GenericObject(42, ObjectType(int_type)));
    Constr4.add();   
    assert(Constr4.get(std::vector<int>(1))[0] == GenericObject(0, ObjectType(int_type)));
    Constr5.add();
    assert(Constr5.get(std::vector<int>(1))[0] == GenericObject({0, 15, 2, 13}, ObjectType(byte_type, 4)));
    
    //Constr1.nullify(0);
    //assert(Constr1.get(std::vector<int>(0))[0].is_null());

    std::cerr << "[TESTS] Collumn tests completed successfully\n"; 
}