#include "bits/stdc++.h"
# define ll long long
using namespace std;

//  1 ij    2 abc   3 def
//  4 gh    5 kl    6 mn
//  7 prs   8 tuv   9 wxy
//  0 oqz
map<char, int> map_char_to_number = {
        {'i', 1},
        {'j', 1},
        {'a', 2},
        {'b', 2},
        {'c', 2},
        {'d', 3},
        {'e', 3},
        {'f', 3},
        {'g', 4},
        {'h', 4},
        {'k', 5},
        {'l', 5},
        {'m', 6},
        {'n', 6},
        {'p', 7},
        {'r', 7},
        {'s', 7},
        {'t', 8},
        {'u', 8},
        {'v', 8},
        {'w', 9},
        {'x', 9},
        {'y', 9},
        {'o', 0},
        {'q', 0},
        {'z', 0},
};

bool check_solution(int target_start, string &word, vector<int> &target) {
    if (target_start + word.size() > target.size()) return false;
    for (int i = 0; i < word.size(); i++) {
        if (map_char_to_number[word[i]] != target[i + target_start]) {
            return false;
        }
    }
    return true;
}

struct node_state {
    string word_ending;
    int number_of_words;
};

int main() {
    string number_to_decode;
    cin >> number_to_decode;
    while (number_to_decode != "-1") {
        int N;
        cin >> N;

        vector<string> words;
        vector<int> target;
        unordered_map<int, node_state> dp;

        for (int i = 0; i < N; i++) {
            string a;
            cin >> a;
            words.push_back(a);
        }

        for (int i = 0; i < number_to_decode.size(); i++) {
            string phone_number;
            std::stringstream ss;
            ss << number_to_decode[i];
            ss >> phone_number;
            target.push_back(stoi(phone_number));
        }

        dp[0] = {"", 0};
        while (true) {
            bool no_new_states = true;
            for (auto it: dp) {
                for (string word: words) {
                    int loc = it.first;
                    if (check_solution(loc, word, target)) {
                        if (dp[loc + word.size()].word_ending == "" || dp[loc + word.size()].number_of_words > it.second.number_of_words + 1) {
                            dp[loc + word.size()] = {word, it.second.number_of_words + 1};
                            no_new_states = false;
                        }
                    }
                }
            }
            if (no_new_states) {
                break;
            }
        }

        if (dp[target.size()].word_ending != "") {
            // solution exists, print optimal
            vector<string> output_answer;
            int current_loc = target.size();
            while (current_loc != 0) {
                output_answer.push_back(dp[current_loc].word_ending);
                current_loc -= dp[current_loc].word_ending.size();
            }
            for (int i = output_answer.size() - 1; i >= 0; i --) {
                cout << output_answer[i];
                if (i != 0) cout << " ";
            }
            cout << endl;
        }
        else {
            // no solution
            cout << "No solution." << endl;
        }
        cin >> number_to_decode;
    }
}
