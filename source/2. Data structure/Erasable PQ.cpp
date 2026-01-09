template <typename T = int, typename Compare = std::less<T>>
struct EraseablePQ {
    priority_queue<T,vector<T>,Compare> q, del;
    void flush() {
        while (!del.empty() && !q.empty() && q.top() == del.top()) {
            q.pop(); del.pop();
        }
    }
    void push(const T& x) { q.push(x); flush(); }
    void erase(const T& x) { del.push(x); flush(); }
    void pop() { flush(); if (!q.empty()) q.pop(); flush(); }
    const T& top() { flush(); return q.top(); }
    int size() const { return int(q.size() - del.size()); }
    bool empty() { flush(); return q.empty(); }
};