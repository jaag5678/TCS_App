//
// Created by shantanu on 19/6/16.
//

#include "t_table.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
void t_table::build_array() {
    int i;
    cout << "Enter number of states followed by number of variables!" << endl;
    cin>>states>>variables;
    array = (int **)malloc(states * sizeof(int));                          //an array of states pointers
    string burray;
    cin.ignore();                                                          //flush input
    for(i = 0; i < states; i++) {
        array[i] = (int*)malloc(variables*sizeof(int));                    //each pointer is assigned variables int
        cout << "State " <<i<<" has name : ";
        getline(cin, burray);
        if (!burray.empty() && burray[burray.length()-1] == '\n') {        //remove '\n' from end of line, if any
            burray.erase(burray.length()-1);
        }
        state_names.push_back(burray);                                     //update vector
    }
    cout<<"Remember, theoretically an automata reads one char at a time, make sure your variable name follows\n";
    for(i = 0; i < variables; i++) {
        cout << "Variable " <<i<<" has name : ";
        //cin.ignore();
        getline(cin, burray);
        if (!burray.empty() && burray[burray.length()-1] == '\n') {
            burray.erase(burray.length()-1);
        }
        variable_names.push_back(burray);
    }
}

void t_table::fill_table() {                                            //allows user to use state names as input
    int i, j;
    string temp;
    //print an empty table
    for(i = 0; i < states; i++) {
        cout<<"For state "<<state_names[i]<<endl;
        for(j = 0; j < variables; j++) {
            cout<<"\ttransition form here on variable "<<variable_names[j]<<" goes to which state? ";
            cin>>temp;
            mappy(temp, i, j);                                          //mappy the mvp
        }
    }
}

void t_table::mappy(string state,int state_off, int var_off) {
    //check if state in state_names, find offset
    int i;
    if (!state.empty() && state[state.length()-1] == '\n') {            //remove '\n', if any from the given string
        state.erase(state.length()-1);
    }
    for(i = 0; i < states; i++) {                                       //state offset
        if(state_names[i] == state)
            break;
    }
    //now update array
    if(state_names[i] == state)
        array[state_off][var_off] = i;                                  //update array
    else {
        string temp;
        declare_error(0);                                               //handle typos in case of user fault
        cout << "Try again. For variable " << variable_names[var_off] << " on state " << state_names[state_off]
        << " we transition to which state? ";
        cin>>temp;
        mappy(temp, state_off, var_off);
    }
}

void t_table::display_table() {                                         //display feature
    int i, j;
    cout<<"STATE\t\t";
    for(i = 0; i < variables; i++)
        cout<<variable_names[i]<<"\t\t";
    cout<<endl;
    for(i = 0; i < states; i++) {
        cout<<state_names[i]<<"\t\t";
        for(j = 0; j < variables; j++)
            cout<<state_names[array[i][j]]<<"\t\t";
        cout<<endl;
    }
}

void t_table::declare_error(int i) {
    string errors[] = { "State not found :/\nCheck the input state name and transition name.\n",
                        "No transition variable matches with input letter from given string.\n"};
    cout<<errors[i];
}

