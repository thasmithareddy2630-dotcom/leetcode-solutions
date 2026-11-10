class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        int n = servers.size();
        int m = tasks.size();

        // Available servers: {weight, index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > available;

        // Busy servers: {freeTime, weight, index}
        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > busy;

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long time = 0;

        for (int i = 0; i < m; i++) {

            // Time must never move backwards
            time = max(time, (long long)i);

            // Release all servers that have completed
            while (!busy.empty() &&
                   get<0>(busy.top()) <= time) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If all servers are busy, wait
            if (available.empty()) {

                time = get<0>(busy.top());

                // Release all servers available at this time
                while (!busy.empty() &&
                       get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Select server with smallest weight and index
            auto [weight, index] = available.top();
            available.pop();

            ans[i] = index;

            // Calculate when this server becomes free
            busy.push({
                time + tasks[i],
                weight,
                index
            });
        }

        return ans;
    }
};