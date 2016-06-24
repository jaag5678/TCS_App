//
// Created by shantanu on 19/6/16.
//

#ifndef TCSTOOL_NONDEFINITE_AUTOMA_H
#define TCSTOOL_NONDEFINITE_AUTOMA_H

#include <vector>
#include <string>
#include "t_table.h"
#include "finite_automa.h"

using namespace std;

class t_table2{         //even this can be used to make DFAs,
                        //kept it inside NFA to show that a NFA is a superset of DFA
public:
    int states;
    int variables;
    vector <string> state_names;
    vector <string> variable_names;
    vector  <int> **array = NULL;                           //only difference between t_table and t_table2 classes
    void build_array();                                     //creates array dynamically
    void fill_table();                                      //takes in input and fills the table built earlier
    void mappy(string state, int state_off, int var_off);   //aid to fill_table since user enters "state name" as input.
    void display_table();                                   //debugging purposes

    void declare_error(int i);                              //error handling
};


class nondefinite_automa {
    public:
        t_table2 transitions;
        string start_state;
        vector <string> final_states;
    void init();
    void passandtest(string user_input);
    finite_automa not_lazy_evaluate();
    int getoffset(char given);
};


#endif //TCSTOOL_NONDEFINITE_AUTOMA_H
