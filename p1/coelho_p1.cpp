#include "coelho_p1.hpp"

using namespace std;

struct state{
    int state_num;
    string action;
};

struct transition{
    int q,r;
    string a, b, x;
};

turing_machine::turing_machine(){
    //empty constructor
}

turing_machine::turing_machine(string file, char* input, int num_transitions){
    read_input(file);
    this->input = input;
    this->num_transitions = num_transitions;

    /* cout << "reading turing machine input from " << file << endl;
    cout << "input string " << endl;
    for(int i = 0; i < 5; i++){
        cout << input[i] << endl;
    }
    cout << "max transitions " << num_transitions << endl; */
}

void turing_machine::read_input(string filename){
    string line, behavior;

    ifstream infile(filename);

    while(getline(infile, line)){
        stringstream s(line);
        s >> behavior;

        if(behavior == "state"){
            string action = "";
            int state_num;
            s >>  state_num >> action;

            state new_state;
            new_state.state_num = state_num;
            new_state.action = action;

            states.push_back(new_state);
        }
        if(behavior == "transition"){
            int q, r;
            string a,b,x;

            s >> q >> a >> r >> b >> x;

            transition new_transition;
            new_transition.q= q;
            new_transition.a = a;
            new_transition.r = r;
            new_transition.b = b;
            new_transition.x = x;

            transitions.push_back(new_transition);

        }

    }
}

string turing_machine::execute(){
    string result = "";
    return result;
}

int main(int argc, char *argv[]){
    if(argc != 4){
        cout << "invalid input" << endl;
    }
    else{
        string file;
        char* input;
        int num_transitions;
        file = argv[1];
        input = argv[2];
        num_transitions = atoi(argv[3]);
        turing_machine test(file, input, num_transitions);

    }
}