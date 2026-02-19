#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0;
        int right= nums.size()-1;
        int k = nums.size()-1;
        vector<int> sorted(nums.size(),0);
        while(k!=-1)
        {
            if(nums[left]*nums[left]>nums[right]*nums[right])
            {
                sorted[k--] = nums[left]*nums[left];
                left++;
            }else
            {
                sorted[k--] = nums[right]*nums[right];
                right--;
            }
        }
        return sorted;
    }
};

int main()
{
    vector<int> test;
    test = {-4,-1,0,3,10};
    Solution sol;
    sol.sortedSquares(test);
    return 0;
}