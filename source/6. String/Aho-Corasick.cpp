struct AhoCorasick {
    struct Node {
        Node *nxt[26], *fail;
        vector<int> out; // 패턴의 인덱스 저장
        int terminal;
        Node() : fail(nullptr), terminal(-1) { fill(nxt, nxt + 26, nullptr); }
        ~Node() {
            for (int i = 0; i < 26; i++) if (nxt[i]) delete nxt[i];
        }
        void insert(const char* s, int id) {
            if (*s == 0) { terminal = id; out.push_back(id); return; }
            int curr = *s - 'a';
            if (!nxt[curr]) nxt[curr] = new Node();
            nxt[curr]->insert(s + 1, id);
        }
    };
    Node* root;
    AhoCorasick() { root = new Node(); }
    ~AhoCorasick() { delete root; }
    void insert(const string& s, int id) { root->insert(s.c_str(), id); }
    void build() {
        queue<Node*> q;
        root->fail = root;
        for (int i = 0; i < 26; i++) {
            if (root->nxt[i]) {
                root->nxt[i]->fail = root;
                q.push(root->nxt[i]);
            } else {
                root->nxt[i] = root; // DFA optimization
            }
        }
        while (!q.empty()) {
            Node* curr = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (curr->nxt[i]) {
                    Node* next = curr->nxt[i];
                    next->fail = curr->fail->nxt[i];
                    next->out.insert(next->out.end(), next->fail->out.begin(), next->fail->out.end());
                    q.push(next);
                } else {
                    curr->nxt[i] = curr->fail->nxt[i]; // DFA optimization
                }
            }
        }
    }
    vector<pair<int, int>> query(const string& s) {
        vector<pair<int, int>> res;
        Node* curr = root;
        for (int i = 0; i < s.size(); i++) {
            curr = curr->nxt[s[i] - 'a'];
            for (int id : curr->out) res.emplace_back(i, id);
        }
        return res;
    }
};
int main() {
    AhoCorasick ac;
    vector<string> patterns = {"he", "she", "hers", "his"};
    for(int i = 0; i < patterns.size(); i++) 
        ac.insert(patterns[i], i); // 패턴과 ID(0~N-1) 삽입
    ac.build(); // 실패 함수/DFA 빌드 (필수)
    string text = "ushers";
    auto res = ac.query(text); // 탐색: {끝 인덱스, 패턴 ID} 쌍 반환
    for (auto& [idx, id] : res) {
        // patterns[id] 가 text의 idx에서 끝남을 의미
    }
}