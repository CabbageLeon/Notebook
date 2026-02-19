#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int slow = 0;
        int result = INT32_MAX;
        int sum = 0;
        for(int i = 0;i<nums.size();i++)
        {
            sum+=nums[i];
            while(sum>=target)
            {
                if(result>(i-slow+1))
                {
                    result = i-slow+1;
                }
                sum -=nums[slow++];
            }
        }
        return result == INT32_MAX?0:result;      
    }
};
int main(int argc, char const *argv[])
{
    vector<int> test = {1,4,4};
    int target = 7;
    Solution sol;
    sol.minSubArrayLen(target,test);
    return 0;
}
