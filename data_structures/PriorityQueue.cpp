#include <vector>
using namespace std;

class PriorityQueue {
   private:
    int n;
    vector<int> A;

    int l(int p) { return (p << 1); }
    int r(int p) { return (p << 1) + 1; }
    int p(int c) { return (c >> 1); }

    // Function that returns true if a should be put after b
    // In other words, if cmp(a, b) == true, then b will be 
    // closer to the top of PriorityQueue
    bool cmp(int a, int b) { return a < b; }

    void bubble_up(int i) {
        if (i == 1) return;

        if (cmp(A[p(i)], A[i])) {
            swap(A[i], A[p(i)]);
            bubble_up(p(i));
        }
    }
    void bubble_down(int i) {
        if (l(i) >= n) return;
        else if (r(i) >= n) {
            if (cmp(A[i], A[l(i)])) swap(A[i], A[l(i)]);
        } else {
            int next = -1;

            if (cmp(A[i], A[l(i)]) && cmp(A[i], A[r(i)])) next = (cmp(A[l(i)], A[r(i)]) ? r(i) : l(i));
            else if (cmp(A[i], A[l(i)])) next = l(i);
            else if (cmp(A[i], A[r(i)])) next = r(i);

            if (next != -1) {
                swap(A[i], A[next]);
                bubble_down(next);
            }
        }
    }
   public:
    PriorityQueue() {
        n = 1;
        A = vector<int>(1);
    }

    int size() { return n - 1; }
    bool empty() { return (n == 1);}
    int top() { return (A.size() < 2 ? 0 : A[1]); }
    void push(int a) {
        if (n >= A.size()) A.resize(A.size() << 1);
        A[n] = a;
        bubble_up(n);
        ++n;
    }
    void remove(int a) {
        if (empty()) return;
        for (int i = 1; i <= n; i++) {
            if (A[i] == a) {
                --n;
                swap(A[i], A[n]);
                bubble_down(i);
                break;
            }
        }
    }
    void pop() { remove(top()); }
};