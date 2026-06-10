#include<iostream>
using namespace std;
#include<vector>
#include<string>

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        for(int i=1;i<s.size()/2;i++)
        {
            int times = s.size()%i;
            if(!times) continue;//如果不能整除说明不可能被这个长度的子串重复
            vector<int> needle(s.begin(),s.begin()+i);
            for(int j=0;j<times;j++)
            {
                for(int k=0;k<i;k++)
                {
                    if(needle[k]!=s[needle.size()*j+k]) return false;
                }
            }
        }
        return true;
    }
};