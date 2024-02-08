/*

*/
#include<iostream>
#include<string>
#include<stack>
#include<limits>
#include<algorithm>
#include<vector>
#include<sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stack;
using std::getline;
using std::vector;

int numVar;
bool a, b, c, d, e;

void evaluator();
void getVar();
void getVal();
void validateVal(bool &in);
void getExp();
vector<string> tokenize(const string &expression);
bool isTokenValid(const string& token);
bool validateExpression(const vector<string>& tokens);
bool evalExpression(const vector<string>& tokens);
bool getTokenVal(const string& token);

int main() {

    cout << "Logical Expressions Evaluator" << endl;
    cout << "-----------------------------" << endl;

    evaluator();

    return 0;

}

void evaluator() {

    cout << "Enter the number of variables in the expression: ";

    getVar();

    cout << endl << "Enter the values of variables - true or false: " << endl;

    getVal();

    cout << "Enter the logical expression: ";

    getExp();

}

void getVar() {

    while(true) {

        cin >> numVar;

        if(cin.fail()) {
            cin.clear();
            cout  << "Invalid input, please enter a valid integer between 1 & 5" << endl;
        } else if(numVar >= 1 && numVar <= 5) {
            break;
        } else {
            cout  << "Invalid input, please enter a valid integer between 1 & 5" << endl;
        }

    }

}

void getVal() {

    int temp = 1;

    while(temp <= numVar){

        switch(temp) {
            case 1:
                cout << endl << "a: ";
                validateVal(a);
                break;
            case 2:
                cout << endl << "b: ";
                validateVal(b);
                break;
            case 3:
                cout << endl << "c: ";
                validateVal(c);
                break;
            case 4:
                cout << endl << "d: ";
                validateVal(d);
                break;
            case 5:
                cout << endl << "e: ";
                validateVal(e);
                break;
        }

        temp += 1;

    }

}

void validateVal(bool &in) {
    string input;

    while (true) {
        cin >> input;

        if (input == "true" || input == "false") {

            if (input == "true") {
                in = true;
            } else {
                in = false;
            }
            break;
        } else {
            cout << endl << "Invalid input. Please enter 'true' or 'false': ";
            cin.clear();
        }
    }

    // Clear any remaining characters in the input buffer
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void getExp() {

    string expression;
    getline(cin, expression);

    vector<string> tokens = tokenize(expression);

    if (!validateExpression(tokens)) {
        cout << "Invalid expression. Enter again." << endl;
        return;
    }

    bool result = evalExpression(tokens);
    cout << "The value of the given logical expression is " << (result ? "true" : "false") << "." << endl;


}

//helper function to assist expression input by tokenizing string stream. 
vector<string> tokenize(const string &expression) {

    std::istringstream iss(expression);
    string token;
    vector<string> tokens;
    
    while(iss >> token){
        tokens.push_back(token);
    }

    return tokens;

}

bool isTokenValid(const string& token) {
    
    const vector<string> validVars = {"a", "~a", "b", "~b", "c", "~c", "d", "~d", "e", "~e"};

    for (int i = 0; i < numVar*2; ++i) {
        if (token == validVars[i]) {
            return true;  
        }
    }

    if (token == "/\\" || token == "\\/") {
        return true;
    }

    return false;

}

bool validateExpression(const vector<string>& tokens) {

    for (const string& token : tokens) {
        if (!isTokenValid(token)) {
            return false;
        }
    }


    return true;
    
}
   
bool evalExpression(const vector<string>& tokens) {

    if (tokens.empty()) return false; 

    bool result = getTokenVal(tokens[0]);

    for (size_t i = 1; i < tokens.size(); i += 2) {
        if (i + 1 >= tokens.size()) break; 

        bool operand = getTokenVal(tokens[i + 1]);
        if (tokens[i] == "/\\") { 
            result &= operand;
        } else if (tokens[i] == "\\/") { 
            result |= operand;
        }
    }

    return result;

}

bool getTokenVal(const string& token) {
    
    if (token == "a" || token == "~a") return (token[0] == '~') ? !a : a;
    if (token == "b" || token == "~b") return (token[0] == '~') ? !b : b;
    if (token == "c" || token == "~c") return (token[0] == '~') ? !c : c;
    if (token == "d" || token == "~d") return (token[0] == '~') ? !d : d;
    if (token == "e" || token == "~e") return (token[0] == '~') ? !e : e;

    return false; 

}