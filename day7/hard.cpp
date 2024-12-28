#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, string> parent;   // Union-Find parent
        unordered_map<string, string> emailToName; // Email to account name
        unordered_map<string, vector<string>> groups;

        // Initialize union-find
        for (const auto& account : accounts) {
            string name = account[0];
            for (int i = 1; i < account.size(); ++i) {
                parent[account[i]] = account[i];
                emailToName[account[i]] = name;
                if (i > 1) {
                    unionFind(account[i - 1], account[i], parent);
                }
            }
        }

        // Group emails by their root parent
        for (const auto& [email, _] : parent) {
            string root = find(email, parent);
            groups[root].push_back(email);
        }

        // Prepare the result
        vector<vector<string>> result;
        for (auto& [root, emails] : groups) {
            sort(emails.begin(), emails.end());
            emails.insert(emails.begin(), emailToName[root]);
            result.push_back(emails);
        }
        return result;
    }

private:
    string find(string email, unordered_map<string, string>& parent) {
        if (parent[email] != email) {
            parent[email] = find(parent[email], parent); // Path compression
        }
        return parent[email];
    }

    void unionFind(string email1, string email2, unordered_map<string, string>& parent) {
        string root1 = find(email1, parent);
        string root2 = find(email2, parent);
        if (root1 != root2) {
            parent[root2] = root1; // Union
        }
    }
};

int main() {
    Solution sol;
    vector<vector<string>> accounts1 = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}
    };

    vector<vector<string>> accounts2 = {
        {"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe1@m.co"},
        {"Kevin", "Kevin3@m.co", "Kevin5@m.co", "Kevin0@m.co"},
        {"Ethan", "Ethan5@m.co", "Ethan4@m.co", "Ethan0@m.co"},
        {"Hanzo", "Hanzo3@m.co", "Hanzo1@m.co", "Hanzo0@m.co"},
        {"Fern", "Fern5@m.co", "Fern1@m.co", "Fern0@m.co"}
    };

    vector<vector<string>> result1 = sol.accountsMerge(accounts1);
    vector<vector<string>> result2 = sol.accountsMerge(accounts2);

    // Print results
    for (const auto& account : result1) {
        for (const string& email : account) {
            cout << email << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (const auto& account : result2) {
        for (const string& email : account) {
            cout << email << " ";
        }
        cout << endl;
    }

    return 0;
}

