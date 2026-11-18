
class Solution {
public:
    int maxNumberOfBalloons(string text) {

        int freq[26] = {0};

        // Count frequency of every character
        for (int i = 0; i < text.length(); i++) {
            freq[text[i] - 'a']++;
        }

        // Calculate how many balloons we can form
        int b = freq['b' - 'a'];
        int a = freq['a' - 'a'];
        int l = freq['l' - 'a'] / 2;
        int o = freq['o' - 'a'] / 2;
        int n = freq['n' - 'a'];

        return min({b, a, l, o, n});
    }
};
