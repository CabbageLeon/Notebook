#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> answer(n,vector<int>(n,0));
        int loop = n/2;
        int mid = n/2;
        int offset = 0;
        int count = 1;
        while(loop --)
        {
            //上方从左到右
            for(int i = offset;i<n-offset-1;i++)
            {
                answer[offset][i] = count;
                count++;
            }
            //右边从上到下
            for(int i = offset;i<n-offset-1;i++)
            {
                answer[i][n-offset-1] = count;
                count++;
            }
            //下边从右到左
            for(int i = n-offset-1;i>offset;i--)
            {
                answer[n-offset-1][i] = count;
                count++;
            }
            //左边从下到上
            for(int i = n-offset-1;i>offset;i--)
            {
                answer[i][offset] = count;
                count++;
            }
            
            offset++;
        }
        if(n%2) answer[n/2][n/2] = count;

        return answer;
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;
    sol.generateMatrix(3);
    return 0;
}
