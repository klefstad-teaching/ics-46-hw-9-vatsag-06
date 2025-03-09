//
// Created by Vatsa Gupta on 3/7/2025.
//

#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << endl << msg << endl << endl;
}



bool edit_distance_within(const std::string &str1, const std::string &str2, int d) {
    int m = str1.length(), n = str2.length();
    if (abs(int(m-n)) > d) {
        return false;
    }
    vector<vector<int>> matrix(m+1, vector<int>(n+1, 0));
    for (int i = 0; i < m+1; i++) {
        for (int j = 0; j < n+1; j++) {
            if (i == 0) {
                matrix[i][j] = j;
            }
            else if (j == 0) {
                matrix[i][j] = i;
            }
            else if (str1[i] == str2[j]) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                matrix[i][j] = 1 + min({matrix[i-1][j], matrix[i][j-1], matrix[i-1][j-1]});
            }
        }
    }
    return matrix[m][n] <= d;
}

bool is_adjacent(const string &word1, const string &word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    queue<vector<string>> Q;
    vector<string> word;
    if (begin_word == end_word) {
        return word;
    }
    word.push_back(begin_word);
    Q.push(word);
    set<string> visited;
    visited.insert(begin_word);
    while (!Q.empty()) {
        vector<string> lastladder = Q.front();
        Q.pop();
        string w = lastladder.back();
        for (string s: word_list) {
            if (is_adjacent(s, w)) {
                if (!visited.count(s)) {
                    visited.insert(s);
                    vector<string> newladder = lastladder;
                    newladder.push_back(s);
                    Q.push(newladder);
                    if (s == end_word) {
                        return newladder;
                    }
                }
            }
        }
    }
    return Q.front();
}

void load_words(set<string> &word_list, const string &file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string> &ladder) {
    for (int i = 0; i < ladder.size(); i++) {
        cout << ladder[i] << endl;
    }
}
