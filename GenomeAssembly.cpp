#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to merge DNA strings for genome assembly
string mergeDNAStrings(const vector<string>& dnaStrings) {
    string shortest = "";
    int n = dnaStrings.size();

    for (int i = 0; i < n; ++i) {
        string merged = dnaStrings[i];

        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int overlap = 0;
                int len1 = merged.size();
                int len2 = dnaStrings[j].size();

                for (int k = 1; k <= len1 && k <= len2 && k <= 2; ++k) {
                    if (merged.substr(len1 - k) == dnaStrings[j].substr(0, k)) {
                        overlap = k;
                    }
                }

                merged += dnaStrings[j].substr(overlap);
            }
        }

        if (shortest.empty() || merged.size() < shortest.size()) {
            shortest = merged;
        }
    }

    return shortest;
}

int main() {
    int n;
    cout << "Enter the number of DNA strings: ";
    cin >> n;

    vector<string> dnaStrings(n);

    cout << "Enter the DNA strings:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> dnaStrings[i];
    }

    string result = mergeDNAStrings(dnaStrings);

    cout << "Merged DNA Sequence for Genome Assembly: " << result << endl;

    return 0;
}
