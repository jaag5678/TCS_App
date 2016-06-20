//
// Created by shantanu on 19/6/16.
//

#include "finite_automa.h"
#include "t_table.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void finite_automa::init() {
    string burray = "";
    transitions.build_array();                                   //FA needs a transition table, init will look after it
    transitions.fill_table();
    //transitions.display_table();
    cout<<"Which state is the start state? ";
    cin>>start_state;
    cout<<"Which states are/is the final state(s)?  ";
    cin.ignore();                                               //input flush
    char option = 'y';
    while(option == 'y' || option == 'Y') {
        getline(cin, burray);
        if (!burray.empty() && burray[burray.length()-1] == '\n') {
            burray.erase(burray.length()-1);                    //remove '\n' from end of line
        }
        final_states.push_back(burray);                         //keep collecting final states
        cout<<"Add another final state? (Y/N) ";
        cin>>option;
    } //start from start state
}

void finite_automa::passandtest(string user_input) {            //magic^2
    int i, state_set = 0, input_set;
    input = user_input;
    string next_state;
    for(i = 0; i < transitions.states; i++) {
        if(transitions.state_names[i] == start_state) {         //find out where to start
            state_set = i;
            break;
        }
    }
    cout<<"PATH : "<<start_state;                               //fancy
    //current_state = transitions.state_names[0];
    for(i = 0; i < input.length(); i++) {                       //transition by updating input_set, state_set
        input_set = getoffset(input[i]);
        state_set = transitions.array[state_set][input_set];
        next_state = transitions.state_names[state_set];        //string next_state used solely for printing path
        cout<<"-->"<<next_state;
    }
    state_set = -1;
    for(i = 0; i < final_states.size(); i++) {                  //see if we end up among the final states
        if(final_states[i] == next_state) {
            state_set++;
            break;
        }
    }
    if(!state_set)
        cout<<"\nAccepted\n";                                   //cool
    else
        cout<<"\nLets try that again\n";
}

int finite_automa::getoffset(char given) {
    int i, y = 1;
    for(i = 0; i < transitions.variables; i++) {
        if(transitions.variable_names[i][0] == given) {         //a man wants input_set for passandtest
            y--;
            break;
        }
    }
    if(!y)
        return i;
    else
        transitions.declare_error(1);
    return -1;

}
