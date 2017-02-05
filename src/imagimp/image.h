#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 

//Structure IMAGE
typedef struct Image {
	char numVar[2]; // Numéro de variante, P5 pour images en noir/blanc, P6 pour images couleurs
	unsigned int hauteur;
	unsigned int largeur;
	unsigned char* tabPixel; 
	int valMax; // Valeur maximale
} Image;

int saisieUtilisateurImage(Image* img, int initialisation, unsigned int largeurInitial, unsigned int hauteurInitial);
int chargerImage(Image* img, char* nom, int initialisation, unsigned int largeurInitial, unsigned int hauteurInitial);
int sauvegarderImage(Image* img, char* nomImg);
int retourneImage(Image *img, unsigned char *tab);
int libererImage(Image* img);



#endif

