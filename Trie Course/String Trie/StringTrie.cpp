struct TrieNode {
    int cnt_end;            // count of words ending at this node
    int cnt_prefix;         // count of words having this node as proper prefix
    vector<string> wend;    // store all the strings which end at that node
    TrieNode *child[26];
    TrieNode() {
        cnt_end = cnt_prefix = 0;
        for(int i = 0; i < 26; i++) child[i] = nullptr;
    }
};

class StringTrie {
    TrieNode* root;

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
    
    // O(len) --> count of words having given proper prefix
    int search_proper_prefix(string s) {
        TrieNode* curr = root;
        for(int i = 0; i < s.length(); i++) {
            if(curr->child[s[i] - 'a'] == nullptr)
                return 0;
            curr = curr->child[s[i] - 'a'];
        }
        return curr->cnt_prefix;
    }
    
    // O(len) --> exact word frequency
    int search_word(string s) {
        TrieNode* curr = root;
        for(int i = 0; i < s.length(); i++) {
            if(curr->child[s[i] - 'a'] == nullptr)
                return 0;
            curr = curr->child[s[i] - 'a'];
        }
        return curr->cnt_end;
    }
    
    // O(len) --> delete one occurrence of word (if present) 
    void erase(string s) {
        if(search_word(s) == 0) return;  // word not found
        
        TrieNode* curr = root;
        for(int i = 0; i < s.length(); i++) {
            curr->cnt_prefix--;  // decrease prefix count
            curr = curr->child[s[i] - 'a'];
        }
        auto it = find(curr->wend.begin(), curr->wend.end(), s);
        curr->wend.erase(it);
        curr->cnt_end--;
    }
};
