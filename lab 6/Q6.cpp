/* Task 6 – Infix to Prefix Conversion using Stack
Write a program to convert an infix expression into prefix form using stack rules.
1. Include operator precedence and associativity handling.
2. Evaluate the prefix expression as well. */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T> *next;

    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Stack {
    Node<T> *top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    void push(T val){
        Node<T> *newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop(){
        if(size == 0){
            cout << "Stack underflow!" << endl;
            return;
        }
        Node<T> *delNode = top;
        top = top->next;
        delete delNode;
        size--;
    }

    T peek() const {
        if(size == 0){
            return '-';
        }
        return top->data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    ~Stack(){
        while(top != nullptr){
            Node<T> *delNode = top;
            top = top->next;
            delete delNode;
        }
    }
};

int priority(char c){
    if(c == '^') return 3;
    else if(c == '*' || c == '/') return 2;
    else if(c == '+' || c == '-') return 1;
    else return -1;
}

string infixToPrefix(string s){
    reverse(s.begin(), s.end());
    Stack<char> st;
    string result = "";

    for(char &c : s){
        if(c == '(') c = ')';
        else if(c == ')') c = '(';
    }

    for(char c : s){
        if(isalnum(c)){
            result += c;
        }
        else if(c == '('){
            st.push(c);
        }
        else if(c == ')'){
            while(!st.isEmpty() && st.peek() != '('){
                result += st.peek();
                st.pop();
            }
            if(!st.isEmpty()) st.pop();
        }
        else{
            while(!st.isEmpty() && (priority(c) < priority(st.peek()) ||
                (priority(c) == priority(st.peek()) && c != '^'))){
                result += st.peek();
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.isEmpty()){
        result += st.peek();
        st.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

double evaluatePrefix(string expr){
    Stack<double> st;
    reverse(expr.begin(), expr.end());

    for(char c : expr){
        if(isdigit(c)){
            st.push(c - '0');
        }
        else{
            double val1 = st.peek();
            st.pop();
            double val2 = st.peek();
            st.pop();

            switch(c){
                case '+': st.push(val2 + val1); break;
                case '-': st.push(val2 - val1); break;
                case '*': st.push(val2 * val1); break;
                case '/': st.push(val2 / val1); break;
                case '^': st.push(pow(val2, val1)); break;
            }
        }
    }

    return st.peek();
}

int main(){
    string infix;
    cout << "Enter infix expression (e.g., (3+5)*2): ";
    cin >> infix;

    string prefix = infixToPrefix(infix);
    cout << "Prefix Expression: " << prefix << endl;

    double result = evaluatePrefix(prefix);
    cout << "Evaluation Result: " << result << endl;

    return 0;
}
