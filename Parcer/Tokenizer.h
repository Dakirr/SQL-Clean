#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include "../Common/Error/Error.h"
#include "../ObjectType/ObjectType.h"

typedef enum {
    ND,
    UNK,
    UNF,
    HEAD,
    KEY, 
    OP,
    ID, 
    NUM,
    STR,
    BYTE,
    LOG,
    NONE,
    TYPE,
    BAR,
    BR,
    CBR,
    SBR,
    SYNT
} TokenCategory;

extern std::set<TokenCategory> simplifiable;
extern std::set<TokenCategory> valueable;
extern std::map<TokenCategory, ObjectTypeName> TokenToType;
extern std::set<std::string> types;
extern std::set<std::string> u_operators;
extern std::set<std::string> keywords;

class Token {
    public:
    Token* left;
    Token* right;
    TokenCategory cat;
    std::string value;

    Token (TokenCategory c = ND);
    Token(std::string v, TokenCategory c, Token* l = nullptr, Token* r = nullptr);
    Token* add(std::string v, TokenCategory c, bool is_left = false);
    Token* add(Token* other, bool is_left = false);
    Token* del ();
    bool is_bin_simplifyable();
    Token* replace (Token* first, Token* last);
    Token* get (int ind);
    void identify ();
};
std::string display(TokenCategory cat);
std::pair<Token*, Token*> split_binary (std::string input);
Token* prepare (std::string input);
void print(Token* x);


#endif