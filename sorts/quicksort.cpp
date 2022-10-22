#include <bits/stdc++.h>
using namespace std;

const int VECTOR_SIZE = 30;
vector<int> v(VECTOR_SIZE);

int get_rand(int from, int to) {
    return rand() % (to - from) + from;
}

vector<int>::iterator partition(vector<int>::iterator from, vector<int>::iterator to) {
    int pivot = *(from + get_rand(0, to - from));
    while (true) {
        while (*from < pivot) ++from;
        while (*to > pivot) --to;
        if (from >= to) return to;
        swap(*from, *to);
        ++from;
        --to;
    }
}

void quick_sort(vector<int>::iterator from, vector<int>::iterator to) {
    if (prev(to) <= from) return;
    auto pivot = partition(from, prev(to));
    quick_sort(from, next(pivot));
    quick_sort(pivot + 1, to);
}

int main() {
    srand(time(nullptr));
    
    for (int i = 0; i < VECTOR_SIZE; i++) {
        v[i] = get_rand(0, 100);
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