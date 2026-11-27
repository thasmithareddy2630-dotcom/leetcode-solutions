
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> dp(budget + 1, 0);
        int minPrice = INT_MAX;

        for (auto &item : items) {
            int factor = item[0];
            int price = item[1];

            minPrice = min(minPrice, price);

            // Count purchased item + free items
            int cnt = 0;

            for (auto &other : items) {
                if (other[0] % factor == 0) {
                    cnt++;
                }
            }

            // 0/1 Knapsack
            for (int j = budget; j >= price; j--) {
                dp[j] = max(dp[j], dp[j - price] + cnt);
            }
        }

        int ans = 0;

        // Use remaining budget to buy cheapest items
        for (int i = 0; i <= budget; i++) {
            ans = max(ans, dp[i] + (budget - i) / minPrice);
        }

        return ans;
    }
};
