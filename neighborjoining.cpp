#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double calculateNewDistance(double d_ab, double d_am, double d_bm) {
    return 0.5 * (d_ab + d_am - d_bm);
}

void mergeNeighbors(
    vector<vector<double>>& distance_matrix,
    vector<string>& nodes,
    vector<pair<string, string>>& merged_nodes,
    vector<double>& merged_distances) {

    int step = 1;  

    while (nodes.size() > 2) {
        int L = nodes.size();
        vector<string> current_nodes = nodes;
        vector<double> sum_d(L, 0.0);

        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < L; ++j) {
                sum_d[i] += distance_matrix[i][j];
            }
        }

        vector<vector<double>> new_distance_matrix(L, vector<double>(L, 0.0));

        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < L; ++j) {
                new_distance_matrix[i][j] = (L - 2) * distance_matrix[i][j] - sum_d[i] - sum_d[j];
            }
        }

        for (int i = 0; i < L; ++i) {
            new_distance_matrix[i][i] = 0;
        }

        auto min_elem = min_element(new_distance_matrix.begin(), new_distance_matrix.end(), [](const auto& a, const auto& b) {
            return *min_element(a.begin(), a.end()) < *min_element(b.begin(), b.end());
        });

        int row = min_elem - new_distance_matrix.begin();
        int column = min_element(new_distance_matrix[row].begin(), new_distance_matrix[row].end()) - new_distance_matrix[row].begin();

        string node_row = current_nodes[row];
        string node_column = current_nodes[column];
        string new_node = node_row + node_column;
        nodes.erase(nodes.begin() + column);
        nodes.erase(nodes.begin() + row);
        nodes.insert(nodes.begin(), new_node);

        double distance_row_new = 0.5 * (distance_matrix[row][column] + distance_matrix[row][column + 1] - distance_matrix[column +1][column ]);
        double distance_column_new = distance_matrix[row][column] - distance_row_new;

        cout << "Step " << step << ": Merging " << node_row << " and " << node_column << endl;
        cout << "Distance of " << node_row << " from new node " << new_node << " is " << distance_row_new << endl;

       cout << "Distance of " << node_column << " from new node " << new_node << " is " << distance_column_new << endl;

        // Store merged nodes and their distances
        merged_nodes.push_back(make_pair(node_row, node_column));
        merged_distances.push_back(distance_row_new);
        merged_distances.push_back(distance_column_new);

        // Calculate and update the distance of the new node to the remaining nodes
        for (int i = 0; i < L - 2; ++i) {
            if (i != row && i != column) {
                double distance_new_node_other = 0.5 * (distance_matrix[row][i] + distance_matrix[column][i] - distance_matrix[row][column]);
                new_distance_matrix[i].push_back(distance_new_node_other);
            }
        }

        // Store distances between the new node and the remaining nodes
        for (int i = 0; i < L - 2; ++i) {
            double distance_new_node_other = 0.5 * (distance_matrix[row][i] + distance_matrix[column][i] - distance_matrix[row][column]);
            new_distance_matrix[L - 1].push_back(distance_new_node_other);
        }

        new_distance_matrix.push_back(vector<double>(L - 1, 0.0));

        cout << "Updated Distance Matrix:" << endl;
        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < L; ++j) {
                cout << new_distance_matrix[i][j] << " ";
            }
            cout << endl;
        }
        

        step++;
    }
}

int main() {
    vector<vector<double>> distance_matrix = {
        {0, 5, 9, 9, 8},
        {5, 0, 10, 10, 9},
        {9, 10, 0, 8, 7},
        {9, 10, 8, 0, 3},
        {8, 9, 7, 3, 0}
    };

    vector<string> nodes = {"a", "b", "c", "d", "e"};
    vector<pair<string, string>> merged_nodes;
    vector<double> merged_distances;

    mergeNeighbors(distance_matrix, nodes, merged_nodes,  merged_distances);

    return 0;
}
