#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> genetic_code = {
    {"UUU", "Phenylalanine"}, {"UUC", "Phenylalanine"}, {"UUA", "Leucine"}, {"UUG", "Leucine"},
    {"UCU", "Serine"}, {"UCC", "Serine"}, {"UCA", "Serine"}, {"UCG", "Serine"},
    {"UAU", "Tyrosine"}, {"UAC", "Tyrosine"}, {"UAA", "Stop"}, {"UAG", "Stop"},
    {"UGU", "Cysteine"}, {"UGC", "Cysteine"}, {"UGA", "Stop"}, {"UGG", "Tryptophan"},
    {"CUU", "Leucine"}, {"CUC", "Leucine"}, {"CUA", "Leucine"}, {"CUG", "Leucine"},
    {"CCU", "Proline"}, {"CCC", "Proline"}, {"CCA", "Proline"}, {"CCG", "Proline"},
    {"CAU", "Histidine"}, {"CAC", "Histidine"}, {"CAA", "Glutamine"}, {"CAG", "Glutamine"},
    {"CGU", "Arginine"}, {"CGC", "Arginine"}, {"CGA", "Arginine"}, {"CGG", "Arginine"},
    {"AUU", "Isoleucine"}, {"AUC", "Isoleucine"}, {"AUA", "Isoleucine"}, {"AUG", "Methionine"},
    {"ACU", "Threonine"}, {"ACC", "Threonine"}, {"ACA", "Threonine"}, {"ACG", "Threonine"},
    {"AAU", "Asparagine"}, {"AAC", "Asparagine"}, {"AAA", "Lysine"}, {"AAG", "Lysine"},
    {"AGU", "Serine"}, {"AGC", "Serine"}, {"AGA", "Arginine"}, {"AGG", "Arginine"},
    {"GUU", "Valine"}, {"GUC", "Valine"}, {"GUA", "Valine"}, {"GUG", "Valine"},
    {"GCU", "Alanine"}, {"GCC", "Alanine"}, {"GCA", "Alanine"}, {"GCG", "Alanine"},
    {"GAU", "Aspartic Acid"}, {"GAC", "Aspartic Acid"}, {"GAA", "Glutamic Acid"}, {"GAG", "Glutamic Acid"},
    {"GGU", "Glycine"}, {"GGC", "Glycine"}, {"GGA", "Glycine"}, {"GGG", "Glycine"}
};

string start_codon = "AUG";
string stop_codon_1 = "UAA";
string stop_codon_2 = "UAG";
string stop_codon_3 = "UGA";

string read_dna_sequence_from_user() {
    string dna_sequence;
    cout << "Enter DNA sequence: ";
    cin >> dna_sequence;
    return dna_sequence;
}

string dna_to_rna(const string& dna_sequence) {
    string rna_sequence = dna_sequence;
    for (char& c : rna_sequence) {
        if (c == 'T') {
            c = 'U';
        }
    }
    return rna_sequence;
}

string translate_rna_to_protein(const string& rna_sequence) {
    string protein = "";
    int i = 0;
    while (i < rna_sequence.size()) {
        string codon = rna_sequence.substr(i, 3);
        if (codon == start_codon) {
            i += 3;
        } else if (codon == stop_codon_1 || codon == stop_codon_2 || codon == stop_codon_3) {
            break;
        } else {
            string protein_name = genetic_code[codon];
            if (protein_name != "") {
                protein += protein_name + " ";
            } else {
                protein += "Unknown ";
            }
            i += 3;
        }
    }
    return protein;
}

int main() {
    string dna_sequence = read_dna_sequence_from_user();
    string rna_sequence = dna_to_rna(dna_sequence);

    if (rna_sequence.find(start_codon) != string::npos) {
        string protein_sequence = translate_rna_to_protein(rna_sequence);
        cout << "RNA Sequence: " << rna_sequence << endl;
        cout << "Protein Sequence: " << protein_sequence << endl;
    } else {
        cout << "Start codon 'AUG' not found. Protein translation is not possible." << endl;
    }

    return 0;
}
