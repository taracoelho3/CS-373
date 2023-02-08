#ifndef COELHO_P1_HPP
#define COELHO_P1_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

struct state;
struct transition;

class turing_machine{
    public:
        turing_machine();
        turing_machine(string, char*, int);
        void read_input(string);
        void execute();
    private:
        vector<state> states;
        vector<transition> transitions;
        char* input;
        int num_transitions;
};

#endif