//
// Created by shantanu on 19/6/16.
//

#ifndef TCSTOOL_T_TABLE_H
#define TCSTOOL_T_TABLE_H
#include <string>
#include <vector>
using namespace std;

class t_table {                         //refer comments on t_table2 in nondefinite_automa.h
public:
    int states;
    int variables;
    vector <string> state_names;
    vector <string> variable_names;
    vector <int> final_state_indices;
    int **array = NULL;
    void build_array();
    void fill_table();
    void mappy(string state, int state_off, int var_off);
    void display_table();
    void display_table_indices();

    void declare_error(int i);
};



#endif //TCSTOOL_T_TABLE_H
