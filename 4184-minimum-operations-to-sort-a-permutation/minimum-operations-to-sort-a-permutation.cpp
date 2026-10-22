
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;

        bool inc = true, dec = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (nums[0] + i) % n)
                inc = false;

            if (nums[i] != (nums[0] - i + n) % n)
                dec = false;
        }

        if (inc) {
            int k = nums[0];
            ans = min((n - k) % n, k + 2);
        }

        if (dec) {
            int k = (n - 1 - nums[0] + n) % n;
            ans = min(ans, 1 + min(k, (n - k) % n));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
