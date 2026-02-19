#include<iostream>
#include<vector>
using namespace std;
class Solution
{
    public:

        int removeElement(vector<int>& nums ,int val)
        {
            int slowIndex = 0;
            for(int fastIndex = 0;fastIndex<nums.size();fastIndex++)
            {
                if(nums[fastIndex] != val)
                {
                    nums[slowIndex++] = nums[fastIndex];
                } 
            }     
            return slowIndex;   
        } 

};
int main()
{
    vector<int> test;
    test.push_back(3);
    test.push_back(2);
    test.push_back(2);
    test.push_back(3);

    Solution sol;
    sol.removeElement(test,2);
    // cout<<"hello"<<endl;

}