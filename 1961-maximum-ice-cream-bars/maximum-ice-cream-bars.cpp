
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {

        int n = costs.size();

        // Find maximum cost
        int maxi = 0;

        for (int i = 0; i < n; i++) {
            maxi = max(maxi, costs[i]);
        }

        // Create frequency array
        vector<int> freq(maxi + 1, 0);

        // Count frequency of each price
        for (int i = 0; i < n; i++) {
            freq[costs[i]]++;
        }

        int count = 0;

        // Buy cheapest ice creams first
        for (int i = 1; i <= maxi; i++) {

            while (freq[i] > 0 && coins >= i) {

                coins -= i;
                count++;
                freq[i]--;
            }

            if (coins < i) {
                break;
            }
        }

        return count;
    }
};
