#include "ObjectType.h"
#include <cassert>
#include <iostream>
void ObjectType_test() {
    ObjectType NullObjType (null_type, 0);
    ObjectType IntObjType  (int_type, 0);
    ObjectType Int1ObjType (int_type, 1);
    ObjectType BoolObjType (bool_type, 0);
    ObjectType Str1ObjType (str_type, 1);
    ObjectType Str3ObjType (str_type, 3);
    ObjectType Byte1ObjType (byte_type, 1);
    ObjectType Byte3ObjType (byte_type, 3);
    
    assert (NullObjType.type_name == null_type);
    assert (IntObjType.type_name == int_type);
    assert (BoolObjType.type_name == bool_type);
    assert(Str1ObjType.type_name == str_type);
    assert(Byte1ObjType.type_name == byte_type);

    assert (NullObjType != NullObjType);
    assert (IntObjType == IntObjType);
    assert (IntObjType == Int1ObjType);
    assert (BoolObjType == BoolObjType);
    assert (Str1ObjType == Str1ObjType);
    assert (Str1ObjType != Str3ObjType);
    assert (Byte1ObjType == Byte1ObjType);
    assert (Byte1ObjType != Byte3ObjType);

    assert (NullObjType != IntObjType);
    assert (BoolObjType != Str1ObjType);
    assert (Str3ObjType != NullObjType);
    assert (Byte1ObjType != Int1ObjType);

    assert (NullObjType.type_str() == "NULL");
    assert (IntObjType.type_str() == "INT");
    assert (Int1ObjType.type_str() == "INT");
    assert (BoolObjType.type_str() == "BOOL");
    assert (Str1ObjType.type_str() == "STR[1]");
    assert (Byte3ObjType.type_str() == "BYTE[3]");
    
    std::cerr << "[TESTS] ObjectTypes tests completed successfully \n"; 
}