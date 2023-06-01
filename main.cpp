
#include <iostream>
#include <cstdlib>

using namespace std;

class DFA {
    int alphabetLen, numbOfStates;
    int **transitionTable = NULL;
    int initial, *finals = NULL, finalsLen;

public:
    DFA(int _alphabetLen, int _numbOfStates, int _transitionTable[][2],
        int _initial, int _finals[], int _finalsLen) {
        int i, j;
        alphabetLen = _alphabetLen;
        numbOfStates = _numbOfStates;

        transitionTable = new int*[numbOfStates];
        for(i = 0; i < numbOfStates; i++) {
            transitionTable[i] = new int[alphabetLen];
            for(j = 0; j < alphabetLen; j++)
                transitionTable[i][j] = _transitionTable[i][j];
        }

        initial = _initial;
        finalsLen = _finalsLen;

        finals = new int[finalsLen];
        for(i = 0; i < finalsLen; i++) finals[i] = _finals[i];
    }

    bool operator()(const char* w) {
        int i = 0, currentState = initial;

        for(i = 0; w[i] != 0; i++)
            currentState = transitionTable[currentState][w[i] - 48];
        for(i = 0; i < finalsLen; i++)
            if(currentState == finals[i]) return true;

        return false;
    }

    ~DFA() {
        if(transitionTable != NULL) {
            for(int i = 0; i < numbOfStates; i++)
                delete[] transitionTable[i];
            delete[] transitionTable;
        }
        if(finals != NULL) delete[] finals;
    }
};

int main ()
{
    int t[][2] = {{0, 1},
                  {0, 1}};
    int f[] = {0};
    int ns = 2, al = 2, nf = 1, in = 0;

    DFA aut(al, ns, t, in, f, nf);
    if(aut("1010")) cout << "1";
    else cout << "0";

    cout << "\n\n";

    return 0;
}
