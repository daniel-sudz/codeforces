#include "bits/stdc++.h"

# define ll long long
using namespace std;

int W;
int N;
int MAX_POSSIBILITY = 1;

struct tail_dp {
    bool tail_invalid = false;
    bool tail_multisol = false;
    int tail_value = 0;
};

tail_dp dp(unordered_multiset<int> &cards, int target) {
    vector<vector<int>> states(MAX_POSSIBILITY);
    //for (int i = 0; i < MAX_POSSIBILITY; i ++) states[i].reserve(100);
    for (int card : cards) {
        vector<pair<int, int>> insert_list;
        //insert_list.reserve(100001);
        for (int i = 0; i < states.size(); i++) {
            if (i < MAX_POSSIBILITY && states[i].size() != 0) {
                int new_val = i + card;
                if (new_val <= target /* perf optimization */) {
                    insert_list.push_back(make_pair(new_val, card));
                }
            }
        }
        for (int j = 0; j < insert_list.size(); j++) {
            states[insert_list[j].first].push_back(insert_list[j].second);
        }
        if (card < MAX_POSSIBILITY && card <= target /* perf optimization */) {
            states[card].push_back(card);
        }
    }
    if (target < MAX_POSSIBILITY == false || states[target].size() == 0) {
        return {true, false, 0};
    }
    if (states[target].size() > 1) {
        return {false, true, 0};
    }
    return {false, false, *(states[target].begin())};
}

int main() {
    cin >> W >> N;
    int card_sum = 0;
    unordered_multiset<int> cards;
    vector<int> original_card_list;
    for (int i = 0; i < N; i++) {
        int card;
        cin >> card;
        cards.insert(card);
        original_card_list.push_back(card);
        card_sum += card;
    }
    MAX_POSSIBILITY = card_sum + 1;

    // optimize if we should remove or insert elements
    // since the problem can be solved symmetrically
    bool should_remove = W * 2 > MAX_POSSIBILITY;
    int to_total = should_remove ? card_sum - W : W; // basic heuristic to which might be faster
    // we might have an invalid state (should_remove negative) based on the heuristic above
    // reset optimization if we have an invalid state
    if (should_remove < 0) {
        should_remove = !should_remove;
        to_total = should_remove ? card_sum - W : W;
    }

    unordered_multiset<int> added_cards;

    while (to_total != 0) {
        tail_dp new_tail = dp(cards, to_total);
        if (new_tail.tail_invalid) {
            cout << 0 << endl;
            return 0;
        }
        if (new_tail.tail_multisol) {
            cout << -1 << endl;
            return 0;
        }
        int tail_card = new_tail.tail_value;
        cards.erase(cards.find(tail_card)); // erase on value deletes all duplicate values
        added_cards.insert(tail_card);
        to_total -= tail_card;
    }

    // print out removed cards
    unordered_map<int, set<int>> value_to_index;

    for (int i = 0; i < original_card_list.size(); i++) {
        value_to_index[original_card_list[i]].insert(i);
    }
    vector<int> cout_indexes;

    if (should_remove) {
        for (int value: added_cards) {
            cout_indexes.push_back(*value_to_index[value].begin());
            value_to_index[value].erase(value_to_index[value].begin());
        }
        sort(cout_indexes.begin(), cout_indexes.end());
        for (int value: cout_indexes) {
            cout << value + 1 << " ";
        }
    }
    else {
        for (int i = 0; i < original_card_list.size(); i++) {
            if (added_cards.find(original_card_list[i]) == added_cards.end()) {
                cout << i + 1 << " ";
            } else {
                added_cards.erase(added_cards.find(original_card_list[i])); // erase on value deletes all duplicate values
            }
        }
    }
}
