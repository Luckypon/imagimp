#include "histogramme.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int couleurHisto() {
	int repHisto = 0, couleur;
	char poubelle;

	printf("\nVoulez vous afficher l'histogramme sur : \n1-\tle Rouge\n2-\tle Vert \n3-\tle Bleu\n4-\tla luminance globale\n");
	scanf("%d", &repHisto);
	while((poubelle = getchar ()) != '\n' && poubelle != EOF){}

	switch (repHisto) {
		case 1 :
			couleur = 0;
			break;
		case 2 :
			couleur = 1;
			break;
		case 3 :
			couleur = 2;
			break;
		case 4 :
			couleur = 3;
			break;
		default :
			printf("Cette valeur n'est pas affectée. Voici l'histogramme sur l'image gloable\n");
	 		couleur = 3;
	}
	return couleur;
}



float* creationHisto(Calque *calqueCourant, unsigned char *tabHisto, int couleur) {

	int ImageLargeur = calqueCourant->img->largeur;
	int ImageHauteur = calqueCourant->img->hauteur;

	float histo[256];

	int i,j;
	for (j = 0; j < 256; j++) {
		histo[j] = 0;
	}

	unsigned char *imgPourHisto;

	imgPourHisto = appliqueLUT(calqueCourant->img, &(calqueCourant->listeLUT));

	if (couleur != 3) {
		for (i = couleur, j=0; i + 3 < 3*(ImageHauteur * ImageLargeur); i = i+3) {
			histo[imgPourHisto[i]]++;
		}
	}
	else {
		for (i = 0, j=0; i + 3 < 3*(ImageHauteur * ImageLargeur); i = i+3, j++) {
			histo[(imgPourHisto[i+0] + imgPourHisto[i+1] + imgPourHisto[i+2] )/3]++;
		}
	}

	for (j = 0; j < 256; j++) 
		tabHisto[j] = (int)histo[j];

	return histo;
}


Image *afficherHistogramme (unsigned char *tabHisto, int taille) {
	Image *imageHisto = malloc(sizeof(Image));
	imageHisto->hauteur = taille;
	imageHisto->largeur = taille;
	imageHisto->tabPixel = malloc(3*(imageHisto->hauteur)*(imageHisto->largeur) * sizeof(unsigned char));
	
	int i, j;
	for (i = 0; i < 3*(imageHisto->hauteur * imageHisto->largeur); i++) {
		imageHisto->tabPixel[i] = 255;
	}

	int largeurBandeHisto;
	largeurBandeHisto = taille/256;
	
	if (imageHisto->largeur >= 256) {
		for (i = 0; i < imageHisto->largeur; i++) {
			j = 0;
			while (j <= tabHisto[i/largeurBandeHisto] ) {		//SI LA VALEUR POUR LA NUANCE I EST INFERIEUR A LA LIGNE DE I OU ON SE TROUVE

				imageHisto->tabPixel[3* ((j*imageHisto->largeur) + i % imageHisto->largeur ) +0] = 0;
				imageHisto->tabPixel[3* ((j*imageHisto->largeur) + i % imageHisto->largeur ) +1] = 0;
				imageHisto->tabPixel[3* ((j*imageHisto->largeur) + i % imageHisto->largeur ) +2] = 0;
				j++;
			}
		}
	}
	else {
		float tabHistoPlusPetit [imageHisto->largeur];

		for (i = 0; i < imageHisto->largeur; i++) {
			tabHistoPlusPetit[i] = 0;
		}

		largeurBandeHisto = 256/taille;
		int k = 0;
		for (i = 0; i < 255; i++) {
			if (i % largeurBandeHisto)
				k++;

			tabHistoPlusPetit[k] = tabHistoPlusPetit[k] + tabHisto[i];
		}

		for (i = 0; i < imageHisto->largeur; i++) {
			j = 0;
			while (j <= tabHisto[i] ) {		//SI LA VALEUR POUR LA NUANCE I EST INFERIEUR A LA LIGNE DE I OU ON SE TROUVE

				imageHisto->tabPixel[3* ((j*imageHisto->largeur) + i % imageHisto->largeur ) +0] = 0;
				imageHisto->tabPixel[3* ((j*imageHisto->largeur) + i % imageHisto->largeur ) +1] = 0;
				imageHisto->tabPixel[3* ((j*imageHisto->largeur) + i % imageHisto->largeur ) +2] = 0;
				j++;
			}
		}
	}

	return imageHisto;
}


void integreHistoSurImage (Image *histo, Calque *calqueCourant, int couleur) {

	int ImageLargeur = calqueCourant->img->largeur;
	int ImageHauteur = calqueCourant->img->hauteur;

	int i,j;
		
	for(i=0; i<(calqueCourant->img->hauteur*calqueCourant->img->largeur*3); i++){
		calqueCourant->img->tabPixel[i] = 255;
	}

	int r = 0, v = 0, b = 0;
	if (couleur == 0) {
		r = 50;
	}
	else if (couleur == 1) {
		v = 50;
	}
	else if (couleur == 2) {
		b = 50;
	}
	else  {
		r = 50;
		v = 50;
		b = 50;
	}
	for (i = 0; i +2 <= 3*(ImageLargeur); i = i+3) {
		for (j = 0; j+3 < 3*(ImageHauteur); j = j+3) {

			if (!(j+3 > 3*histo->hauteur || (histo->tabPixel[3*(i%ImageLargeur)+(j * ImageLargeur)] == 255))) { 
				calqueCourant->img->tabPixel[3*(i%ImageLargeur)+(j * ImageLargeur)+0] = r;
				calqueCourant->img->tabPixel[3*(i%ImageLargeur)+(j * ImageLargeur)+1] = v;
				calqueCourant->img->tabPixel[3*(i%ImageLargeur)+(j * ImageLargeur)+2] = b;
			}
		}
	}

	free(histo->tabPixel);
	free(histo);
}
