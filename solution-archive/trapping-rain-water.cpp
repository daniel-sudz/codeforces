#include "bits/stdc++.h"

using namespace std;

int trap(vector<int> &height) {
    int ret = 0;
    struct stack_element {
        int tower_height;
        int index;
    };
    stack<stack_element> tower_stack;
    for (int i = 0; i < height.size(); i++) {
        stack_element current_tower = stack_element({height[i], i});
        while (tower_stack.size() > 0 && tower_stack.top().tower_height <= current_tower.tower_height) {
            stack_element left_tower = tower_stack.top();
            if (tower_stack.size() > 1) {
                ret -= left_tower.tower_height;
            } else {
                ret += (current_tower.index - left_tower.index - 1) * left_tower.tower_height;
            }
            tower_stack.pop();
        }
        tower_stack.push(current_tower);
    }
    stack_element right_tower;
    if (tower_stack.size() > 0) {
        right_tower = tower_stack.top();
        tower_stack.pop();
    }
    while (tower_stack.size() > 0) {
        stack_element left_tower = tower_stack.top();
        tower_stack.pop();
        ret += (right_tower.index - left_tower.index - 1) * right_tower.tower_height;
        right_tower = left_tower;
    }
    return ret;
}
