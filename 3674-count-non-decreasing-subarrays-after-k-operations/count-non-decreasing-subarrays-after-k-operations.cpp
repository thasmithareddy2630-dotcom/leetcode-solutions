
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        long long cost = 0;

        deque<pair<int, int>> dq;

        int j = nums.size() - 1;

        for (int i = nums.size() - 1; i >= 0; i--) {

            int num = nums[i];
            int count = 1;

            // Merge smaller values into the current value.
            while (!dq.empty() && dq.back().first < num) {

                auto [nextNum, nextCount] = dq.back();
                dq.pop_back();

                count += nextCount;

                cost += (long long)(num - nextNum) * nextCount;
            }

            dq.push_back({num, count});

            // Shrink the window if cost exceeds k.
            while (cost > k) {

                auto [rightmostNum, rightmostCount] = dq.front();
                dq.pop_front();

                cost -= rightmostNum - nums[j];
                j--;

                if (rightmostCount > 1) {
                    dq.push_front({
                        rightmostNum,
                        rightmostCount - 1
                    });
                }
            }

            ans += j - i + 1;
        }

        return ans;
    }
};
