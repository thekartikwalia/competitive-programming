struct manacher {
    string t;
    vector<int> p;

    // O(N) --> p[i] = radius of longest odd/even palindrome centered at i
    void run_manacher(string s) {
        int n = s.size();
        p.assign(n, 1);
        for(int i=1, l=0, r=0; i<n; i++) {
            if(i <= r) p[i] = min(p[r-i+l], r-i+1);                               // use mirror inside [l, r]
            while(i-p[i] >= 0 && i+p[i] < n && s[i-p[i]] == s[i+p[i]]) p[i]++;    // expand around center i
            if(i+p[i]-1 > r) l = i-p[i]+1, r = i+p[i]-1;                          // update [l, r] if we extended beyond it
        }
    }

    // O(N) --> build transformed string with '#' separators to handle even-length palindromes uniformly
    void build(string s) {
        for(auto v:s) {
            t += string("#") + v;
        }
        t += string("#");

        run_manacher(t);
    }
};
