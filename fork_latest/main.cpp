#include <iostream>
#include <vector>
#include <string>
#include "t_table.h"
#include "finite_automa.h"
#include "nondefinite_automa.h"

using namespace std;

int main() {
   // finite_automa FA1;
   // FA1.init();
   // FA1.passandtest("1aa1aa11a1a"); //example, strings that end with 1a

    //t_table2 example;
    //example.build_array();
    //example.fill_table();
    //example.display_table();

    nondefinite_automa rial;
    rial.init();
    finite_automa y = rial.not_lazy_evaluate();
    y.transitions.display_table_indices();

    return 0;
}