class Solution {
    bool dfs(string bottom, vector<string>& allowed) {
        if (bottom.size() == 1) return true;

        string next = "";
        return build(0, bottom, next, allowed);
    }

    bool build(int idx, string& bottom, string& next, vector<string>& allowed) {
        if (idx == bottom.size() - 1) {
            return dfs(next, allowed);
        }

        for (auto &s : allowed) {
            if (s[0] == bottom[idx] && s[1] == bottom[idx + 1]) {
                next.push_back(s[2]);
                if (build(idx + 1, bottom, next, allowed))
                    return true;
                next.pop_back(); // backtrack
            }
        }
        return false;
    }

public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        return dfs(bottom, allowed);
    }
};


//optimzed using hash - map
class Solution {
    unordered_map<string, vector<char>> mp;
    unordered_set<string> bad;  // memo for failed rows

    bool dfs(string bottom) {
        if (bottom.size() == 1) return true;
        if (bad.count(bottom)) return false;

        string next = "";
        if (build(0, bottom, next)) return true;

        bad.insert(bottom); // mark as impossible
        return false;
    }

    bool build(int idx, string &bottom, string &next) {
        if (idx == bottom.size() - 1) {
            return dfs(next);
        }

        string key;
        key.push_back(bottom[idx]);
        key.push_back(bottom[idx + 1]);

        if (mp.find(key) == mp.end()) return false;

        for (char ch : mp[key]) {
            next.push_back(ch);
            if (build(idx + 1, bottom, next))
                return true;
            next.pop_back();
        }
        return false;
    }

public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (auto &s : allowed) {
            mp[s.substr(0,2)].push_back(s[2]);
        }
        return dfs(bottom);
    }
};
