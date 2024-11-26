#include "GenericObject.h"
#include <cassert>
#include <iostream>

void GenericObject_general() {
    GenericObject Constr1 (3, ObjectType(int_type, 1));
    std::string x = "TEST_STRING";
    GenericObject Constr2 (x, ObjectType(str_type, 13));
    GenericObject Constr3 (ObjectType(bool_type, 0));
    GenericObject Constr4 = GenericObject();
    char *y = new char[4];
    y[0] = 3; y[1] = 1; y[2] = 15; y[3] = 3;
    GenericObject Constr5 (y, ObjectType(byte_type, 4));

    assert (Constr1 == Constr1);
    assert (Constr3 == Constr3);
    assert (Constr2 == Constr2);
    assert (Constr4 != Constr4);
    assert (Constr5 == Constr5);
    
    assert (Constr1.get_int() == 3);
    assert (Constr2.get_string() == "TEST_STRING");
    assert (Constr3.get_bool() == false);
    assert (Constr5.get_byte() == "0x31f3");

    assert (Constr1.to_str() == "3");
    assert (Constr2.to_str() == "\"TEST_STRING\"");
    assert (Constr3.to_str() == "false");
    assert (Constr4.to_str() == "NULL");
    assert (Constr5.to_str() == "0x31f3");

    assert(Constr4.is_null());
    
    std::cerr << "[TESTS] GenericObject (general) tests completed successfully\n"; 
}

void GenericObject_create_object() {
    GenericObject IntObj = create_object("42", ObjectType(int_type));
    GenericObject StrObj = create_object("sTR!ng", ObjectType(str_type, 6));
    GenericObject BoolObj = create_object("true", ObjectType(bool_type));
    GenericObject ByteObjHex = create_object("0x112a45f", ObjectType(byte_type, 4));
    GenericObject ByteObjStr = create_object("!2CTev", ObjectType(byte_type, 6));

    assert (IntObj.get_int() == 42);
    assert (StrObj.get_string() == "sTR!ng");
    assert (BoolObj.get_bool() == true);
    assert (ByteObjHex.get_byte_dbg() == "1,18,164,95");
    std::cerr << ByteObjStr.get_byte();
    assert (ByteObjStr.get_byte() == "0x213243546576");


    std::cerr << "[TESTS] GenericObject (create_object) tests completed successfully\n"; 
}

void GenericObject_operations_object() {
    GenericObject int3 (3, ObjectType(int_type, 1));
    GenericObject int9 (9, ObjectType(int_type, 0));
    assert(int9 > int3);
    assert(int3 <= int3);
    assert(int9 == int9);
    assert(int9 != int3);
    assert(int9 == int3+int3+int3);
    assert(int9 == int3*int3);
    assert(int3 == int9/int3);

    GenericObject str_aa ("aa", ObjectType(str_type, 2));
    GenericObject str_ab ("ab", ObjectType(str_type, 2));
    GenericObject str_aaab ("aaab", ObjectType(str_type, 4));
    assert(str_ab > str_aa);
    assert(str_aa <= str_aaab);
    assert(str_aa <= str_aa);
    assert(str_aa == str_aa);
    assert(str_aa != str_ab);
    assert(str_aa + str_ab == str_aaab);

    GenericObject byte_aa ("0x0a0a", ObjectType(byte_type, 2));
    GenericObject byte_fa ({15, 10}, ObjectType(byte_type, 2));
    assert(byte_fa != byte_aa);
    assert(byte_fa >= byte_aa);
    assert(byte_fa > byte_aa);

    GenericObject bool_1 (true, ObjectType(bool_type, 2));
    GenericObject bool_0 (0, ObjectType(bool_type));
    assert(bool_0 != bool_1);
    assert(bool_1 >= bool_0);
    assert(bool_1 ^ bool_1 == bool_0);
    assert(bool_1 && bool_1 == bool_1);
    

    std::cerr << "[TESTS] GenericObject (operators) tests completed successfully\n"; 
}

void GenericObject_test() {
    GenericObject_general();
    GenericObject_create_object();
    GenericObject_operations_object();
    std::cerr << "[TESTS] GenericObject tests completed successfully\n"; 
}

// int main() {
//     try {
//         GenericObject_test();
//         return 0;
//     } catch (Message M) {
//         std::cerr << M.text;
//     }
//}