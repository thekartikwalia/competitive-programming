int MSB = 31;

struct TrieNode {
    int cnt;
    bool is_end;
    TrieNode* child[2];
    TrieNode() {
        cnt = 0;
        child[0] = child[1] = nullptr;
        is_end = false;
    }
};

class BitTrie {
    TrieNode* root;

public:
    BitTrie() {
        root = new TrieNode();
    }

    // O(MSB) --> insert number bit by bit (MSB -> LSB)
    void add(int num) {
        TrieNode* curr = root;
        for(int i=MSB; i>=0; i--) {
            int bit = ((num >> i) & 1);
            if(curr->child[bit] == nullptr) {
                curr->child[bit] = new TrieNode();
            }
            curr = curr->child[bit];
            curr->cnt++;
        }
        curr->is_end = true;
    }

    // O(MSB) --> find max XOR value possible with given num
    int get_max_xor(int num) {
        int res = 0;
        TrieNode* curr = root;
        for(int i=MSB; i>=0; i--) {
            int bit = ((num >> i) & 1);
            int opp = (bit ^ 1);  // opposite bit gives max xor
            if(curr->child[opp] != nullptr) {
                res |= (1LL << i);  // set this bit in result
                curr = curr->child[opp];
            } else curr = curr->child[bit];
        }
        return res;
    }
};

// O(N) --> find maximum xor pair
int find_maximum_xor_pair(vector<int>& nums) {
    BitTrie tt;
    for(auto v:nums) tt.add(v);  // build trie of all numbers

    int max_xor = 0;
    for(int v:nums) 
        max_xor = max(max_xor, tt.get_max_xor(v));  // compute best pair
    return max_xor;
}
