#include<iostream>
#include<string>
using namespace std;

void get_next(string t, int* next) {
    next[0] = -1;
    int j;
    for (int i = 1; i < t.length(); ++i) {
        j = i - 1;
        while(j >= 0 && t[next[j]+1]!=t[i]) j = next[j];
        if (j < 0) next[i] = -1;
        else next[i] = next[j] + 1;
    }
}

int kmp(string s, string t) {
    int* next = new int[t.length()];
    get_next(t, next);

    int i = 0, j = 0;
    while(i < s.length() && j < t.length()) {
        if (t[j]==s[i]) {
            ++i; ++j;
        }
        else if (j == 0) ++i;
            else j = next[j-1] + 1;
    }

    delete[] next;

    if (j == t.length()) return i - j;
    else return -1;
}

int main() {
    string s = "abaabaabacacaabaabcc";
    string t = "abaabc";
    cout << kmp(s,t) << endl;
    return 0;
}