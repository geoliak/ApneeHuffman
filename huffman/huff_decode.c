#include <stdio.h>
#include "arbrebin.h"
#include "bfile.h"
#include "assert.h"

FILE * fichier_encode;
FILE * fichier_decode;

Arbre ArbreHuffman;

void Decoder() {
	BFILE *bitfile;
	int bit;
	Arbre parcours;
	
	ArbreHuffman = LireArbre(fichier_encode);
	AfficherArbre(ArbreHuffman);
	bitfile = bstart(fichier_encode,"r");
	parcours = ArbreHuffman;
	
	while(!feof(fichier_encode)){
		bit = bitread(bitfile);

		if(bit == 0)
			parcours = FilsGauche(parcours);
		else
			parcours = FilsDroit(parcours);

		if(EstVide(FilsGauche(parcours)) && EstVide(FilsDroit(parcours))){
			fputc((int)Etiq(parcours),fichier_decode);
			parcours = ArbreHuffman;
		}
	}
}

int main(int argc, char * argv[]) {
	fichier_encode = fopen(argv[1], "r");
	fichier_decode = fopen(argv[2], "w");

	Decoder();

	fclose(fichier_encode);
	fclose(fichier_decode);
  
	return 0;
}