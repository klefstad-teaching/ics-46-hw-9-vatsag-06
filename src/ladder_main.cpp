#include <iostream>
#include <vector>
#include "ladder.h"

using namespace std;

int main() {
    set<string> L;
    load_words(L, "/home/vatsag/A4/ICS 46/ics-46-hw-9-vatsag-06/src/words.txt");
    vector<string> v = generate_word_ladder("cat", "dog", L);
    print_word_ladder(v);
    return 0;
}
