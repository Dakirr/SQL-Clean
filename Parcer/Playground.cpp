#include "Tokenizer.h"



int main () {
    try {
        print(prepare("(1) \"(\" \"]\" 234,int32, \"2\" (\"3\", \"}\" \")\") {\"}\"} {-4} || |5| NuLl byte[6] |()|(123) 1 = 2 3 + 4 3 - 4 >= create TABLE Select 0X12356 fdfFFsD"));
    } catch (Message M) {
        std::cerr << M.text << "\n";
    }
}

