#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;

    int hash_function(string name)
    {
        int val = 0;
        for (char c : name)
        {
            val += (int)c;
        }
        return val % bucket_count;
    }

public:
    scope_table(){
        this->bucket_count = 20;   
        this->unique_id = 0;        
        this->parent_scope = nullptr;  
        this->table = vector<list<symbol_info*>>(bucket_count); 
    }
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope){
        this->bucket_count = bucket_count;    
        this->unique_id = unique_id;          
        this->parent_scope = parent_scope;   
        this->table = vector<list<symbol_info*>>(bucket_count);
    }
    scope_table *get_parent_scope(){
        return parent_scope;
    }
    int get_unique_id(){
        return unique_id;
    }
    symbol_info *lookup_in_scope(symbol_info* symbol){
        int index = hash_function(symbol->get_name());
        for (auto& entry : table[index]) {
            if (entry->get_name() == symbol->get_name()) {
                return entry;
            }
        }
        return nullptr;

    }
    bool insert_in_scope(symbol_info* symbol){
        if(!lookup_in_scope(symbol)) {
            int index = hash_function(symbol->get_name());
            table[index].push_back(symbol);
            return true;
        }
        return false;
    }
    bool delete_from_scope(symbol_info* symbol){
        int index = hash_function(symbol->get_name());
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if ((*it)->get_name() == symbol->get_name()) {
                delete *it;  
                bucket.erase(it);
                return true;
        
            }
        }
        return false;
    }
    void print_scope_table(ofstream& outlog);
    ~scope_table(){
        for (auto &bucket : table) {
            for (auto symbol : bucket) {
                delete symbol;  
            }
        }
    }

    // you can add more methods if you need
};

// complete the methods of scope_table class
void scope_table::print_scope_table(ofstream& outlog)
{
    outlog << "ScopeTable # " << unique_id << std::endl;

    for (int i = 0; i < bucket_count; ++i) {
        if (!table[i].empty()) {
            outlog << i << " --> " << std::endl;
            for (auto symbol : table[i]) {
                outlog << "< " << symbol->get_name() << " : " << symbol->get_type() << " >" << std::endl;
                if (symbol->get_data_type() != "") {
                    outlog << "Variable\nType: " << symbol->get_data_type() << std::endl;
                }
                if (!symbol->get_param_types().empty()) {
                    outlog << "Function Definition\nReturn Type: " << symbol->get_data_type() << std::endl;
                    outlog << "Number of Parameters: " << symbol->get_param_types().size() << std::endl;
                    for (size_t j = 0; j < symbol->get_param_types().size(); ++j) {
                        outlog << symbol->get_param_types()[j] << " " << symbol->get_param_names()[j] << ", ";
                    }
                    outlog << std::endl;
                }
            }
        }
    }
    outlog << "------------------------------------" << std::endl;
}