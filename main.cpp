
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class DFA {
    // -For the time being we'll be using the {0,1}
    //  alphabet.
    int numOfStates, alphabetLen = 2;
    int **transitionTable;
    int initial, *finals, numOfFinals;

public:
    DFA() {
        transitionTable = NULL;
        finals = NULL;
    }

    // -Building from given arrays. This is mostly intended
    //  for debugging purposes.
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

    // -Building from a .txt file.
    DFA(const char* fileName) {
        int i, j;

        ifstream input(fileName);
        if(!input.is_open()) {
            throw "\nCould not open file...\n";
        }

        // -First number encounter is the number of states.
        numOfStates = getNextInt(&input);
        // -Second number encounter is the number of final
        //  states.
        numOfFinals = getNextInt(&input);

        // -The following 'numOfFinals' numbers are the
        //  final states.
        finals = new int[numOfFinals];
        for(i = 0; i < numOfFinals; i++)
            finals[i] = getNextInt(&input);

        // -The next 'numOfStates * alphabetLen' numbers
        //  represents the transition table.
        transitionTable = new int*[numOfStates];
        for(i = 0; i < numOfStates; i++) {
            transitionTable[i] = new int[alphabetLen];
            for(j = 0; j < alphabetLen; j++)
                transitionTable[i][j] = getNextInt(&input);
        }
        // -The last number is the initial state.
        initial = getNextInt(&input);
        input.close();
    }

    // -Validating the input string.
    bool operator()(const char* w) {
        int i = 0, currentState = initial;

        for(i = 0; w[i] == '0' || w[i] == '1'; i++) // -Transition.
            currentState = transitionTable[currentState][w[i] - 48];
        for(i = 0; i < numOfFinals; i++) // -Valid string?
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
    // -Gets all the content of a .txt file and store it in
    //  a c-style string. Mostly intended for debugging purposes.
    char* getText(const char* fileName) {
        char tmp, *text;
        int len = -1, i = 0;

        ifstream input(fileName);

        if(!input.is_open()) {
            throw "\nCould not open file...\n";
        }
        // -Length of the content of the file.
        while(input.get() != EOF) len++;
        text = new char[len + 1];
        // -Returning to the beginning of file.
        input.clear();
        input.seekg(0, input.beg);
        // -Storing file content in 'text'.
        while((tmp = input.get()) != EOF) {
            text[i++] = tmp;
        }
        text[i] = 0; // -End of string.
        input.close();
        return text;
    }

    // -Ignores non-digits characters and gets the first
    //  integer that encounters.
    int getNextInt(ifstream *f) {
        char tmp;
        int num = 0;
        tmp = f->get();
        // -Ignores character that are not digits.
        while(tmp <= 47 || tmp >= 58) {
            if(tmp == EOF) return num;
            tmp = f->get();
        }
        // -Gets the first number that encounters.
        while(tmp > 47 && tmp < 58) {
            num *= 10;
            num += (tmp - 48);
            tmp = f->get();
        }
        return num;
    }

    // -Same as the function above, but with a string.
    int getNextInt(const char* str, int& position) {
        char tmp;
        int num = 0;
        tmp = str[position++];
        while(tmp <= 47 || tmp >= 58) {
            if(tmp == 0) return num;
            tmp = str[position++];
        }
        while(tmp > 47 && tmp < 58) {
            num *= 10;
            num += (tmp - 48);
            tmp = str[position++];
        }
        return num;
    }
};

int main (int argc, char* argv[]) {
    char w[50];
    bool print = true;

    while(true) {
        if(argc == 1) {
            cout << "\nToo few arguments...\n";
            return 1;
        }
        if(argc > 2) {
            cout << "\nToo many arguments...\n";
            return 1;
        }
        cout << "\nPress ctrl+C to exit the program.";

        DFA aut(argv[1]);
        if(print) {
            aut.print();
            print = false;
        }

        cout << "\nInput string: ";
        cin >> w;

        if(aut(w)) cout << "\nAccepted string\n";
        else cout << "\nString not accepted\n";
    }

    return 0;
}
