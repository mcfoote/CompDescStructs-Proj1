#include<iostream>
#include<string>
#include<stack>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stack;

int numVar;
bool a, b, c, d, e;

int main() {

    cout << "Logical Expressions Evaluator" << endl;
    cout << "-----------------------------" << endl;

    evaluator();

    return 0;

}

static void evaluator() {

    cout << "Enter the number of variables in the expression: ";

    getVar();

    cout << endl << "Enter the values of variables - true or false: " << endl;

    getVal();

    cout << "Enter the logical expression: ";

    getExp();

}

static void getVar() {

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

static void getVal() {

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

static void validateVal(bool in) {

    while(true) {
        cin >> in;
        if(cin.fail()) {
            cin.clear();
            cout << endl << "Invalid input please enter true or false";
        } else if(in == true || in == false) {
            break;
        }
    }

}

static void getExp() {

}
   
