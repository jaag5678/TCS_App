//
// Created by shantanu on 19/6/16.
//

#include "nondefinite_automa.h"
#include <iostream>
//#include <vector>
//#include <string>
#include <cmath>
//#include "t_table.h"
//#include "finite_automa.h"
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
                cin.ignore();
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
        cin.ignore();
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

void nondefinite_automa::passandtest(string user_input) {
    finite_automa we_need = not_lazy_evaluate();
    we_need.transitions.display_table_indices();
    int i, state_set, input_set;
    for(i = 0; i < we_need.transitions.states; i++) {
        if(we_need.transitions.state_names[i] == start_state) {         //find out where to start
            state_set = i;
            break;
        }
    }
    cout<<"PATH : "<<start_state;                               //fancy
    //current_state = transitions.state_names[0];
    for(i = 0; i < user_input.length(); i++) {                       //transition by updating input_set, state_set
        input_set = getoffset(user_input[i]);
        state_set = we_need.transitions.array[state_set][input_set];
        //next_state = transitions.state_names[state_set];        //string next_state used solely for printing path
        cout<<"-->"<<state_set;
    }
    input_set = -1;
    for(i = 0; i < we_need.transitions.final_state_indices.size(); i++) {                  //see if we end up among the final states
        if(we_need.transitions.final_state_indices[i] == state_set) {
            input_set++;
            break;
        }
    }
    if(!input_set)
        cout<<"\nAccepted\n";                                   //cool
    else
        cout<<"\nLets try that again\n";
}


void nondefinite_automa::init() {
    transitions.build_array();
    transitions.fill_table();
    transitions.display_table();
    cout<<"Which state is the start state? ";
    cin>>start_state;
    cout<<"Which states is/are the final state(s)?  ";
    cin.ignore();                                               //input flush
    char option;
    option = 'y';
    string burray;
    while(option == 'y' || option == 'Y') {
        cin.ignore();
        getline(cin, burray);
        if (!burray.empty() && burray[burray.length()-1] == '\n') {
            burray.erase(burray.length()-1);                    //remove '\n' from end of line
        }
        final_states.push_back(burray);                         //keep collecting final states
        cout<<"Add another final state? (Y/N) ";
        cin>>option;
    } //start from start state
}


finite_automa nondefinite_automa::not_lazy_evaluate() {

    //idea is to construct all possible subsets using combinations and mapping *vector array[a][b] to one such subset
    //how to store subsets? and search for them? minimal idea is to have an array of int vectors (variable sizes)
    //that contains all these subsets, later we could just compare these structures using linear search
    //so what happens if we compare? we don't get anywhere unless we evaluate where each ofr these subsets go!
    //but we don't really need to check every item in a subset and see where it goes for which input symbol
    //because of our t_table2. What if we just create a t_table out of t_table2 and note down the subsets containing
    //final symbols! Will that be okay? hell yeah! lets not forget to force epsilon closures i.e
    //last column/row in the variables compartment.


    //this is better from lazy evaluation in a few ways for this particular code since we will directly obtain
    //an object of class dfa instead of converting the **vector <vector> into int **array to avoid writing functions
    //such as checking if it accepts a string or printing the automa for the newly obtained dfa.


    //by all subsets I mean we need the power set
    vector <int> *subsets;
    //how many subsets? summation nCr for all r from 0 to n i.e 2^n
    int subsets_number = pow(2, transitions.states);
    subsets->reserve(subsets_number);
    int *state_index = (int *) malloc(transitions.states * sizeof(int));
    for (int k = 0; k < transitions.states; k++) {
        state_index[k] = k;

    }
    subsets = (vector<int> *) malloc(subsets_number * sizeof(vector <int>));


    vector <int> final_states_we_need;      //subsets offset
    vector <int> final_states_we_have;      //given final state offsets


    for(int i = 0; i < transitions.states; i++) {
        for(int j = 0; j < final_states.size(); j++) {
            if(transitions.state_names[i] == final_states[j])
                final_states_we_have.push_back(i);
        }
    }


    for(int i = 0; i < subsets_number; i++) {
        for(int j = 0; j < transitions.states; j++) {
            if(i & (1<<j))
                subsets[i].push_back(state_index[j]);
            for (int k = 0; k < final_states_we_have.size(); ++k) {
                if(final_states_we_have[k] == state_index[j]) //subsets[i][state_index[j]]  //is what you are pushing,
                    final_states_we_need.push_back(i);                        // one of the final states?
            }

        }
    }
    //now we have the power set
    //let us convert t_table2 in nfa to a t_table we will use in a dfa
    t_table construct;

    construct.states = transitions.states;
    construct.variables = transitions.variables - 1;
    //construct.state_names = transitions.state_names; //here?
    for(int i = 0; i < transitions.state_names.size(); i++) {
        construct.state_names.push_back(transitions.state_names[i]);
    }
    //construct.variable_names = transitions.variable_names;  //including epsilon
    for(int i = 0; i < transitions.variable_names.size(); i++) {
        construct.variable_names.push_back(transitions.variable_names[i]);
    }
    construct.array = (int **) malloc(construct.states * sizeof(int));
    for(int i = 0; i < construct.states; i++) {
        construct.array[i] = (int *) malloc(construct.variables * sizeof(int));
    }
    //modify t_table2 to make e closure
    //t_table2  closure = transitions;
    t_table2 closure;
    //init t_table2 then

    closure.states = transitions.states;
    closure.variables = transitions.variables;

    for(int i = 0; i < transitions.variable_names.size(); i++) {
        closure.variable_names.push_back(transitions.variable_names[i]);
    }
    for(int i = 0; i < transitions.state_names.size(); i++) {
        closure.state_names.push_back(transitions.state_names[i]);
    }


    closure.array = (vector<int> **)malloc(transitions.states * sizeof(vector <int>));              //array of state vectors pointers
    for(int i = 0; i < transitions.states; i++) {
        closure.array[i] = (vector<int> *) malloc((transitions.variables) * sizeof(vector<int>));
    }
    //
    int y;
    for(int i = 0; i < transitions.states; i++) {
        for(int j = 0; j < transitions.variables; j++) {
            for (int k = 0; k < transitions.array[i][j].size(); k++) {
                y = transitions.array[i][j][k];
                closure.array[i][j].push_back(y);
            }
        }
    }

    //







    //just append states in last row of variables with other transitions in that state;

    for (int i = 0; i < closure.states; i++) {
        for (int j = 0; j < closure.variables; j++) {
            for (int k = 0; k < transitions.array[i][closure.variables - 1].size(); ++k) { //e transitions
                //if transitions.array[i][closure.variables - 1][k] not inside transitions.array[i][j], append it
                int p = 0;
                int status = 0;
                while(p < transitions.array[i][j].size()) {
                    if(transitions.array[i][j][p] == transitions.array[i][transitions.variables - 1][k]) {
                        status++;
                        goto next;
                    }
                    p++;
                }
                next:
                if(!status)
                    closure.array[i][j].push_back(transitions.array[i][transitions.variables - 1][k]);
            }
        }
    }




    for (int i = 0; i < transitions.states; i++) {
        for (int j = 0; j < transitions.variables - 1; j++) {   //no need to check e transitions since we have
            //e closure now
            for (int k = 0; k < subsets_number; ++k) {
                if(subsets[k] == closure.array[i][j])
                    construct.array[i][j] = k;
            }
        }
    }
    //so construct should be ready now;
    //lets make a DFA out of it
    finite_automa result;
    result.transitions.states = construct.states;
    result.transitions.variables = construct.variables;

    for(int i = 0; i < construct.state_names.size(); i++) {
        result.transitions.state_names.push_back(construct.state_names[i]);
    }
    //construct.variable_names = transitions.variable_names;  //including epsilon
    for(int i = 0; i < construct.variable_names.size(); i++) {
        result.transitions.variable_names.push_back(construct.variable_names[i]);
    }
    result.transitions.array = (int **) malloc(construct.states * sizeof(int));
    for(int i = 0; i < construct.states; i++) {
        result.transitions.array[i] = (int *) malloc(construct.variables * sizeof(int));
    }


    for (int i = 0; i < construct.states; i++) {
        for (int j = 0; j < construct.variables; j++) {   //no need to check e transitions since we have
            result.transitions.array[i][j] = construct.array[i][j];
        }
    }


    vector <int> starts_here;
    int i;
    for(i = 0; i < transitions.states; i++) {
        if(transitions.state_names[i] == start_state)                                 //fetch x
            break;
    }
    starts_here.push_back(i);
    int l;
    for (l = 0; l < subsets_number; ++l) {
        if ((subsets[l].size() == 1) && (subsets[l][0] == starts_here[0]))
            break;
    }
    result.start_state = transitions.state_names[subsets[l][0]];    //name wont be the same, but it'll work

    //search for groups with final states

    for(l = 0; l < final_states_we_need.size(); l++) //no use, they can cross number of states
        result.transitions.final_state_indices.push_back(final_states_we_need[l]);

    //search for that group with a single element as start state



    return result;
}

int nondefinite_automa::getoffset(char given) {
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







