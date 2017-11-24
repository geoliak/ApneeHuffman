#ifndef __BONUS__
#define __BONUS__

#include <stdio.h>
#include "huffman_code.h"
#include "arbrebin.h"

void bonus2_ConstruireTableOcc(int *TableOcc, FILE *fichier);
void bonus1_Encoder(FILE* fichier, FILE* fichier_encode, Arbre ArbreHuffman, struct code_char* HuffmanCode);


#endif
