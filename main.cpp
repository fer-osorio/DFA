
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class DFA {
    int numOfStates, alphabetLen = 2;
    int **transitionTable;
    int initial, *finals, numOfFinals;

public:
    DFA() {
        transitionTable = NULL;
        finals = NULL;
    }

    DFA(int _numOfStates, int _transitionTable[][2],
        int _initial, int _finals[], int _numOfFinals) {
        int i, j;
        numOfStates = _numOfStates;

        transitionTable = new int*[numOfStates];
        for(i = 0; i < numOfStates; i++) {
            transitionTable[i] = new int[alphabetLen];
            for(j = 0; j < alphabetLen; j++)
                transitionTable[i][j] = _transitionTable[i][j];
        }

        initial = _initial;
        numOfFinals = _numOfFinals;

        finals = new int[numOfFinals];
        for(i = 0; i < numOfFinals; i++) finals[i] = _finals[i];
    }

    DFA(const char* fileName) {
        int i, j;
        ifstream input(fileName);
        if(!input.is_open()) {
            throw "\nCould not open file...\n";
        }
        numOfStates = getNextInt(&input);
        numOfFinals = getNextInt(&input);

        finals = new int[numOfFinals];
        for(i = 0; i < numOfFinals; i++)
            finals[i] = getNextInt(&input);

        transitionTable = new int*[numOfStates];
        for(i = 0; i < numOfStates; i++) {
            transitionTable[i] = new int[alphabetLen];
            for(j = 0; j < alphabetLen; j++)
                transitionTable[i][j] = getNextInt(&input);
        }
        initial = getNextInt(&input);
        input.close();
    }

    bool operator()(const char* w) {
        int i = 0, currentState = initial;

        for(i = 0; w[i] == '0' || w[i] == 1; i++)
            currentState = transitionTable[currentState][w[i] - 48];
        for(i = 0; i < numOfFinals; i++)
            if(currentState == finals[i]) return true;

        return false;
    }

    ~DFA() {
        if(transitionTable != NULL) {
            for(int i = 0; i < numOfStates; i++)
                if(transitionTable[i] != NULL)
                    delete[] transitionTable[i];

            delete[] transitionTable;
        }
        if(finals != NULL) delete[] finals;
    }

    void print() {
        int i;
        cout << "\nNumber of states : " << numOfStates << '\n';
        cout << "Number of finals : " << numOfFinals << '\n';
        cout << "Finals : ";
        for(i = 0; i < numOfFinals; i++) {
            cout << finals[i];
            if(i != numOfFinals -  1) cout << ", ";
        }
        cout << "\nTransition table : \n";
        for(i = 0; i < numOfStates; i++) {
            cout << transitionTable[i][0];
            cout << ", ";
            cout << transitionTable[i][1];
            cout << "\n";
        }
        cout << "Initial state: " << initial << '\n';
    }

private:
    /*char* getText(char* fileName){
        char tmp;
        int len = 0;
        ifstream input(fileName);
        if(!input.is_open()) {
            throw "\nCould not open file...\n";
        }


        input.close();
    }*/

    int getNextInt(ifstream *f) {
        char tmp;
        int num = 0;
        tmp = f->get();
        while(tmp <= 47 || tmp >= 58) {
            if(tmp == EOF) return num;
            tmp = f->get();
        }
        while(tmp > 47 && tmp < 58) {
            num *= 10;
            num += (tmp - 48);
            tmp = f->get();
        }
        return num;
    }
};

int main (int argc, char* argv[]) {
    /*int t[][2] = {{0, 1},
                  {0, 1}};
    int f[] = {0};
    int ns = 2, al = 2, nf = 1, in = 0;

    DFA aut(ns, t, in, f, nf);
    if(aut("10111")) cout << "1";
    else cout << "0";*/

    DFA aut;
    char w[50];

    switch (argc) {
        case 1:
            cout << "\nToo few arguments...\n";
            return 1;
        case 2:
            try {
                aut = DFA(argv[1]);
            } catch(char* msg) {
                cout << msg;
            }
            break;
        default:
            cout << "\nToo many arguments...\n";
            return 1;
    }

    aut.print();

    cout << "\nInput string: ";
    cin >> w;

    if(aut(w)) cout << "\n1\n";
    else cout << "\n0\n";

    cout << "\n\n";

    return 0;
}
