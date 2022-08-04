class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return (to_string(a) + to_string(b) > to_string(b) + to_string(a));
        });
        string ret; for (int num : nums) ret += to_string(num);
        bool not_all_zero = false; for (int num : nums) not_all_zero = not_all_zero || (num != 0);
        return (not_all_zero ? ret : "0");
    }
};
