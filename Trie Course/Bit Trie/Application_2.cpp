int MSB = 31;

struct TrieNode {
    int cnt;         // count of binary numbers having this node as prefix
    bool is_end;
    TrieNode *child[2];
    TrieNode() {
        cnt = 0;
        is_end = false;
        child[0] = child[1] = nullptr;
    }
};

class BitTrie {
    TrieNode* root;

public:
    BitTrie() {
        root = new TrieNode();
    }
    
    // O(MSB) --> insert binary number into BitTrie
    void add(int num) {
        TrieNode* curr = root;
        for(int i=MSB; i>=0; i--) {
            int bit = ((num >> i) & 1);
            if(curr->child[bit] == nullptr) 
                curr->child[bit] = new TrieNode();
            curr = curr->child[bit];
            curr->cnt++;
        }
        curr->is_end = true;
    }
    
    // O(MSB) --> find the exact binary number
    bool search(int num) {
        TrieNode* curr = root;
        for(int i=MSB; i>=0; i--) {
            int bit = ((num >> i) & 1);
            if(curr->child[bit] == nullptr) 
                return false;
            curr = curr->child[bit];
        }
        return curr->is_end;
    }
    
    // O(MSB) --> delete binary number (if present) 
    void erase(int num) {
        if(search(num) == 0) return;  // binary number not found
        
        TrieNode* curr = root;
        for(int i=MSB; i>=0; i--) {
            int bit = ((num >> i) & 1);
            curr = curr->child[bit];
            curr->cnt--;
        }
        curr->is_end = false;
    }

    // O(MSB) --> find number of x in trie such that (x^y <= k)
    int get_cnt_x(int y, int k) {
        int ans = 0;
        TrieNode* curr = root;
        for(int i=MSB; i>=0; i--) {
            if(curr == nullptr) break;

            int yb = ((y >> i) & 1);
            int kb = ((k >> i) & 1);

            if(kb) {
                if(curr->child[yb]) {
                    ans += curr->child[yb]->cnt;
                }
                curr = curr->child[yb ^ 1];
            } else {
                curr = curr->child[yb];
            }
        }
        if(curr) ans += curr->cnt;
        return ans;
    }
};
