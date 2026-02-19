class Solution:
    def sortedSquares(self, nums: list[int]) -> list[int]:
        
        left = 0
        right = len(nums)-1
        k = len(nums)-1
        sorted = [0]*len(nums)
        while(k!=-1):
            if(nums[right]**2>nums[left]**2):
                sorted[k] = nums[right]**2
                k-=1
                right-=1
            else:
                sorted[k] = nums[left]**2
                k-=1
                left+=1
        return sorted
if __name__ == "__main__":
    test = [-4,-1,0,3,10]
    sol = Solution()
    sol.sortedSquares(test)