#include <ncurses.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

// menghapus spasi yg tidk diperlukan
static inline void trim_inplace(string &s) {
    // trim left
    s.erase(s.begin(), find_if(s.begin(), s.end(),
        [](unsigned char ch){ return !isspace(ch); }));
    // trim right
    s.erase(find_if(s.rbegin(), s.rend(),
        [](unsigned char ch){ return !isspace(ch); }).base(), s.end());
}

// baca string dari posisi (y,x) dengan prompt
string nc_getstr(int y, int x, const string &prompt, int maxlen = 100) {
    const int BUF = 256;
    char buf[BUF];
    memset(buf, 0, sizeof(buf));

    // tampilkan prompt
    mvprintw(y, x, "%s", prompt.c_str());
    // tampilkan area input kosong (opsional, bersihkan sisa)
    move(y, x + (int)prompt.length());
    clrtoeol();

    echo();              // tampilkan input user
    curs_set(1);         // tampilkan kursor
    mvgetnstr(y, x + (int)prompt.length(), buf, std::min(maxlen, BUF-1));
    noecho();
    curs_set(0);

    string s(buf);
    trim_inplace(s);
    return s;
}

// baca int dari posisi (y,x) dengan prompt; mengembalikan pair(ok, value)
pair<bool,int> nc_getint(int y, int x, const string &prompt, int maxlen = 20) {
    string str = nc_getstr(y, x, prompt, maxlen);
    if (str.empty()) return {false, 0};
    // coba konversi
    try {
        size_t pos;
        long val = stol(str, &pos);
        if (pos != str.size()) return {false, 0}; // ada karakter non-digit
        return {true, static_cast<int>(val)};
    } catch (...) {
        return {false, 0};
    }
}
