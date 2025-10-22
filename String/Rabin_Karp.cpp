const long long p = 31;
const long long m = 1e9+9;

vector<int> rabin_karp(string const &s, string const &t) {
    int S = s.size(), T = t.size();

    // O(max(|s|,|t|)) --> compute powers of p 
    vector<long long> p_pow(max(S, T));
    p_pow[0] = 1;
    for(int i=1; i<(int)p_pow.size(); i++) {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    // O(|t|) --> compute hash values for all prefixes of text t
    vector<long long> h(T, 0);    // h[i] now stores hash of prefix t[0..i]
    for(int i=0; i<T; i++) {
        long long add = ((t[i]-'a'+1) * p_pow[i]) % m;
        h[i] = (i == 0 ? add : (h[i-1] + add) % m);
    }

    // O(|s|) --> compute hash value of pattern s
    long long h_s = 0;
    for(int i=0; i<S; i++) {
        h_s = (h_s + (s[i]-'a'+1) * p_pow[i]) % m;
    }

    // O(|t|) --> compare each substring of length |s| with pattern
    vector<int> occurences;
    for(int i=0; i+S-1<T; i++) {
        long long cur_h = h[i+S-1];
        if(i > 0) cur_h = (((cur_h - h[i-1]) % m) + m) % m;

        if(cur_h == (h_s * p_pow[i]) % m) {
            occurences.push_back(i);
        }
    }
    return occurences;
}
