#include "coelho_p2.hpp"

using namespace std;

char x1, x2, x3, x4;
char* gate_directions;
string init_input;


int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "invalid input" << endl;
    }
    else{
       gate_directions = argv[1];
       init_input = argv[2];
    }
    string result = "";

    x1 = gate_directions[0];
    x2 = gate_directions[1];
    x3 = gate_directions[2];
    x4 = gate_directions[3];

    char arr[init_input.length()];
    strcpy(arr, init_input.c_str());

    for(int i = 0; i < init_input.length(); i++){
        int input = arr[i];
        
        cout << x1 << x2 << x3 << x4 << "->";
        if(x1 == 'L'){
            if(input == '1'){
                x1 = 'R';  
            }else{
                x1 = 'C';
            }

            if(x2 == 'L'){
                if(x2 == 'L'){
                    x2 = 'R';  
                }else{
                    x2 = 'L';
                }
                result = "B";
            }else{
                if(x2 == 'L'){
                    x2 = 'R';  
                }else{
                    x2 = 'L';
                }
                result = "C";
            }
            continue;
        }

        if(x1 == 'C'){
            if(input == '1'){
                x1 = 'L';  
            }else{
                x1 = 'R';
            }

            if(x3 == 'L'){
                if(x3 == 'L'){
                    x3 = 'R';  
                }else{
                    x3 = 'L';
                }
                result = "C";
            }else{
                if(x3 == 'L'){
                    x3 = 'R';  
                }else{
                    x3 = 'L';
                }
                result = "D";
            }
            continue;
        }

        if(x1 == 'R'){
            if(input == '1'){
                x1 = 'C';  
            }else{
                x1 = 'L';
            }

            if(x4 == 'L'){
                if(x4 == 'L'){
                    x4 = 'R';  
                }else{
                    x4 = 'L';
                }
                result = "D";
            }else{
                if(x4 == 'L'){
                    x4 = 'R';  
                }else{
                    x4 = 'L';
                }
                result = "E";
            }
            continue;
        }
        result.push_back(x1);
        result.push_back(x2);
        result.push_back(x3);
        result.push_back(x4);
        result.append(" -> ");
    }
    cout << x1 << x2 << x3 << x4;
    cout << " " << result << endl;
}