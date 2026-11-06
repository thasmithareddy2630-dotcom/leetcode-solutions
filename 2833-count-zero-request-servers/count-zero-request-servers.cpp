class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {

        int m = queries.size();

        // Sort logs according to time
        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        // Store queries with their original indices
        vector<pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(m);

        // Frequency of requests for each server
        vector<int> freq(n + 1, 0);

        int left = 0, right = 0;
        int active = 0;

        for (auto [time, idx] : q) {

            // Add logs within the current time window
            while (right < logs.size() &&
                   logs[right][1] <= time) {

                int id = logs[right][0];

                if (freq[id] == 0)
                    active++;

                freq[id]++;
                right++;
            }

            // Remove logs older than the window
            while (left < right &&
                   logs[left][1] < time - x) {

                int id = logs[left][0];

                freq[id]--;

                if (freq[id] == 0)
                    active--;

                left++;
            }

            // Servers without requests
            ans[idx] = n - active;
        }

        return ans;
    }
};