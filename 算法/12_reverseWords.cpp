#include<iostream>
using namespace std;
#include<vector>
#include<string>
class Solution {
public:
    void reverse(string& s,int begin,int end)
    {
        int first = begin;
        int second = end;
        for(;begin<s.size();begin++,end--)
        {
            swap(s[first],s[second]);
        }

    }
    void removeExtraSpace(string& s)
    {
        int fast = 0;
        int slow = 0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]!=' ')
            {
                if(slow!=0) s[i++]=' ';
            }
            while(i<s.size()){}  
        }
    }
    string reverseWords(string s) {

    }
};