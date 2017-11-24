#include <stdio.h>

#include "arbrebin.h"
#include "bfile.h"
#include "assert.h"

FILE * fichier_encode;

Arbre ArbreHuffman;

void Decoder() {
  AfficherArbre(ArbreHuffman);
  /* A COMPLETER */
  printf("Programme non realise (Decoder)\n");  
}

int main(int argc, char * argv[]) {
  fichier_encode = fopen(argv[1], "r");

  ArbreHuffman = LireArbre(fichier_encode);

  Decoder();

  fclose(fichier_encode);
  
  return 0;
}
