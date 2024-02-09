/*
    Class: 314 Wed 1:00 pm Winter
    Programmer: Mitchell Foote
    Description: A CLI program that takes input on the desired number of variables, their truth values, and a logical expression using
    these variables and outputs the expressions final truth value to the terminal.

*/
#include<iostream>
#include<string>
#include<stack>
#include<limits>
#include<algorithm>
#include<vector>
#include<sstream>

// Scoping
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stack;
using std::getline;
using std::vector;

int numVar;
bool a, b, c, d, e;

// Function prototypes
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

// Prints instructions to terminal and calls needed functions to handle program specifications.
void evaluator() {

    cout << "Enter the number of variables in the expression: ";

    getVar();

    cout << endl << "Enter the values of variables - true or false: " << endl;

    getVal();

    cout << "Enter the logical expression: ";

    getExp();

}

// Handles input for number of variables.
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

// Handles input for truth values of variables.
void getVal() {

    int temp = 1;

    // Handle input and validation for variable values.
    while(temp <= numVar){

        switch(temp) {
            case 1:
                cout << "a: " << endl;
                validateVal(a);
                break;
            case 2:
                cout << "b: " << endl;
                validateVal(b);
                break;
            case 3:
                cout << "c: " << endl;
                validateVal(c);
                break;
            case 4:
                cout << "d: " << endl;
                validateVal(d);
                break;
            case 5:
                cout << "e: " << endl;
                validateVal(e);
                break;
        }

        temp += 1;

    }

}

// Ensures only true or false values are entered, converts string to bool value.
void validateVal(bool &in) {
    string input;

    while (true) {
        cin >> input;

        //check string
        if (input == "true" || input == "false") {

            //convert to apropriate bool val
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

    // Clear remaining characters within input buffer.
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Handles input of logical expression and passes off to the eval function.
void getExp() {

    string expression;
    getline(cin, expression);

    // Calls helper to tokenize string input
    vector<string> tokens = tokenize(expression);

    //Check for valid expressions
    if (!validateExpression(tokens)) {
        cout << "Invalid expression. Enter again." << endl;
        cin.clear();
        getExp(); // restart expression input if failed.
    }

    bool result = evalExpression(tokens);
    cout << "The value of the given logical expression is " << (result ? "true" : "false") << "." << endl;


}

// Helper function to assist expression input by tokenizing string stream. 
vector<string> tokenize(const string &expression) {

    std::istringstream iss(expression);
    string token;
    vector<string> tokens;
    
    while(iss >> token){
        tokens.push_back(token);
    }

    return tokens;

}

// Helper function to validate tokens in the logical expression.
bool isTokenValid(const string& token) {
    
    const vector<string> ValidVars = {"a", "~a", "b", "~b", "c", "~c", "d", "~d", "e", "~e"};

    // Ensure only valid variables are used in expression.
    for (int i = 0; i < numVar*2; ++i) {
        if (token == ValidVars[i]) {
            return true;  
        }
    }

    if (token == "/\\" || token == "\\/") {
        return true;
    }

    //Return false for invalid expressions.
    return false;

}

// Wrapper function calls helper function on each token in the expression.
bool validateExpression(const vector<string>& tokens) {

    for (const string& token : tokens) {
        if (!isTokenValid(token)) {
            return false;
        }
    }


    return true;

}

// Calculates the expressions final truth value.
bool evalExpression(const vector<string>& tokens) {

    if (tokens.empty()) return false; // Corner case

    bool result = getTokenVal(tokens[0]);

    // Iterates through the expression and calculates value.
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

// Helper that returns truth value after handling if there are Not operations on tokens.
bool getTokenVal(const string& token) {
    
    if (token == "a" || token == "~a") return (token[0] == '~') ? !a : a;
    if (token == "b" || token == "~b") return (token[0] == '~') ? !b : b;
    if (token == "c" || token == "~c") return (token[0] == '~') ? !c : c;
    if (token == "d" || token == "~d") return (token[0] == '~') ? !d : d;
    if (token == "e" || token == "~e") return (token[0] == '~') ? !e : e;

    return false; 

}