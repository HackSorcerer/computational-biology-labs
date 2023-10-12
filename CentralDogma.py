#!/usr/bin/env python
# coding: utf-8

# In[2]:


genetic_code = {
    'UUU': 'Phenylalanine', 'UUC': 'Phenylalanine', 'UUA': 'Leucine', 'UUG': 'Leucine',
    'UCU': 'Serine', 'UCC': 'Serine', 'UCA': 'Serine', 'UCG': 'Serine',
    'UAU': 'Tyrosine', 'UAC': 'Tyrosine', 'UAA': 'Stop', 'UAG': 'Stop',
    'UGU': 'Cysteine', 'UGC': 'Cysteine', 'UGA': 'Stop', 'UGG': 'Tryptophan',
    'CUU': 'Leucine', 'CUC': 'Leucine', 'CUA': 'Leucine', 'CUG': 'Leucine',
    'CCU': 'Proline', 'CCC': 'Proline', 'CCA': 'Proline', 'CCG': 'Proline',
    'CAU': 'Histidine', 'CAC': 'Histidine', 'CAA': 'Glutamine', 'CAG': 'Glutamine',
    'CGU': 'Arginine', 'CGC': 'Arginine', 'CGA': 'Arginine', 'CGG': 'Arginine',
    'AUU': 'Isoleucine', 'AUC': 'Isoleucine', 'AUA': 'Isoleucine', 'AUG': 'Methionine',
    'ACU': 'Threonine', 'ACC': 'Threonine', 'ACA': 'Threonine', 'ACG': 'Threonine',
    'AAU': 'Asparagine', 'AAC': 'Asparagine', 'AAA': 'Lysine', 'AAG': 'Lysine',
    'AGU': 'Serine', 'AGC': 'Serine', 'AGA': 'Arginine', 'AGG': 'Arginine',
    'GUU': 'Valine', 'GUC': 'Valine', 'GUA': 'Valine', 'GUG': 'Valine',
    'GCU': 'Alanine', 'GCC': 'Alanine', 'GCA': 'Alanine', 'GCG': 'Alanine',
    'GAU': 'Aspartic Acid', 'GAC': 'Aspartic Acid', 'GAA': 'Glutamic Acid', 'GAG': 'Glutamic Acid',
    'GGU': 'Glycine', 'GGC': 'Glycine', 'GGA': 'Glycine', 'GGG': 'Glycine'
}


start_codon = "AUG"
stop_codon_1 = "UAA"
stop_codon_2 = "UAG"
stop_codon_3 = "UGA"

def read_dna_sequence_from_file(file_path):
    with open(file_path, 'r') as file:
      
        dna_sequence = "".join(line.strip() for line in file.readlines())
    return dna_sequence

def dna_to_rna(dna_sequence):
    return dna_sequence.replace('T', 'U')

def translate_rna_to_protein(rna_sequence):
    protein = ''
    i = 0
    while i < len(rna_sequence):
        codon = rna_sequence[i:i + 3]

        if codon == start_codon:
            i += 3
        elif codon in (stop_codon_1, stop_codon_2, stop_codon_3):
            break
        else:
            protein_name = genetic_code.get(codon, 'Unknown')
            protein += protein_name
            i += 3

    return protein

if __name__ == "__main__":
    dna_file_path = "dna_sequence.txt"

   
    dna_sequence = read_dna_sequence_from_file(dna_file_path)

   
    rna_sequence = dna_to_rna(dna_sequence)

    
    has_start_codon = start_codon in rna_sequence

    if has_start_codon:
       
        rna_file_path = "rna.txt"
        with open(rna_file_path, 'w') as rna_file:
            rna_file.write(rna_sequence)

        
        protein_sequence = translate_rna_to_protein(rna_sequence)

       
        print("Protein Sequence:", protein_sequence)

       
        protein_file_path = "protein.txt"
        with open(protein_file_path, 'w') as protein_file:
            protein_file.write(protein_sequence)
    else:
        print("Start codon 'AUG' not found. Protein translation is not possible.")

