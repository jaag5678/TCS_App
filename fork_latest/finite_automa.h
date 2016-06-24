//
// Created by shantanu on 19/6/16.
//

#ifndef TCSTOOL_FINITE_AUTOMA_H
#define TCSTOOL_FINITE_AUTOMA_H


#include "t_table.h"
#include <vector>
#include <string>

using namespace std;

class finite_automa {
public:
    t_table transitions;
    string input;
    string start_state;
    vector <string> final_states;
    void init();
    void passandtest(string input);
    //we will try string and substring transitions later but they are not reg expressions. They be cfls
    int getoffset(char given);


};



#endif //TCSTOOL_FINITE_AUTOMA_H
