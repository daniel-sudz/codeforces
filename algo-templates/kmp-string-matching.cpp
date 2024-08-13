class Solution {
public:
   struct KMP {
        string p;
        vector<int> lps;
        KMP(string _p): p(_p), lps(_p.size()) {
            for(int i=1;i<lps.size();i++) {
                int j = lps[i-1];
                while(j > 0 && p[j] != p[i]) {
                    j = lps[j-1];
                }
                lps[i] = j + (p[j]==p[i]);
            }
        }
        int match(string s) {
            if(p.size() > s.size()) return -1;
            int j = 0;
            for(int i=0;i<s.size();i++) {
                if(j == p.size()) return i-((int)p.size());
                while(j > 0 && p[j] != s[i]) {
                    j = lps[j-1];
                }
                j += (p[j]==s[i]);
            }
            return (j==p.size() ? s.size()-p.size() : -1);
        }
        
    };
    int strStr(string haystack, string needle) {
        KMP kmp(needle);
        return kmp.match(haystack);
    }
};
