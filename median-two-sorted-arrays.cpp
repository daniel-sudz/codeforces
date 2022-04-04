class Solution {
public:
    int count_how_many_less(vector<int>& numx, double x) {
        if (numx.size() == 0 || x < numx[0]) return 0;
        if (x > numx[numx.size() - 1]) return numx.size();
        int low = 0;
        int high = numx.size() - 1;
        while (low < high) {
            int mid = (low + high + 2) / 2;
            if (x < numx[mid]) {
                high = mid - 1;
            }
            else {
                low = mid;
            }
        }
        return low + 1;
    }
    double find_mid_point_pegs(vector<int>& nums1, vector<int>& nums2, bool variant) {
        double low = -10e6; 
        double high = 10e6;
        for (int i = 0; i < 50; i ++) {
            double mid = (low + high) / 2; 
            int how_many_less = count_how_many_less(nums1, mid) + count_how_many_less(nums2, mid);
            if (how_many_less * 2 > nums1.size() + nums2.size()) {
                high = mid;
            }
            else if (how_many_less * 2 == nums1.size() + nums2.size()) {
                if (variant) {
                    high = mid;
                }
                else {
                    low = mid;
                }
            }
            else {
                low = mid;
            }
        }
        return low;
    }
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double pegLeft = find_mid_point_pegs(nums1, nums2, true);
        double pegRight = find_mid_point_pegs(nums1, nums2, false);
        return (pegLeft + pegRight) / 2;
    }
};
