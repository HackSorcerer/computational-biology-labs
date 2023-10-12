#include <bits/stdc++.h>

using namespace std;

// Define a function to generate k-mers from a sequence
vector<string> kmers(string seq, int k) {
    vector<string> result;
    for (int i = 0; i <= seq.length() - k; ++i) {
        result.push_back(seq.substr(i, k));
    }
    return result;
}

// Define a function to construct the De Bruijn graph
pair<map<string, vector<string>>, map<string, vector<string>>> DeBruijnGraph(vector<string> reads, int k) {
    map<string, vector<string>> dicti;
    vector<vector<string>> E;

    // Iterate through each read in the list of reads
    for (const string& read : reads) {
        vector<string> KMers = kmers(read, k);
        vector<vector<string>> edges;
        for (const string& mer : KMers) {
            vector<string> edge = kmers(mer, k - 1);
            edges.push_back(edge);
        }
        
        // Iterate through the edges and update the dictionaries
        for (const vector<string>& edge : edges) {
            dicti[edge[0]]; // Initialize the dictionary entry
            dicti[edge[1]]; // Initialize the dictionary entry
            dicti[edge[0]].push_back(edge[1]);
            E.push_back(edge);
        }
    }

    map<string, vector<string>> graph;
    for (const auto& entry : dicti) {
        graph[entry.first] = entry.second;
    }

    return make_pair(graph, dicti);
}

int main() {
    vector<string> reads = {"ACG", "CGA", "CGC", "CGT", "GAC", "GCG", "GTA", "TCG"};
    int k = 3;

    // Construct the De Bruijn graph and obtain the graph structure and dictionary
    pair<map<string, vector<string>>, map<string, vector<string>>> result = DeBruijnGraph(reads, k);
    map<string, vector<string>> graph = result.first;
    map<string, vector<string>> dicti = result.second;

    map<string, int> Diff;
    // Calculate the difference between outgoing and incoming edges for each node
    for (const auto& entry : dicti) {
        Diff[entry.first] = entry.second.size();
    }
    for (const auto& entry : dicti) {
        for (const string& neighbor : entry.second) {
            Diff[neighbor]--;
        }
    }

    string startNode = "";
    // Find the starting node with a difference of 1
    for (const auto& entry : Diff) {
        if (entry.second == 1) {
            startNode = entry.first;
            break;
        }
    }

    vector<string> path;

    // Define a function to construct the Eulerian path using a lambda function
    function<void(map<string, vector<string>>&, string)> EulerPath = [&](map<string, vector<string>>& dicti, string node) {
        while (!dicti[node].empty()) {
            string neighbor = dicti[node][0];
            dicti[node].erase(dicti[node].begin());
            EulerPath(dicti, neighbor);
        }
        path.push_back(node);
    };

    if (!startNode.empty()) {
        // Construct the Eulerian path starting from the identified start node
        EulerPath(dicti, startNode);
        reverse(path.begin(), path.end());

        string sequence = path[0];
        for (size_t i = 1; i < path.size(); ++i) {
            sequence += path[i].back();
        }

        cout << sequence << endl;
    } else {
        cout << "No Eulerian path found." << endl;
    }

    return 0;
}
// "CGT", "GAC", "GCG", "ACG", "CGA", "CGC", "GTA", "TCG" 
