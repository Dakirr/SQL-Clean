#include "./CreateTableSt/CreateTableSt.h"
#include <cassert>
#include "../Common/Test/Test.cpp"
#include "Parse.h"
void GetTypeSt_test() {
    Token* p = prepare("int32 striNg[2] ByTeS[32] BooL");
    //print(p);
    GetTypeSt IntSt(p->get(1));
    GetTypeSt StrSt(p->get(2));
    GetTypeSt ByteSt(p->get(4));
    GetTypeSt BoolSt(p->get(6));
    assert(*(IntSt.get().get(ObjectType())) == ObjectType(int_type));
    assert(*(StrSt.get().get(ObjectType())) == ObjectType(str_type, 2));
    assert(*(ByteSt.get().get(ObjectType())) == ObjectType(byte_type, 32));
    assert(*(BoolSt.get().get(ObjectType())) == ObjectType(bool_type));
    std::cerr << "[TESTS] GetTypeStatetement tests completed succesfully\n";
}

void GetValueSt_test() {
    Token* p = prepare("123 \"Hello\" 0x12345 \"abc\" true null");
    GetValueSt IntSt (p->get(1), ObjectType(int_type));
    GetValueSt StrSt(p->get(2), ObjectType(str_type, 5));
    GetValueSt ByteStHex(p->get(3), ObjectType(byte_type, 3));
    GetValueSt ByteStStr(p->get(4), ObjectType(byte_type, 3));
    GetValueSt BoolSt(p->get(5), ObjectType(bool_type));
    GetValueSt NullSt(p->get(6), ObjectType(null_type));
    assert(*(IntSt.get().get(GenericObject())) == GenericObject(123, ObjectType(int_type)));
    assert(*(StrSt.get().get(GenericObject())) == GenericObject("Hello", ObjectType(str_type, 5)));
    assert(*(ByteStHex.get().get(GenericObject())) == GenericObject("0x12345", ObjectType(byte_type, 3)));
    assert(*(ByteStStr.get().get(GenericObject())) == GenericObject("abc", ObjectType(byte_type, 3)));
    assert(*(BoolSt.get().get(GenericObject())) == GenericObject(true, ObjectType(bool_type)));
    assert((NullSt.get().get(GenericObject()))->type.type_name == null_type);
    std::cerr << "[TESTS] GetValueStatetement tests completed succesfully\n";   
}

void CreateCollumnSt_test() {
    Token* p = prepare("{key, unique} id: string[5] = \"42\"");
    CreateCollumnSt St(p->right);
    assert(*(St.get().get(Collumn())) == Collumn("id", ObjectType(str_type, 5), true, true, false, GenericObject("42", ObjectType(str_type, 5))));
    std::cerr << "[TESTS] CreateCollumn tests completed succesfully\n";   
}

void CreateTableSt_test() {
    Token* p = prepare("create table users ({key, autoincrement} id :int32, {unique} login: string[32], password_hash: bytes[8], is_admin:bool = false)");
    CreateTableSt St(p->right->right->right);
    St.apply();
    Table *T = (St.get().get(Table("s")));
    Table NT = Table("users");
    NT.add_collumn(ObjectType(int_type), "id", true, false, true);
    NT.add_collumn(ObjectType(str_type, 32), "login", false, true, false);
    NT.add_collumn(ObjectType(byte_type, 8), "password_hash");
    NT.add_collumn(ObjectType(bool_type), "is_admin", false, false, false, GenericObject(false, ObjectType(bool_type)));
    assert(*T == NT);
    std::cerr << "[TESTS] CreateTable tests completed succesfully\n";   
}

void parcer_tests() {
    GetTypeSt_test();
    GetValueSt_test();
    CreateCollumnSt_test();
    CreateTableSt_test();
}

int main () {
    try {
        implementation_tests();
        parcer_tests();
        //std::string x = "CrEaTe table users ({key, autoincrement} id :int32, {unique} login: string[32], password_hash: bytes[8], is_admin:bool = false)";
        //std::string y1 = "insert (,\"vasya\", 0xdeadbeefdeadbeef) to users";
        //std::string y2  = "insert (login = \"Petya\", password_hash = 0xbeefdeaddeadbeef) to users";
        std::cout << "\n\nWaiting for input (Create and Insert are implemented)\n"; 
        std::string x;
        while (true) {
            std::getline(std::cin, x);
            parse(x);
        }
    } catch (Message M) {
        std::cerr << M.text << "\n";
    }
}