
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Step 1: Build suffix array
        vector<int> s = nums;
        s.push_back(0);

        int N = n + 1;

        vector<int> p(N), c(N);

        int alphabet = max(100001, N);
        vector<int> cnt(alphabet, 0);

        for (int x : s)
            cnt[x]++;

        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i - 1];

        for (int i = N - 1; i >= 0; i--)
            p[--cnt[s[i]]] = i;

        c[p[0]] = 0;
        int classes = 1;

        for (int i = 1; i < N; i++) {
            if (s[p[i]] != s[p[i - 1]])
                classes++;

            c[p[i]] = classes - 1;
        }

        vector<int> pn(N), cn(N);

        for (int h = 0; (1 << h) < N; h++) {
            int len = 1 << h;

            for (int i = 0; i < N; i++) {
                pn[i] = p[i] - len;

                if (pn[i] < 0)
                    pn[i] += N;
            }

            fill(cnt.begin(), cnt.begin() + classes, 0);

            for (int i = 0; i < N; i++)
                cnt[c[pn[i]]]++;

            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];

            for (int i = N - 1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];

            cn[p[0]] = 0;
            int newClasses = 1;

            for (int i = 1; i < N; i++) {
                pair<int, int> cur = {
                    c[p[i]],
                    c[(p[i] + len) % N]
                };

                pair<int, int> prev = {
                    c[p[i - 1]],
                    c[(p[i - 1] + len) % N]
                };

                if (cur != prev)
                    newClasses++;

                cn[p[i]] = newClasses - 1;
            }

            c.swap(cn);
            classes = newClasses;
        }

        // Remove the suffix starting with sentinel 0
        vector<int> sa;

        for (int i = 1; i < N; i++)
            sa.push_back(p[i]);

        // Step 2: Build rank array
        vector<int> rank(n);

        for (int i = 0; i < n; i++)
            rank[sa[i]] = i;

        // Step 3: Calculate LCP
        vector<int> best(n, 0);

        int k = 0;

        for (int i = 0; i < n; i++) {
            int r = rank[i];

            if (r == n - 1) {
                k = 0;
                continue;
            }

            int j = sa[r + 1];

            while (i + k < n && j + k < n &&
                   nums[i + k] == nums[j + k]) {
                k++;
            }

            best[i] = max(best[i], k);
            best[j] = max(best[j], k);

            if (k > 0)
                k--;
        }

        // Step 4: Find minimum unique subarray length
        int ans = n;

        for (int i = 0; i < n; i++) {
            if (best[i] < n - i) {
                ans = min(ans, best[i] + 1);
            }
        }

        return ans;
    }
};
