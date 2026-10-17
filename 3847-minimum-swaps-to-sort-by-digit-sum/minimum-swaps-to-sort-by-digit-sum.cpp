class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> a = nums;

        auto sum = [](int x) {
            int s = 0;
            while (x) {
                s += x % 10;
                x /= 10;
            }
            return s;
        };

        sort(a.begin(), a.end(), [&](int x, int y) {
            if (sum(x) != sum(y)) return sum(x) < sum(y);
            return x < y;
        });

        unordered_map<int, int> pos;
        for (int i = 0; i < n; i++) pos[nums[i]] = i;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] != a[i]) {
                int j = pos[a[i]];
                pos[nums[i]] = j;
                pos[a[i]] = i;
                swap(nums[i], nums[j]);
                ans++;
            }
        }
        return ans;
    }
};