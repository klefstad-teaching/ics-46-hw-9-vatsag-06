//
// Created by Vatsa Gupta on 3/7/2025.
//

#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << endl << msg << endl << endl;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d) {
    int ops = 0;
    for (int i = 0; i < min(str1.length(), str2.length()); i++) {
        if (str1[i] != str2[i]) {
            ops++;
        }
    }
    if (str1.length() == str2.length()) {
        if (ops <= d) {
            return true;
        }
    }
    else if (str1.length() != str2.length()) {
        if (ops + abs(int(str1.length()) - int(str2.length())) <= d) {
            return true;
        }
        else {
            cout << "reached inner else for" << endl;
            int incorrect = 0;
            int i = 0, j = 0;
            for (int ct = 0; ct < max(str1.size(), str2.size()); ct++) {
                if (str1[i] == str2[j]) {
                    i ++;
                    j ++;
                    continue;
                }
                else {
                    incorrect++;
                    if (str1.size() > str2.size()) {
                        j --;
                    }
                    else if (str2.size() > str1.size()) {
                        i --;
                    }
                }
                i ++;
                j ++;
            }
            return incorrect <= d;
        }
    }
    return false;
}

bool is_adjacent(const string &word1, const string &word2) {
    if (!edit_distance_within(word1, word2, 1)) {
        return false;
    }
    if (word1 == word2){
        return true;
    }
    int correct = 0;
    int i = 0, j = 0;
    for (int ct = 0; ct < max(word1.size(), word2.size()); ct++) {
        if (word1[i] == word2[j]) {
            correct++;
        }
        else {
            if (word1.size() > word2.size()) {
                i = j + 1;
                i --;
                j --;
            }
            else if (word2.size() > word1.size()) {
                j = i + 1;
                i --;
                j --;
            }
        }
        i ++;
        j ++;
    }
    if (word1.size() == word2.size()) {
        return correct == word1.size() - 1;
    }
    else {
        return correct == min(word1.size(), word2.size());
    }
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
