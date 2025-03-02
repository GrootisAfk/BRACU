#include<bits/stdc++.h>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;
    // Write necessary attributes to store what type of symbol it is (variable/array/function)
    string data_type;
    // Write necessary attributes to store the type/return type of the symbol (int/float/void/...)
    vector<string> param_types;
    // Write necessary attributes to store the parameters of a function
    vector<string> param_names;
    // Write necessary attributes to store the array size if the symbol is an array
    int array_size;

public:
    symbol_info(string name, string type, string data_type="", vector<string> param_types = vector<string>(), vector<string> param_names = vector<string>())
    {
        this->name = name;
        this->type = type;
        this->data_type=data_type;
        this->array_size=0;
        this->param_types = param_types;
        this->param_names = param_names;
    }
    string get_name()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    void set_type(string type)
    {
        this->type = type;
    }
    // Write necessary functions to set and get the attributes

    string get_data_type(){
        return data_type;
    }
    void set_data_type(string data_type){
        this->data_type=data_type;
    }
    vector<string> get_param_types() { 
        return param_types; 
        }
    vector<string> get_param_names() { 
        return param_names; 
        }
    void add_parameter(string type, string name) {
        param_types.push_back(type);
        param_names.push_back(name);
    }
     void set_param_types(const vector<string>& types) { 
        param_types = types; 
        }
    void set_param_names(const vector<string>& names) { 
        param_names = names; 
        }

    int get_array_size() { 
        return array_size; 
        }
    void set_array_size(int size) { 
        this->array_size = size; 
        }
   
    ~symbol_info()
    {
        // Write necessary code to deallocate memory, if necessary
    }
};