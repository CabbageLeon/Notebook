#include<iostream>
#include<stack>
using namespace std;
class MyQueue {
        stack<int> inStack;
        stack<int> outStack;
public:
    MyQueue() {

    }
    
    void push(int x) {
        inStack.push(x);
    }
    
    int pop() {
        if(outStack.empty())
        {
            while(!inStack.empty())
            {
                int temp = inStack.top();
                outStack.push(temp);
                inStack.pop();
            }
            int temp = outStack.top();
            outStack.pop();
            return temp;
        }
        else 
        {
            int temp = outStack.top();
            outStack.pop();
            return temp;
        }
    }
    
    int peek() {
        if(outStack.empty())
        {
            while(!inStack.empty())
            {
                int temp = inStack.top();
                outStack.push(temp);
                inStack.pop();
            }
            int temp = outStack.top();
            // outStack.pop();
            return temp;
        }
        else 
        {
            int temp = outStack.top();
            // outStack.pop();
            return temp;
        }
    }
    
    bool empty() {
        if(inStack.empty()&&outStack.empty()) return true;
        else return false;
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */