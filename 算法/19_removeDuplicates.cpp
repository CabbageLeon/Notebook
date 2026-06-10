#include<iostream>
#include<stack>
#include<string>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        string result;
        for(int i=0;i<s.size();i++)
        {
            if(st.empty()||s[i]!=st.top()) st.push(s[i]);
            else st.pop();
        }
        while(!st.empty())
        {
            result += st.top();
            st.pop();
        }

        int begin = 0;
        int end = result.size()-1;
        for(;begin<end;begin++,end--)
        {
            swap(result[begin],result[end]);
        }
        return result;
    }
};
int main(){
    Solution sol;
    string test = "abbaca";
    sol.removeDuplicates(test);
}