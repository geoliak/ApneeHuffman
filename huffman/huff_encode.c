
#include <stdio.h>
#include "fap.h"
#include "arbrebin.h"
#include "bfile.h"
#include "bonus.h"
#include "huffman_code.h"
#include <assert.h>

FILE * fichier ;
FILE * fichier_encode;

int TableOcc[256] ;
fap file;
Arbre ArbreHuffman;

// Décommentez les lignes suivantes si vous avez réalisé les bonus correspondants
// ATTENTION : les bonus ne seront pris en compte que si le reste fonctionne
// #define BONUS_1 // fonction ConstruireTableOcc

struct code_char HuffmanCode[256];

void  ConstruireTableOcc () {

#ifdef BONUS_1
  int c;

  /* A COMPLETER ... */
  printf("Programme non realise (ConstruireTableOcc)\n");


  c = fgetc(fichier);
  while (c != EOF) {
    /* A COMPLETER ... */
    c = fgetc(fichier);
  } ;
#else
  bonus2_ConstruireTableOcc(TableOcc, fichier);
#endif
  
  int i;
  for (i=0 ; i<256 ; i++) {
    if (TableOcc[i] != 0)  
      printf ("Occurences du caractere %c (code %d) : %d\n",
              i, i, TableOcc[i]) ;
  } ;

}


void InitHuffman() {
  /* A COMPLETER */
	Arbre node = ArbreVide();
	int i=0;

	for (i=0; i<256; i++) {
		if (TableOcc[i] > 0) {
			node = NouveauNoeud(NULL, (char) i, NULL);
			file = inserer(file, node, TableOcc[i]);
		}
		
	} 

  //printf("Programme non realise (InitHuffman)\n");
}

Arbre ConstruireArbre() {
  /* A COMPLETER */
	Arbre tempNode, node1, node2;
	int pr1, pr2;
	while (!(est_fap_vide(file))) {
		file = extraire(file, &node1, &pr1);
		file = extraire(file, &node2, &pr2);
		tempNode = NouveauNoeud(node1, '$', node2);
		if (!(est_fap_vide(file))) 
			file = inserer(file, tempNode, pr1+pr2);
	}

    return tempNode;
}

void saveHuffmanCode(struct code_char source, struct code_char dest, int length) {
  int i=0;
  dest.lg = source.lg;
  for (; i < length; i++) 
    dest.code[i] = source.code[i];
  return;
}

void Parcours(Arbre huff, struct code_char *HuffCode, struct code_char codeArray, int index){
	if(EstVide(FilsGauche(huff)) && EstVide(FilsDroit(huff))){
    saveHuffmanCode(codeArray, HuffCode[(int)Etiq(huff)], codeArray.lg);
    return;
	}
  else {
    codeArray.lg++;
    codeArray.code[index] = 0;
    int indexCopy = index;
    Parcours(FilsGauche(huff), HuffCode, codeArray, indexCopy++);
    codeArray.code[index] = 1;
    Parcours(FilsGauche(huff), HuffCode, codeArray, index++);    
  }
}

void ConstruireCode(Arbre huff) {
	struct code_char code_temp;
	Parcours(huff, HuffmanCode, code_temp, 0);

  //printf("Programme non realise (ConstruireCode)\n");
}

void Encoder() {
  /* A COMPLETER */
  printf("Programme non realise (Encoder)\n");
}
  
int main (int argc, char *argv[]) {

  fichier = fopen (argv[1], "r") ;
  /* Construire la table d'occurences */

  ConstruireTableOcc () ;
  fclose(fichier);

  /* Initialiser la FAP */
  InitHuffman();

  /* Construire l'arbre d'Huffman */
  ArbreHuffman = ConstruireArbre();
  
  AfficherArbre(ArbreHuffman);

  /* Construire la table de codage */
  ConstruireCode(ArbreHuffman);
  
  /* Encodage */
  fichier = fopen (argv[1], "r");
  fichier_encode = fopen(argv[2], "w");

  Encoder();
  
  fclose(fichier_encode);
  fclose(fichier);
  
  return 0 ;
}
