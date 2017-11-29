#include <stdio.h>
#include "fap.h"
#include "arbrebin.h"
#include "bfile.h"
#include "bonus.h"
#include "huffman_code.h"
#include <assert.h>
#include <string.h>

FILE * fichier ;
FILE * fichier_encode;

int TableOcc[256] ;
fap file;
Arbre ArbreHuffman;

// Décommentez les lignes suivantes si vous avez réalisé les bonus correspondants
// ATTENTION : les bonus ne seront pris en compte que si le reste fonctionne
// #define BONUS_1 // fonction ConstruireTableOcc

struct code_char HuffmanCode[256];

void Parcours(Arbre huff, struct code_char code_temp);

void  ConstruireTableOcc () {

#ifdef BONUS_1
	int c;

	for(int i = 0; i < 256; i++){
		TableOcc[i] = 0;
	}

	c = fgetc(fichier);
	while (c != EOF) {
		TableOcc[c] = TableOcc[c] + 1;
		c = fgetc(fichier);
	};


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

	Arbre node = ArbreVide();
	int i=0;

	for (i=0; i<256; i++) {
		if (TableOcc[i] > 0) {
			node = NouveauNoeud(NULL, (char) i, NULL);
			file = inserer(file, node, TableOcc[i]);
		}
	} 
}

Arbre ConstruireArbre() {
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


void ConstruireCode(Arbre huff) {

	struct code_char code_temp;
	code_temp.lg = 0;
	Parcours(huff, code_temp);
	
	for(int i = 0; i<256; i++){
		if(HuffmanCode[i].lg!=0){
			printf("\nlg=%d %c code=",HuffmanCode[i].lg,(char)i);
			for(int g=0;g<HuffmanCode[i].lg;g++){
				printf("%d",HuffmanCode[i].code[g]);
			}
			printf("\n");
		}
	}
	
}

void Parcours(Arbre huff, struct code_char code_temp){
	struct code_char a;
	
	if(EstVide(FilsGauche(huff)) && EstVide(FilsDroit(huff))){

		memcpy(a.code,code_temp.code,sizeof(int)*code_temp.lg);
		a.lg = code_temp.lg;
		HuffmanCode[(int)Etiq(huff)] = code_temp;
	}
	else{
		
		if(code_temp.lg!=0)
			memcpy(a.code,code_temp.code,sizeof(int)*(code_temp.lg));
		a.code[code_temp.lg] = 0;
		a.lg = code_temp.lg + 1;
		Parcours(FilsGauche(huff),a);
		
		if(code_temp.lg!=0)
			memcpy(a.code,code_temp.code,sizeof(int)*(code_temp.lg));
		a.code[code_temp.lg] = 1;
		a.lg = code_temp.lg + 1;
		Parcours(FilsDroit(huff),a);		
		
	}

}

void Encoder() {
	struct code_char char_encode;
	BFILE *ecr_bab = bstart(fichier_encode,"w");
	
	EcrireArbre(fichier_encode,ArbreHuffman);

	while(!feof(fichier)){
		int i=0;
		char_encode = HuffmanCode[fgetc(fichier)];
		while(i < char_encode.lg){
			bitwrite(ecr_bab,char_encode.code[i]);
			i++;
		}
	}
	bstop(ecr_bab);
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