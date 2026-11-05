
class Solution {
    struct Fenwick {
        int n;
        vector<long long> b1, b2;

        Fenwick(int n) : n(n) {
            b1.assign(n + 2, 0);
            b2.assign(n + 2, 0);
        }

        void add(vector<long long>& bit, int i, long long val) {
            for (; i <= n + 1; i += i & -i)
                bit[i] += val;
        }

        long long query(vector<long long>& bit, int i) {
            long long res = 0;
            for (; i > 0; i -= i & -i)
                res += bit[i];
            return res;
        }

        // Add val to every position in [l, r]
        void update(int l, int r, long long val) {
            int L = l + 1;
            int R = r + 1;

            add(b1, L, val);
            add(b1, R + 1, -val);

            add(b2, L, val * l);
            add(b2, R + 1, -val * (r + 1LL));
        }

        // Sum of positions [0, p]
        long long prefixSum(int p) {
            if (p < 0) return 0;

            int x = p + 1;

            return query(b1, x) * x - query(b2, x);
        }
    };

    struct Node {
        int val, l, r;
    };

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();

        // Count subarrays having range >= threshold
        auto countAtLeast = [&](long long threshold) -> long long {

            deque<int> mx, mn;
            int left = 0;
            long long count = 0;

            for (int i = 0; i < n; i++) {

                while (!mx.empty() && nums[mx.back()] <= nums[i])
                    mx.pop_back();

                mx.push_back(i);

                while (!mn.empty() && nums[mn.back()] >= nums[i])
                    mn.pop_back();

                mn.push_back(i);

                while (left <= i &&
                       (long long)nums[mx.front()] - nums[mn.front()]
                       >= threshold) {

                    if (mx.front() == left)
                        mx.pop_front();

                    if (mn.front() == left)
                        mn.pop_front();

                    left++;
                }

                count += left;
            }

            return count;
        };

        // Calculate count and sum of ranges >= threshold
        auto calculate = [&](long long threshold)
            -> pair<long long, long long> {

            Fenwick maxBIT(n), minBIT(n);

            vector<Node> maxSt, minSt;

            deque<int> mx, mn;

            int left = 0;
            long long count = 0;
            long long total = 0;

            for (int i = 0; i < n; i++) {

                int x = nums[i];

                // Update maximum contributions
                int start = i;

                while (!maxSt.empty() && maxSt.back().val <= x) {

                    Node t = maxSt.back();
                    maxSt.pop_back();

                    maxBIT.update(t.l, t.r,
                                  (long long)x - t.val);

                    start = t.l;
                }

                maxBIT.update(i, i, x);
                maxSt.push_back({x, start, i});

                // Update minimum contributions
                start = i;

                while (!minSt.empty() && minSt.back().val >= x) {

                    Node t = minSt.back();
                    minSt.pop_back();

                    minBIT.update(t.l, t.r,
                                  (long long)x - t.val);

                    start = t.l;
                }

                minBIT.update(i, i, x);
                minSt.push_back({x, start, i});

                // Maintain sliding window maximum
                while (!mx.empty() && nums[mx.back()] <= x)
                    mx.pop_back();

                mx.push_back(i);

                // Maintain sliding window minimum
                while (!mn.empty() && nums[mn.back()] >= x)
                    mn.pop_back();

                mn.push_back(i);

                // Find valid starting positions
                while (left <= i &&
                       (long long)nums[mx.front()] - nums[mn.front()]
                       >= threshold) {

                    if (mx.front() == left)
                        mx.pop_front();

                    if (mn.front() == left)
                        mn.pop_front();

                    left++;
                }

                count += left;

                // Sum max - min for valid subarrays
                long long maxSum = maxBIT.prefixSum(left - 1);
                long long minSum = minBIT.prefixSum(left - 1);

                total += maxSum - minSum;
            }

            return {count, total};
        };

        int mnVal = *min_element(nums.begin(), nums.end());
        int mxVal = *max_element(nums.begin(), nums.end());

        long long low = 0;
        long long high = (long long)mxVal - mnVal;

        // Binary search for the kth largest range
        while (low < high) {

            long long mid = low + (high - low + 1) / 2;

            if (countAtLeast(mid) >= k)
                low = mid;
            else
                high = mid - 1;
        }

        // Calculate sum of ranges strictly greater than low
        auto [cnt, sum] = calculate(low + 1);

        // Fill remaining selections with range = low
        return sum + (long long)(k - cnt) * low;
    }
};
