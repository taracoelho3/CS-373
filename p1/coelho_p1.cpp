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
    initialize_states();
    read_input(file);
    this->input = input;
    this->num_transitions = num_transitions;
    execute();
}

void turing_machine::initialize_states(){
    for(int i = 0; i < 1000; i++){
        state new_state;
        new_state.state_num = i;
        new_state.action = "";
        states.push_back(new_state);
    }
    return;
}

void turing_machine::read_input(string filename){
    string line, behavior;

    ifstream infile(filename);

    while(getline(infile, line)){
        stringstream s(line);
        s >> behavior;

        if(behavior == "state"){
            string action = "";
            int state_num = 0;
            s >>  state_num >> action;
            
            if(state_num < 1001){
                states.at(state_num).action = action;
            }
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

void turing_machine::execute(){
    string tape_head_move, replace_char;
    vector<char> tape;
    int tape_head_index = 0, curr_state_num = 0, transition_counter = 0;
    state curr_state;

    //find start state
    for(int i = 0; i < states.size(); i++){
        if(states.at(i).action == "start"){
            curr_state = states.at(i);
        }
    }

    //initialize tape with blank characters
    for(int i = 0; i < 100; i++){
        tape.push_back('_');
    }

    //replace beginning tape with input characters
    for(int i = 0; i < strlen(input); i++){
        tape.at(i) = input[i];
    }
    
    while(curr_state.action != "accept"){   

    //quit if max transitions exceeded
    if(transition_counter > this->num_transitions){
        for(int i = tape_head_index + 1; i < tape.size(); i++){
            if(tape.at(i) != '_'){
                cout << tape.at(i);
            }
            
        }
        cout << " quit" << endl;
        return;
    } 

    if(tape_head_index < 0){
        cout << "invalid tape index, moved too far to the left" << endl;
        return;
    }

    if(curr_state.action == "reject"){
        for(int i = tape_head_index; i < tape.size(); i++){
            if(tape.at(i) != '_'){
                cout << tape.at(i);
            }
        }
        cout << " reject" << endl;
        return;
    }

    //if there is an existing next state for the symbol...
    if(curr_state.accepts(tape.at(tape_head_index)) == true){
        /*cout << "changing from " << curr_state.state_num << " to next state " << curr_state.get_transition(tape.at(tape_head_index)).r << endl;
        cout << "replacing " << tape.at(tape_head_index) << " with " << curr_state.get_transition(tape.at(tape_head_index)).b << endl;
        cout << "tape head moving " << curr_state.get_transition(tape.at(tape_head_index)).x << endl;
        cout << "-------END TRANSITION-------" << endl;
        cout << endl;*/
 
        //gather information from current state
        curr_state_num = curr_state.get_transition(tape.at(tape_head_index)).r;
        tape_head_move = curr_state.get_transition(tape.at(tape_head_index)).x;
        tape.at(tape_head_index) = curr_state.get_transition(tape.at(tape_head_index)).b;

        //now change states to next state
        curr_state = states.at(curr_state_num);
        transition_counter++;
            
        //check if tape head moves
        if(tape_head_move.compare("R") == 0){
            tape_head_index++;
        }
        if(tape_head_move.compare("L") == 0){
            tape_head_index--;
        }
    }
    //no possible transition state, reject
    else{
        for(int i = tape_head_index; i < tape.size(); i++){
            if(tape.at(i) != '_'){
                cout << tape.at(i);
            }
        }
        cout << " reject" << endl;
        return;
    }
        if(curr_state.action == "accept"){
            int i = 0;
            while(tape.at(i) != '_'){
                cout << tape.at(i);
                i++;
            }
            cout << " accept" << endl;
        }
    }
    return;
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