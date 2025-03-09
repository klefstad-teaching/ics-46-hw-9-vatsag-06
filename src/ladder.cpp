//
// Created by Vatsa Gupta on 3/7/2025.
//

#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << endl << msg << endl << endl;
}

#define my_assert(e) (std::cout << #e << ((e) ? " passed" : " failed") << std::endl);

void verify_word_ladder() {
    std::set<std::string> word_list;
    load_words(word_list, "/home/vatsag/A4/ICS 46/ics-46-hw-9-vatsag-06/src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("matry", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
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
            else if (str1[i-1] == str2[j-1]) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int mintemp = min(matrix[i-1][j], matrix[i][j-1]);
                matrix[i][j] = 1 + min(mintemp, matrix[i-1][j-1]);
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
    vector<string> NA;
    return NA;
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
    if (ladder.size() == 0){
        cout << "No word ladder found.";
    }
    else{
        cout << "Word ladder found: ";
        for (int i = 0; i < ladder.size(); i++) {
            cout << ladder[i] << " ";
        }
    }
    cout << endl;
}
