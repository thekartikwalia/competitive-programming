struct TrieNode {
    int cnt_end;            // count of words ending at this node
    int cnt_prefix;         // count of words having this node as proper prefix
    TrieNode *child[26];
    TrieNode() {
        cnt_end = cnt_prefix = 0;
        for(int i = 0; i < 26; i++) child[i] = nullptr;
    }
};

class StringTrie {
    TrieNode* root;

    // O(K*S) --> perform DFS in Lex First Order to collect K suffixes
    void dfs(TrieNode* node, string &curr_suffix, vector<string> &res, int k) {
        if(res.size() >= k) return;
        if(node->cnt_end > 0)
            res.push_back(cur_suffix);

        for(int i=0; i<26; i++) {
            if(node->child[i] == nullptr) continue;

            curr_suffix.push_back('a' + i);
            dfs(node->child[i], curr_suffix, res, k);
            curr_suffix.pop_back();

            if(res.size() >= k) return;
        }
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
        curr->cnt_end++;
    }

    // O(P + K*S) --> get top K lexicographically smallest words with given prefix
    vector<string> get_top_k(string prefix, int k) {
        vector<string> res;

        // search the existence of prefix
        TrieNode* curr = root;
        for(int i = 0; i < prefix.length(); i++) {
            if(curr->child[prefix[i] - 'a'] == nullptr)
                return 0;
            curr = curr->child[prefix[i] - 'a'];
        }
        if(curr->cnt_end == 0) return res;

        // perform DFS in Lex First Order to collect K suffixes
        string suffix;
        dfs(curr, suffix, res, k);

        // prepend the prefix to each suffix to form full strings
        for(string &s:res) {
            s = prefix + s;
        }
        return res;
    }
};
