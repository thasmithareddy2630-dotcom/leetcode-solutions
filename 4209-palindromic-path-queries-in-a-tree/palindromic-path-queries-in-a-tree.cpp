
class Solution {
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) {
            this->n = n;
            bit.assign(n + 2, 0);
        }

        void update(int i, int val) {
            for (; i <= n; i += i & -i) {
                bit[i] ^= val;
            }
        }

        void rangeUpdate(int l, int r, int val) {
            update(l, val);
            update(r + 1, val);
        }

        int query(int i) {
            int ans = 0;

            for (; i > 0; i -= i & -i) {
                ans ^= bit[i];
            }

            return ans;
        }
    };

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        int LOG = 17;

        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> depth(n, 0);
        vector<int> tin(n), tout(n);
        vector<int> pref(n, 0);

        int timer = 0;

        // Iterative DFS
        vector<tuple<int, int, bool>> st;
        st.push_back({0, 0, false});

        while (!st.empty()) {
            auto [u, p, exit] = st.back();
            st.pop_back();

            if (exit) {
                tout[u] = timer;  // Corrected
                continue;
            }

            tin[u] = ++timer;

            up[0][u] = p;

            for (int j = 1; j < LOG; j++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }

            int bit = 1 << (s[u] - 'a');

            if (u == 0) {
                pref[u] = bit;
            } else {
                pref[u] = pref[p] ^ bit;
            }

            st.push_back({u, p, true});

            for (int v : adj[u]) {
                if (v == p) continue;

                depth[v] = depth[u] + 1;
                st.push_back({v, u, false});
            }
        }

        Fenwick fw(n);

        // LCA function
        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) {
                swap(u, v);
            }

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j)) {
                    u = up[j][u];
                }
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return up[0][u];
        };

        vector<bool> ans;

        for (string& q : queries) {
            string type;
            int u, v;

            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');

                int delta = oldMask ^ newMask;

                fw.rangeUpdate(tin[u], tout[u], delta);

                s[u] = c;
            }
            else {
                ss >> v;

                int w = lca(u, v);

                int maskU = pref[u] ^ fw.query(tin[u]);
                int maskV = pref[v] ^ fw.query(tin[v]);

                int pathMask = maskU ^ maskV
                             ^ (1 << (s[w] - 'a'));

                ans.push_back(
                    (pathMask & (pathMask - 1)) == 0
                );
            }
        }

        return ans;
    }
};
