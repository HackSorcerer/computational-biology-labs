#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to make the scoring matrix
vector<vector<double>> make_matrix(double g, double Score_p, double Score_n, string seq1, string seq2) {
    int l1 = seq1.length() + 1; // columns
    int l2 = seq2.length() + 1; // rows

    vector<vector<double>> scoring_matrix(l2, vector<double>(l1, 0.0));

    for (int col = 1; col < l1; col++) {
        scoring_matrix[0][col] = scoring_matrix[0][col - 1] - g;
    }

    for (int row = 1; row < l2; row++) {
        scoring_matrix[row][0] = scoring_matrix[row - 1][0] - g;
    }

    for (int j = 1; j < l1; j++) {
        for (int i = 1; i < l2; i++) {
            double flag1, flag2, flag3;
            if (seq1[j - 1] == seq2[i - 1]) {
                flag1 = scoring_matrix[i - 1][j - 1] + Score_p;
            } else {
                flag1 = scoring_matrix[i - 1][j - 1] + Score_n;
            }
            flag2 = scoring_matrix[i - 1][j] - g;
            flag3 = scoring_matrix[i][j - 1] - g;
            double x = max(flag1, flag2);
            double flag = max(x, flag3);
            scoring_matrix[i][j] = flag;
        }
    }

    return scoring_matrix;
}

// Function for traceback
pair<string, string> traceback(const vector<vector<double>>& scoring_matrix, double g, double Score_p, double Score_n, const string& seq1, const string& seq2) {
    int len1 = seq1.length() - 1;
    int len2 = seq2.length() - 1;
    int row_index = scoring_matrix.size() - 1;
    int col_index = scoring_matrix[0].size() - 1;

    string new1 = "";
    string new2 = "";

    for (; row_index != 0 && col_index != 0; ) {
        if (seq1[len1] == seq2[len2] && scoring_matrix[row_index - 1][col_index - 1] + Score_p == scoring_matrix[row_index][col_index]) {
            new1 = seq1[len1] + new1;
            new2 = seq2[len2] + new2;
            len1--;
            len2--;
            col_index--;
            row_index--;
        } else if (seq1[len1] != seq2[len2] && scoring_matrix[row_index - 1][col_index - 1] + Score_n == scoring_matrix[row_index][col_index]) {
            new1 = seq1[len1] + new1;
            new2 = seq2[len2] + new2;
            len1--;
            len2--;
            col_index--;
            row_index--;
        } else if (scoring_matrix[row_index][col_index - 1] - g == scoring_matrix[row_index][col_index]) {
            new1 = seq1[len1] + new1;
            new2 = "_" + new2;
            len1--;
            col_index--;
        } else if (scoring_matrix[row_index - 1][col_index] - g == scoring_matrix[row_index][col_index]) {
            new1 = "_" + new1;
            new2 = seq2[len2] + new2;
            len2--;
            row_index--;
        }
    }

    return make_pair(new1, new2);
}

int main() {
    double g, Score_p, Score_n;
    string seq1, seq2;

    // Input values from the user
    cout << "Enter gap penalty (g): ";
    cin >> g;
    cout << "Enter positive match score (Score_p): ";
    cin >> Score_p;
    cout << "Enter negative match score (Score_n): ";
    cin >> Score_n;
    cout << "Enter sequence 1: ";
    cin >> seq1;
    cout << "Enter sequence 2: ";
    cin >> seq2;

    vector<vector<double>> mat = make_matrix(g, Score_p, Score_n, seq1, seq2);

    cout << "Scoring Matrix:" << endl;
    for (const auto& row : mat) {
        for (double value : row) {
            cout << value << '\t';
        }
        cout << endl;
    }

    pair<string, string> alignment = traceback(mat, g, Score_p, Score_n, seq1, seq2);

    cout << "Aligned sequence 1: " << alignment.first << endl;
    cout << "Aligned sequence 2: " << alignment.second << endl;

    return 0;
}
