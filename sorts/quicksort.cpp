#include <bits/stdc++.h>
using namespace std;

int get_rand(int from, int to) {
    return rand() % (to - from) + from;
}
vector<int> v;


void quick_sort(vector<int>::iterator from, vector<int>::iterator to) {
    int size = to - from;
    if (size <= 1) return;

    vector<int> small, big;
    int pivot = *(from + get_rand(0, size)), pivot_cnt = 0;
    for (auto it = from; it < to; it++) {
        if (*it < pivot) small.push_back(*it);
        else if (*it > pivot) big.push_back(*it);
        else pivot_cnt += 1;
    }
    int i = 0;
    for (int j = 0; j < small.size(); j++, i++) *(from + i) = small[j];
    for (int j = 0; j < pivot_cnt   ; j++, i++) *(from + i) = pivot;
    for (int j = 0; j < big.size()  ; j++, i++) *(from + i) = big[j];
    int small_size = small.size();
    small.resize(0);
    small.shrink_to_fit();
    big.resize(0);
    big.shrink_to_fit();

    quick_sort(from, from + small_size);
    quick_sort(from + small_size + pivot_cnt, to);
}

int main() {
    srand(time(nullptr));
    const int VECTOR_SIZE = 20;
    
    for (int i = 0; i < VECTOR_SIZE; i++) {
        v.push_back(get_rand(0, 10));
    }
    cout << "Before sort:";
    for (auto&& vi : v) {
        cout << ' ' << vi;
    }
    cout << endl;

    quick_sort(v.begin(), v.end());

    cout << "After sort: ";
    for (auto&& vi : v) {
        cout << ' ' << vi;
    }
    cout << endl;
}