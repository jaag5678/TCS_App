//
// Created by shantanu on 19/6/16.
//

#include "nondefinite_automa.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void t_table2::build_array() {
    int i;
    cout << "Enter number of states followed by number of variables!" << endl;
    cin>>states>>variables;
    array = (vector<int> **)malloc(states * sizeof(vector <int>));              //array of state vectors pointers
    string burray;
    cin.ignore();
    for(i = 0; i < states; i++) {
        array[i] = (vector<int> *)malloc((variables + 1)* sizeof(vector <int>));  //+1 for e transitions;
        cout << "State " <<i<<" has name : ";
        getline(cin, burray);
        if (!burray.empty() && burray[burray.length()-1] == '\n') {             //removes '\n' from end of line
            burray.erase(burray.length()-1);
        }
        state_names.push_back(burray);                                          //this is how we add to a vector
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
    variable_names.push_back("e (epsilon transitions)");                //adding the name
    variables++;                                                        // e is officially a variable name now
}

void t_table2::fill_table() {
    int i, j;
    string temp;
    char option = 'Y';                                                  //user friendly feature
    //print an empty table
    cout<<"Use key '-' in case you wish to demonstrate a no transition case.\n";
    for(i = 0; i < states; i++) {
        cout<<"For state "<<state_names[i]<<endl;                       //thats how we print
        for(j = 0; j < variables; j++) {
            cout<<"\ttransition form here on variable "<<variable_names[j]<<" goes to which state(s)? ";
            cin>>temp;
            mappy(temp, i, j);
            cout<<"\t\tAdd another state for this variable? (Y/N) ";
            cin>>option;
            while(option == 'Y' || option == 'y') {
                cout<<"\t\tEnter the destination state name of this extra transition ";
                cin>>temp;
                mappy(temp, i, j);
                cout<<"\t\tAdd another state for this variable? (Y/N) ";
                cin>>option;
            }
        }
    }
}

void t_table2::mappy(string state,int state_off, int var_off) {     //all mappy does is update the array with x
                                                                    // where input state is state_names[x]
                                                                    //check if state in state_names, find offset
    int i;
    if (!state.empty() && state[state.length()-1] == '\n') {
        state.erase(state.length()-1);
    }
    if(state == "-") {
        array[state_off][var_off].push_back(-1);                    //in case user decides to chuck transition midway
        return;                                                     //-1 cannot be an index so its a flag for us
    }
    for(i = 0; i < states; i++) {
        if(state_names[i] == state)                                 //fetch x
            break;
    }
    //now update array
    if(state_names[i] == state)
        array[state_off][var_off].push_back(i);                     //magic
    else {                                                          //input typo handling
        string temp;
        declare_error(0);
        cout << "Try again. For variable " << variable_names[var_off] << " on state " << state_names[state_off]
        << " we transition to which state? ";
        cin>>temp;
        mappy(temp, state_off, var_off);
    }
}

void t_table2::display_table() {
    int i, j, k;
    cout<<"STATES\n";
    int y;
    for(i = 0; i < states; i++) {
        cout<<state_names[i]<<" :\n";
        for(j = 0; j < variables; j++) {
            cout<<"\tOn variable "<<variable_names[j]<<": ";
            for (k = 0; k < array[i][j].size() - 1; k++) {
                y = array[i][j][k];
                if(y != -1)
                    cout<< state_names[y] << "|";
                else
                    continue;
            }
            y = array[i][j][k];
            if(y != -1)
                cout<<state_names[array[i][j][k]];
            cout<<endl;
        }
    }
}

void t_table2::declare_error(int i) {
    string errors[] = { "State not found :/\nCheck the input state name and transition name.\n",
                        "No transition variable matches with input letter from given string.\n"};
    cout<<errors[i];
}

