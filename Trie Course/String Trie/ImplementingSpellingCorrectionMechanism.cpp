struct TrieNode {
    int cnt_end;            // count of words ending at this node
    int cnt_prefix;         // count of words having this node as proper prefix
    vector<string> wend;
    TrieNode *child[26];
    TrieNode() {
        cnt_end = cnt_prefix = 0;
        for(int i = 0; i < 26; i++) child[i] = nullptr;
    }
};

class StringTrie {
    TrieNode* root;

    // O(26^k * N) --> DFS to collect words with <= k mismatches compared to s
    void dfs(TrieNode* curr, int pos, string &s, int mismatch, vector<string> &res, int k) {
        if(curr == nullptr || mismatch > k) return;   // prune invalid paths or too many mismatches                  
        if(pos == s.length()) {                       // reached end of query string                  
            for(auto v:curr->wend) res.push_back(v);  // collect all words ending here
            return;
        }
        for(int i=0; i<26; i++) dfs(curr->child[i], pos+1, s, mismatch + (i != s[pos]-'a'), res, k);
    }

public:
    StringTrie() {
        root = new TrieNode();
    }
    
    // O(len) --> insert word into StringTrie
    void add(string s) {
        TrieNode* curr = root;
        for(int i = 0; i < s.length(); i++) {
            curr->cnt_prefix++;
            if(curr->child[s[i] - 'a'] == nullptr) 
                curr->child[s[i] - 'a'] = new TrieNode();
            curr = curr->child[s[i] - 'a'];
        }
        curr->wend.push_back(s);
        curr->cnt_end++;
    }

    // O(26^k * N) --> find all words with <= k mismatches to s
    vector<string> get_K_mismatch_words(string s, int k) {
        vector<string> res;
        dfs(root, 0, s, 0, res, k);
        return res;
    }
};
