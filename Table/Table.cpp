#include "Table.h"

Table::Table() {}

Table::Table(std::string name) {
    this->name = name;
    this->collumns[INDEX_NAME] = Collumn(INDEX_NAME, int_type, 1, 1, 1);
    this->collumn_names.push_back(INDEX_NAME);
    this->rows_count = 0;
}

void Table::Table::add_collumn(Collumn C) {
    this->collumns[C.name] = C;
    this->collumn_names.push_back(C.name);
    this->rows_count = 0;
}

void Table::add_collumn(ObjectType type, std::string name, bool is_key, bool is_unique, bool is_autoincrement, GenericObject def) {
    if (name == "") {
        error("tried to create a no-name collumn in the table \'" + this->name + "\'", "Name");
    }
    if (!this->collumns.count(name)) {
        this->collumn_names.push_back(name);
        this->collumns[name] = Collumn(name, type, is_key, is_unique, is_autoincrement, def);
        for (int i = 0; i < this->collumns[INDEX_NAME].cells.size(); i++) {
            this->collumns[name].add();
        }
    } else {
        error("collumn \'" + name + "\' already exists in the table \'" + this->name + "\'", "Name");
    }
}

void Table::add_row(std::map<std::string, GenericObject> row) {
    std::vector<std::string> added;
    for (auto& p : (row)) {
        if (collumns.count(p.first)) {
            this->collumns[p.first].add(p.second);
            added.push_back(p.first);
        } else {
            error("there is no collumn \'" + p.first + "\' in the table \'" + name + "\'");
        }
    }
    for (int i = 0; i < collumn_names.size(); i++) {
        if (std::find(added.begin(), added.end(), collumn_names[i]) == added.end()) {
            collumns[collumn_names[i]].add();
            added.push_back(collumn_names[i]);
        }
    }
    this->rows_count++;
}

void Table::add_row(std::vector<GenericObject> row, bool ignoring_index) {
    int cur = 0;
    if (ignoring_index) {
        this->collumns[INDEX_NAME].add();
        cur++;
    }
    for (int i = cur; i < row.size() + 1; i++) {
        this->collumns[this->collumn_names[i]].add(row[i-1]);
    }
    this->rows_count++;
}

void Table::del_collumn(std::string name) {
    if (this->collumns.count(name)) {
        this->collumns.erase(name);
        this->collumn_names.erase(find(this->collumn_names.begin(), this->collumn_names.end(), name));
    } else {
        error("there is no collumn " + name + " in the table " + this->name + " to delete", "Name");
    }
}


void Table::del_row (int i) {
    size_t it = find(this->collumns[INDEX_NAME].cells.begin(), this->collumns[INDEX_NAME].cells.end(), GenericObject(i, int_type)) - this->collumns[INDEX_NAME].cells.begin();
    if (it < this->collumns[INDEX_NAME].cells.size()) {
        for (auto& p : (this->collumns)) {
            p.second.del(it);
        }
    } else {
        error("there is no row " + std::to_string(i) + " in table " + this->name + " to delete", "Name");
    }
    this->rows_count--;
}

void Table::print(std::ostream& os) {
    os << this->name << "\n";
    for (auto& p : (this->collumns)) {
        if (p.first != INDEX_NAME) {
            os << p.first << " (" << p.second.type.type_str() << "); ";
        } else {
            os << "Index; ";
        }
    }
    os << "\n";
    for (int i = 0; i < this->collumns[INDEX_NAME].cells.size(); i++) {
        for (auto& p : (this->collumns)) {
            (p.second.cells[i]).print(os);
            os << "; ";
        }
        os << "\n";
    }

    os << "\n";
}

void Table::save (std::ostream& os) {
    os << this->name << "\n";
    for (auto& p : (this->collumns)) {
        os << p.first << ";" << p.second.type.type_dbg() << p.second.debug_flags() << "\n";
    }
    os << "\n";

    for (int i = 0; i < this->collumns[INDEX_NAME].cells.size(); i++) {
        for (auto& p : (this->collumns)) {
            os << (p.second.cells[i]).to_str_dbg();
            os << ";";
        }
        os << "\n";
    }

    os << "\n";
}

Table load(std::istream& stream) {
	std::string line;

	// Read the table name
	std::getline(stream, line);
	Table T = Table(line);
	
	std::istringstream lineStream(line);
	std::string token;
    int flg = 1;
    std::vector<std::pair<int, int>> types;
	
	while (std::getline(stream, line) && !line.empty()) {
		std::istringstream lineStream(line);
		std::string token;
		std::string name;
		std::getline(lineStream, name, ';');
		std::getline(lineStream, token, ';');
		int type = std::stoi(token);
		std::getline(lineStream, token, ';');
		int size = std::stoi(token);
		std::getline(lineStream, token, ';');
		types.push_back(std::pair(type, size));
		int flag1 = std::stoi(token);
		std::getline(lineStream, token, ';');
		int flag2 = std::stoi(token);
		std::getline(lineStream, token, ';');
		int flag3 = std::stoi(token);

		if (flg) {
			if (name != INDEX_NAME) {
			    T.add_collumn(ObjectType((ObjectTypeName) type, size), name, (bool) flag1, (bool) flag2, (bool) flag3);
		        T.del_collumn(INDEX_NAME);
			}
	        flg = 0;
		} else {
		    T.add_collumn(ObjectType((ObjectTypeName) type, size), name, (bool) flag1, (bool) flag2, (bool) flag3);
		}
	}
        
    while (std::getline(stream, line) && !line.empty()) {
		std::istringstream lineStream(line);
		std::string token;
		std::vector<GenericObject> res;
		
		for (int i = 0; i < types.size(); i++) {
		    //string obj;
		    std::getline(lineStream, token, ';');
		    int m = types[i].first; 

		    switch (m) {
		        case 0:
		            res.push_back(GenericObject(ObjectType(null_type, 0)));
		            break;
		        case 1:
		            res.push_back(GenericObject(std::stoi(token), ObjectType(int_type, 0)));
		            break;
		        case 2:
		            res.push_back(GenericObject(std::stoi(token), ObjectType(bool_type, 0)));
		            break;
		        case 3:
		            {
		            std::istringstream tokenStream(token);
                    std::string minitoken;
                    char* ret = new char [types[i].second];
		            for (int j = 0; j < types[i].second; j++) {
		                std::getline(tokenStream, minitoken, ',');
		                ret[j] = (char) stoi(minitoken);
		            }
		            res.push_back(GenericObject(ret, ObjectType(byte_type, types[i].second)));
		            }
		            break;
		        case 4:
		            //token
		            res.push_back(GenericObject((std::string) token, ObjectType(str_type)));
		            break;
		        default:
		            error("unknown type " + std::to_string(m) + " used in \"load\"", "Type");

		    }
        }
        // for (int i = 0; i < res.size(); i++) {
        //     std::cerr << res[i].to_str_dbg() << ", ";
        // }
        T.add_row(res, false);
    }
	return T;
};