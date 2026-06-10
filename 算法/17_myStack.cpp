#include<iostream>
#include<queue>
using namespace std;
class MyStack {
    queue<int> que;
public:
    MyStack() {
        
    }
    
    void push(int x) {
        que.push(x);
    }
    
    int pop() {
        for(int i = 0;i<que.size()-1;i++)
        {
            que.push(que.front());
            que.pop();
        }
        int ret = que.front();
        que.pop();
        return ret;
    }
    
    int top() {
        int ret = pop();
        push(ret);
    }
    
    bool empty() {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */