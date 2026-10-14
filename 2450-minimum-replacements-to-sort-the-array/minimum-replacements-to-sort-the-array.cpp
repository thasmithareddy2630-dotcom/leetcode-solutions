class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        long long operations = 0;
        long long prev = nums.back();

        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] > prev) {
                long long parts = (nums[i] + prev - 1) / prev;
                operations += parts - 1;
                prev = nums[i] / parts;
            } else {
                prev = nums[i];
            }
        }

        return operations;
    }
};