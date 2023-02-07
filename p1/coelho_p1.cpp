#include "coelho_p1.hpp"

using namespace std;

struct transition{
    int q,r;
    char a, b, x;

    char get_a(){
        return a;
    }
};

struct state{
    int state_num;
    string action;
    vector<transition> curr_state_transitions;

    bool accepts(char symbol){
        bool flag = false;
        for(int i = 0; i < curr_state_transitions.size(); i++){
            if(curr_state_transitions.at(i).get_a() == symbol){
                flag = true;
            }
        }
        return flag;
    }

    transition get_transition(char symbol){
        transition trans;
        for(int i = 0; i < curr_state_transitions.size(); i++){
            if(curr_state_transitions.at(i).get_a() == symbol){
                trans = curr_state_transitions.at(i);
            }
        }
        return trans;
    }
};


turing_machine::turing_machine(){
    //empty constructor
}

turing_machine::turing_machine(string file, char* input, int num_transitions){
    read_input(file);
    this->input = input;
    this->num_transitions = num_transitions;
    execute();
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
            char a,b,x;

            s >> q >> a >> r >> b >> x;

            transition new_transition;
            new_transition.q= q;
            new_transition.a = a;
            new_transition.r = r;
            new_transition.b = b;
            new_transition.x = x;

            transitions.push_back(new_transition);

            states.at(q).curr_state_transitions.push_back(new_transition);

        }

    }
}

string turing_machine::execute(){
    string result = "";
    vector<char> tape;
    int tape_head_index, curr_state_num = 0;
    state curr_state = states.at(0);

    for(int i = 0; i < strlen(input); i++){
        tape.push_back(input[i]);
    }

    if(curr_state.accepts(tape.at(tape_head_index)) == true){
        curr_state_num = curr_state.get_transition(tape.at(tape_head_index)).r;
        curr_state = states.at(curr_state_num);
        cout << "new state = " << curr_state.state_num << endl;
    }

    //printing all states and their associated transitions
    /* for(int n = 0; n < states.size(); n++){
        state curr_state = states.at(n);
        cout << "state " << states.at(n).state_num << endl;

        for(int i = 0; i < curr_state.curr_state_transitions.size(); i++){
            cout << curr_state.curr_state_transitions.at(i).q << " -> " << curr_state.curr_state_transitions.at(i).r << " when received " << curr_state.curr_state_transitions.at(i).a << endl;
        }
    } */

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