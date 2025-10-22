// O(N) --> pi[i] = length of longest proper prefix of substring s[0...i], which is also a suffix of this substring
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n, 0);

    for (int i = 1; i < n; i++) {
        int j = pi[i-1];                              // length of previous longest prefix-suffix match
        while (j > 0 && s[i] != s[j]) j = pi[j-1];    // fallback to shorter prefix-suffix if mismatch
        if (s[i] == s[j]) j++;                        // extend current prefix-suffix match
        pi[i] = j;                                    // store length of current match
    }

    return pi;
}
