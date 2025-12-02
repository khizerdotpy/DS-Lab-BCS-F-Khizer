/* Task 5 – Infix to Postfix Conversion using Stack
Write a program to convert an infix expression into postfix form using a stack. Also, evaluate the
postfix expression afterward. */

#include <iostream>
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
            cout << "Stack underflow! No elements present in the stack to be popped" << endl;
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

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    ~Stack(){
        Node<T> *curr = top;
        while(curr != nullptr){
            Node<T> *delNode = curr;
            curr = curr->next;
            delete delNode;
        }
    }
};

int priority(char c){
    if (c == '^') return 3;
    else if(c == '/' || c == '*') return 2;
    else if(c == '+' || c == '-') return 1;
    else return -1;
}

string infixToPostfix(string s){
    string ans = "";
    Stack<char> st;

    for(char c : s){
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) ans += c;
        else if(c == '(') st.push(c);
        else if (c == ')'){
            while(!st.isEmpty() && st.peek() != '('){
                ans += st.peek();
                st.pop();
            }

            if(!st.isEmpty())
                st.pop();
        }
        else{
            while(!st.isEmpty() && ((priority(c) < priority(st.peek()) || (priority(c) == priority(st.peek()) && c != '^')))){
                ans += st.peek();
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.isEmpty()){
        ans += st.peek();
        st.pop();
    }

    return ans;
}

double evaluatePostfix(string expr){
    Stack<double> st;
    for(char c : expr){
        if(isdigit(c)){
            st.push(c - '0');
        }
        else{
            double val2 = st.peek();
            st.pop();
            double val1 = st.peek();
            st.pop();
            switch(c){
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
                case '^': st.push(pow(val1, val2)); break;
            }
        }
    }

    return st.peek();
}

int main() {
    string infix;
    cout << "Enter infix expression (e.g., 3+5*(2-1)): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    double result = evaluatePostfix(postfix);
    cout << "Evaluation Result: " << result << endl;

    return 0;
}
