#include "../Collumn/Collumn.h"
#ifndef TABLE_H
#define TABLE_H
#define INDEX_NAME "*_Index"
#include <map>

class Table {
	int rows_count;

public:
    std::vector <std::string> collumn_names; 
	std::map<std::string, Collumn> collumns;
	std::string name;

    Table();
    
	Table(std::string name);
    
    void add_collumn(Collumn C);
    
	void add_collumn(ObjectType type, std::string name = "", bool is_key = 0, bool is_unique = 0, bool is_autoincrement = 0, GenericObject def = GenericObject());

	void add_row(std::map<std::string, GenericObject> row = std::map<std::string, GenericObject>());

	void add_row(std::vector<GenericObject> row, bool ignoring_index = true);

	void del_collumn(std::string name);

	void del_row (int i);

	void print(std::ostream& os = std::cout);
	void save (std::ostream& os = std::cout);

	bool operator==(Table& other) {
		if (this->name != other.name) {
			return false;
		}
		for (int i = 0; i < this->collumn_names.size(); i++) {
			if (this->collumns[collumn_names[i]] == other.collumns[collumn_names[i]]) {
				return false;
			} 
		}
		return true;
	}
};  

Table load(std::istream& stream);

#endif