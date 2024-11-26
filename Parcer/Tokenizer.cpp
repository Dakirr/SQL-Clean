#include "Tokenizer.h"

std::set<TokenCategory> simplifiable {ND, UNK, UNF};
std::set<TokenCategory> valueable {NONE, STR, BYTE, NUM, LOG};
std::map<TokenCategory, ObjectTypeName> TokenToType ({{NONE, null_type}, {STR, str_type}, {BYTE, byte_type}, {NUM, int_type}, {LOG, bool_type}});
std::set<std::string> types {"int32", "bool", "string", "bytes"};
std::set<std::string> u_operators {"=", "<", ">", "<=", ">=", "!=", "+", "-", "*", "/", "%", "&&", "||", "!", "^^"};
std::set<std::string> keywords {"create", "table", "insert", "to", "select", "from", "where", "update", "set",\
                                "delete", "join", "on", "unordered", "ordered", "index", "by"};

std::string to_lower (std::string input) {
    std::string ret;
    int sz = input.size();
    for (int i = 0; i < sz; i++) {
        ret += std::tolower(input[i]);
    }
    return ret;
}

std::string display(TokenCategory cat) {
    switch (cat) {
        case ND:
            return "ND";
        case UNK:
            return "UNK";
        case UNF:
            return "UNF";
        case HEAD:
            return "HEAD";
        case KEY:
            return "KEY";
        case OP:
            return "OP";
        case ID:
            return "ID";
        case NUM:
            return "NUM";
        case STR:
            return "STR";
        case NONE:
            return "NONE";
        case BYTE:
            return "BYTE";
        case TYPE:
            return "TYPE";
        case LOG:
            return "LOG";
        case BAR:
            return "BAR";
        case BR:
            return "BR"; 
        case CBR:
            return "CBR";
        case SBR:
            return "SBR";
        case SYNT:
            return "SYNT";
        default:
            error("unknown type of token: " + std::to_string(cat), "Tokenization");
    }
}

Token::Token (TokenCategory c) {
    left = nullptr;
    right = nullptr;
    cat = c;
    value = "";
}

Token::Token(std::string v, TokenCategory c, Token* l, Token* r) {
    left = l;
    right = r;
    value = v;
    cat = c;
}

Token* Token::add(std::string v, TokenCategory c, bool is_left) {
    Token* x = new Token(v, c);
    return this->add(x, is_left);
}

Token* Token::add(Token* other, bool is_left) {
    if (is_left) {
        Token* tmp = this->left;
        this->left = other;
        other->left = tmp;
        other->right = this;
    } else {
        Token* tmp = this->right;
        this->right = other;
        other->right = tmp;
        other->left = this;
    }
    return other;
}

Token* Token::del () {
    if (simplifiable.find(this->cat) == simplifiable.end()) {
        return this;
    }
    if (this->left != nullptr) {
        this->left->right = this->right;
    }
    if (this->right != nullptr) {
        this->right->left = this->left;
    }
    Token* x = this->left;
    delete this;
    return x;
}

bool Token::is_bin_simplifyable() {
    if (simplifiable.find(this->cat) == simplifiable.end()) {
        return false;
    }
    if ((this->value).find("\"") != std::string::npos || (this->value).find("(") != std::string::npos || (this->value).find("|") != std::string::npos || (this->value).find(" ") != std::string::npos) {
        return true;
    }
    return false;
}

Token* Token::replace (Token* first, Token* last) {
    first->left = this->left;
    if (this->left != nullptr) {
        this->left->right = first;
    }
    last->right = this->right;
    if (this->right != nullptr) {
        this->right->left = last;
    }
    delete this;
    return first;
}

Token* Token::get (int ind) {
    Token* ret = this;
    if (ind > 0) {
        for (int i = 0; i < ind; i++) {
            ret = ret->right;
        }
        return ret;
    } else {
        for (int i = 0; i < -ind; i++) {
            ret = ret->left;
        }
        return ret;
    }
}

void Token::identify () {
    if (simplifiable.find(this->cat) != simplifiable.end()) {
        if (u_operators.find(this->value) != u_operators.end()) {
            this->cat = OP;
            return;
        } else {
            bool is_digit = true;
            for (int i = 0; i < this->value.size(); i++) {
                if (!std::isdigit((this->value)[i]) && ((i != 0) || (this->value[i] != '+' && this->value[i] != '-'))) {
                    is_digit = false;
                }
                
            }
            if (is_digit) {
                this->cat = NUM;
                return;
            }
            std::string low = to_lower(this->value); 
            if (keywords.find(low) != keywords.end()) {
                this->value = low;
                this->cat = KEY;
                return;
            }
            if (types.find(low) != types.end()) {
                this->value = low;
                this->cat = TYPE;
                return;
            } 
            if ((low.size() > 1) && low[0] == '0' && low[1] == 'x') {
                this->cat = BYTE;
                this->value = low;
                return;
            } 
            if (low == "null") {
                this->cat = NONE;
                this->value = low;
                return;
            }
            if (low == "true" || low == "false") {
                this->cat = LOG;
                this->value = low;
                return;
            }
            this->cat = ID;
            return;
        }
        
    }
}

std::pair<Token*, Token*> split_binary (std::string input) {
    Token* first = new Token(HEAD);
    Token* last = new Token();
    last = first;
    std::string chunk = "";
    char cur = ' ';
    bool is_str_opened = false;
    char new_cur = ' ';
    int length = input.size();
    for (int i = 0; i < length; i++) {
        if (is_str_opened) {
            if (input[i] == '\"') {
                if (cur == ' ') {
                    last = last->add(chunk, STR);
                    chunk = "";
                } else {
                    chunk += "\"";
                }
                is_str_opened = false; 
            } else {
                chunk += input[i];
            }
        } else {     
            switch (input[i]) {
                case '\"':
                    is_str_opened = true;
                    if (cur == ' ') {
                        if (chunk != "") {
                            last->add(chunk, UNF);
                            chunk = "";
                        }
                    } else {
                        chunk += '\"';
                    }
                    break;
                case '|':
                    switch (cur) {
                    case '|':
                        if (chunk == "") {
                            last = last->add("||", OP);
                        } else {
                            last = last->add(chunk, BAR);
                        }
                        new_cur = ' ';
                        chunk = "";
                        break;
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        }
                        new_cur = '|';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                        break;
                    }
                    break;
                case '(':
                    switch (cur) {
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        }
                        new_cur = '(';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                        break;
                    }
                    break;
                case ')':
                    switch (cur) {
                    case '(':
                        last = last->add(chunk, BR);
                        new_cur = ' ';
                        chunk = "";
                        break;
                    case ' ':
                        error("found \")\" without opening \"(\" in statement \'" + input + "\' at position " + std::to_string(i), "Parsing");
                        break;
                    default:
                        chunk += input[i];
                        break;
                    } 
                    break;
                case '[':
                    switch (cur) {
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        } else {
                            error("expected the type name before \"[\" in the statement \'" + input + "\'", "Tokenization");
                        }
                        new_cur = '[';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                        break;
                    }
                    break;
                case ']':
                    switch (cur) {
                    case '[':
                        last = last->add(chunk, TYPE);
                        new_cur = ' ';
                        chunk = "";
                        break;
                    case ' ':
                        error("found \"]\" without opening \"[\" in statement \'" + input + "\' at position " + std::to_string(i), "Parsing");
                        break;
                    default:
                        chunk += input[i];
                        break;
                    } 
                    break;
                case '{':
                    switch (cur) {
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        }
                        new_cur = '{';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                        break;
                    }
                    break;
                case '}':
                    switch (cur) {
                    case '{':
                        last = last->add(chunk, CBR);
                        new_cur = ' ';
                        chunk = "";
                        break;
                    case ' ':
                        error("found \"}\" without opening \"{\" in statement \'" + input + "\' at position " + std::to_string(i), "Parsing");
                        break;
                    default:
                        chunk += input[i];
                        break;
                    } 
                    break;
                case ';':
                    switch (cur) {
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        }
                        last = last->add(";", SYNT);
                        new_cur = ' ';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                        break;
                    }
                    break;
                case ':':
                    switch (cur) {
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        }
                        last = last->add(":", SYNT);
                        new_cur = ' ';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                        break;
                    }
                    break;
                case ',':
                    switch (cur) {
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        }
                        last = last->add(",", SYNT);
                        new_cur = ' ';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                        break;
                    }
                    break;
                case '\n':
                case '\t':
                case ' ':
                    switch (cur) {
                    case ' ':
                        if (chunk != "") {
                            last = last->add(chunk, UNF);
                        }
                        new_cur = ' ';
                        chunk = "";
                        break;
                    default:
                        chunk += input[i];
                    }
                    break;
                default:
                    chunk += input[i];
                    break;
            }
            cur = new_cur;
    }  
    }
    if (is_str_opened) {
        error("mismatching \" in the statement \'" + input + "\'", "Tokenization");
    }
    if (chunk != "") {
        last = last->add(chunk, UNF);
    }
    last = last->add("", HEAD);
    return std::pair(first, last);
}

Token* prepare (std::string input) {
        Token* head = new Token(input, UNF);
        Token* cur = head;
        bool is_head = true;
        //std::cerr << "before preparation \n";
        //print(head);
        while (true) {
            if (cur->is_bin_simplifyable()) {
                //std::cerr << "ready for preparation \n";
                std::pair<Token*, Token*> output = split_binary(cur->value);
                cur = cur->replace(output.first, output.second);
                if (is_head) head = cur;
            } else {
                //std::cerr << "ready for identification \n";
                cur->identify();
                //std::cerr << "identified \n";
                //print(cur);
                if (cur->value == "") {
                    cur = cur->del();
                }
                if (cur->right == nullptr) {
                    break;
                }
                cur = cur->right;
                is_head = false;
            }

        }
        if (head->cat != HEAD) {
            head->add(new Token(HEAD), true);
            head = head->left;
        }
        if (cur->cat != HEAD) {
            cur->add(new Token(HEAD));
        }

        return head;
}

void print(Token* x) {
    std::cerr << "[";
    Token* a = x;
    while (a != nullptr) {
        std::cerr << "" << display(a->cat) << ": `" << a->value << "`, ";
        a = a->right;
    }
    std::cerr << "]\n";
}
