#include "../../Common/Error/Error.h"
#include "../../ObjectType/Tests.cpp"
#include "../../GenericObject/Tests.cpp"
#include "../../Collumn/Tests.cpp"
#include "../../Table/Tests.cpp"
#include <cassert>

void implementation_tests() {
    ObjectType_test();
    GenericObject_test();
    Collumn_test();
    Table_test();
}



// int main() {
//     try {
//         //Parcer_tests();
//         ObjectType_test();
//         GenericObject_test();
//         Collumn_test();
//         Table_test();
//     } catch (Message M) {
//         std::cerr << M.text << "\n";
//         exit(-1);
//     }
//     return 0;
//}