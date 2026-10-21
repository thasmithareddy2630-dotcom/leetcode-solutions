class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        if (is_sorted(s.begin(), s.end()))
            return 0;

        if (n == 2)
            return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        if (s[0] == mn || s[n - 1] == mx)
            return 1;

        if (s[0] == s[n - 1])
            return 2;

        if (s[0] == mx && s[n - 1] == mn) {
            bool firstRepeated = (s.find(s[0], 1) != string::npos);
            bool lastRepeated = (s.find(s[n - 1]) != s.rfind(s[n - 1]));

            if (!firstRepeated && !lastRepeated)
                return 3;
        }

        return 2;
    }
};