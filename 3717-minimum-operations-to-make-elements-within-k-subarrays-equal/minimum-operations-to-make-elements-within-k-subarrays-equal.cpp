
class Solution {
public:
    multiset<int> leftSet, rightSet;
    long long sumLeft = 0, sumRight = 0;

    void balance() {
        while (leftSet.size() > rightSet.size() + 1) {
            int val = *leftSet.rbegin();
            leftSet.erase(leftSet.find(val));
            sumLeft -= val;

            rightSet.insert(val);
            sumRight += val;
        }

        while (leftSet.size() < rightSet.size()) {
            int val = *rightSet.begin();
            rightSet.erase(rightSet.find(val));
            sumRight -= val;

            leftSet.insert(val);
            sumLeft += val;
        }
    }

    void add(int val) {
        if (leftSet.empty() || val <= *leftSet.rbegin()) {
            leftSet.insert(val);
            sumLeft += val;
        } else {
            rightSet.insert(val);
            sumRight += val;
        }
        balance();
    }

    void remove(int val) {
        auto it = leftSet.find(val);

        if (it != leftSet.end()) {
            leftSet.erase(it);
            sumLeft -= val;
        } else {
            it = rightSet.find(val);
            rightSet.erase(it);
            sumRight -= val;
        }

        balance();
    }

    long long getCost() {
        long long median = *leftSet.rbegin();

        return median * leftSet.size() - sumLeft
             + sumRight - median * rightSet.size();
    }

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);

            cost[i - x + 1] = getCost();
        }

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, 1e18)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {

                dp[j][i] = dp[j][i - 1];

                if (i >= x && dp[j - 1][i - x] != 1e18) {
                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
