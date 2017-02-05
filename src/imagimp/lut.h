
#ifndef _GLIMAGIMP__LUT_H___
#define _GLIMAGIMP__LUT_H___

#include "image.h"
#include "historique.h"

//structure LUT
typedef struct LUT{
	// Définition de 3 tableaux pour le rouge, le vert et le bleu
	unsigned char tabLutR[256];
	unsigned char tabLutV[256];
	unsigned char tabLutB[256];
	struct LUT* nextLUT;
	char id; /* 	identifie la lut, utile pour l'historique	*/
} LUT;

// Ajoute une lut(LUT_1)
void ajoutLUT(LUT** listeLUT);

// Applique une LUT a une image (LUT_2)
unsigned char* appliqueLUT(Image *img, LUT **liste_lut);

// Augmentation de luminosité (ADDLUM) dépend d'un parametre
void augmenteLuminosite(LUT** listeLUT, char id);

// Diminution de luminosité (DIMLUM) dépend d'un parametre
void diminueLuminosite(LUT** listeLUT, char id);

// Augmentation de contraste (ADDCON) dépend d'un parametre
void augmenteContraste(LUT** listeLUT, float histo[], char id);

// Diminution de contraste (DIMCON) dépend d'un parametre
void diminueContraste(LUT** listeLUT, float histo[], char id);

// Inversion de couleur (INVERT)
void inversionCouleur(LUT** listeLUT, char id);

// Effet Sepia (SEPIA) dépend d'un ou plusieurs parametre
void sepia(LUT** listeLUT, char id);
void gris(LUT** listeLUT, char id);

void augmenterRouge(LUT** listeLUT, char id);
void augmenterVert(LUT** listeLUT, char id);
void augmenterBleu(LUT** listeLUT, char id);

void diminuerRouge(LUT** listeLUT, char id);
void diminuerVert(LUT** listeLUT, char id);
void diminuerBleu(LUT** listeLUT, char id);

char supprimerDerniereLUT(LUT** listeLUT);
int supprimerLUT(LUT** listeLUT, int rep, listeHistorique *historique);
// supprime les luts sans l'ajouter à l'historique, pour la création de l'image finale
void supprimerTousLUTsansHistorique(LUT** listeLUT);

#endif
