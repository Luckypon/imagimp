#include "lut.h"
#include "limits.h"



void ajoutLUT(LUT** listeLUT) {
	LUT *temp = *listeLUT;

	LUT *lut = malloc(sizeof(LUT));
	int i;
	for (i = 0; i < 256; i++){
		lut->tabLutR[i] = i;
		lut->tabLutV[i] = i;
		lut->tabLutB[i] = i;
	}
	lut->nextLUT = NULL;
	lut->id = 0;

	if (temp) {
		for (; temp->nextLUT; temp = temp->nextLUT);
		temp->nextLUT = lut;
	}
	else *listeLUT = lut;
}


void augmenteLuminosite(LUT** listeLUT, char id) {
	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		if (i + 10 < 256)  {
			temp->tabLutR[i] = i+10;
			temp->tabLutV[i] = i+10;
			temp->tabLutB[i] = i+10;
		} else {
			temp->tabLutR[i] = 255;
			temp->tabLutV[i] = 255;
			temp->tabLutB[i] = 255;
		}
	}
}

void diminueLuminosite(LUT** listeLUT, char id) {
	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		if (i-10 > 0)  {
			temp->tabLutR[i] = i-10;
			temp->tabLutV[i] = i-10;
			temp->tabLutB[i] = i-10;
		} else {
			temp->tabLutR[i] = 0;
			temp->tabLutV[i] = 0;
			temp->tabLutB[i] = 0;
		}
	}
}

void augmenteContraste(LUT** listeLUT, float histo[], char id) {
	LUT *temp;
	ajoutLUT(listeLUT);

	int min, max;
	 int i = 0;
	while (histo[i] == 0) {
		min = i;
		i++;
	}
	i = 255;
	while (histo[i] == 0) {
		max = i;
		i--;
	}

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int increment = 5;
	for (i  = 0; i < 256; i++) {

		if (i >= min + ((max - min)/2)) {
			if (i+increment < 256) {
				temp->tabLutR[i] = i+increment;
				temp->tabLutV[i] = i+increment;
				temp->tabLutB[i] = i+increment;
			}else {
				temp->tabLutR[i] = 255;
				temp->tabLutV[i] = 255;
				temp->tabLutB[i] = 255;
			}
		}
		else {
			if (i-increment > 0) {
				temp->tabLutR[i] = i-(float)increment;
				temp->tabLutV[i] = i-(float)increment;
				temp->tabLutB[i] = i-(float)increment;
			}else  {
				temp->tabLutR[i] = 0;
				temp->tabLutV[i] = 0;
				temp->tabLutB[i] = 0;
			}
		}
	}
}

void diminueContraste(LUT** listeLUT, float histo[], char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	int min, max;
	int i = 0;
	while (histo[i] == 0) {
		min = i;
		i++;
	}
	i = 255;
	while (histo[i] == 0) {
		max = i;
		i--;
	}


	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int increment = 5;
	for (i  = 0; i < 256; i++) {
		if (i < min + ((max - min)/2)) {
			if (i+increment < 256) {
				temp->tabLutR[i] = i+increment;
				temp->tabLutV[i] = i+increment;
				temp->tabLutB[i] = i+increment;
			}else {
				temp->tabLutR[i] = 255;
				temp->tabLutV[i] = 255;
				temp->tabLutB[i] = 255;
			}
		}
		else {
			if (i-increment > 0) {
				temp->tabLutR[i] = i-increment;
				temp->tabLutV[i] = i-increment;
				temp->tabLutB[i] = i-increment;
			}else  {
				temp->tabLutR[i] = 0;
				temp->tabLutV[i] = 0;
				temp->tabLutB[i] = 0;
			}
		}
	}
}

void inversionCouleur(LUT** listeLUT, char id) {
	LUT *temp;

	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		temp->tabLutR[i] = 255 - i;
		temp->tabLutV[i] = 255 - i;
		temp->tabLutB[i] = 255 - i;
	}

}



void sepia(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		temp->tabLutR[i] = i;
		temp->tabLutV[i] = i/2;
		temp->tabLutB[i] = i/15;
	}
}

void gris(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		temp->tabLutR[i] = i;
	}
}

void augmenterRouge(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		if (i+5 < 256)
			temp->tabLutR[i] = i+5;
		else
			temp->tabLutR[i] = 255;
		temp->tabLutV[i] = i;
		temp->tabLutB[i] = i;
	}
}


void augmenterVert(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		temp->tabLutR[i] = i;

		if (i+5 < 256)
			temp->tabLutV[i] = i+5;
		else
			temp->tabLutV[i] = 255;

		temp->tabLutB[i] = i;
	}
}

void augmenterBleu(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;

	int i;
	for (i  = 0; i < 256; i++) {
		temp->tabLutR[i] = i;
		temp->tabLutV[i] = i;

		if (i+5 < 256)
			temp->tabLutB[i] = i+5;
		else
			temp->tabLutB[i] = 255;
	}
}


void diminuerRouge(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;
	
	int i;
	for (i  = 0; i < 256; i++) {
		if (i-5 > 0)
			temp->tabLutR[i] = i-5;
		else
			temp->tabLutR[i] = 0;
		temp->tabLutV[i] = i;
		temp->tabLutB[i] = i;
	}
}


void diminuerVert(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;
	
	int i;
	for (i  = 0; i < 256; i++) {
		temp->tabLutR[i] = i;

		if (i-5 > 0)
			temp->tabLutV[i] = i-5;
		else
			temp->tabLutV[i] = 0;

		temp->tabLutB[i] = i;
	}
}

void diminuerBleu(LUT** listeLUT, char id) {

	LUT *temp;
	ajoutLUT(listeLUT);

	for (temp = *listeLUT; temp->nextLUT; temp = temp->nextLUT);
	temp->id = id;
	
	int i;
	for (i  = 0; i < 256; i++) {
		temp->tabLutR[i] = i;
		temp->tabLutV[i] = i;

		if (i-5 > 0)
			temp->tabLutB[i] = i-5;
		else
			temp->tabLutB[i] = 0;
	}
}


unsigned char* appliqueLUT(Image *img, LUT **liste_lut) {

	unsigned char *imageLUT = malloc(3*(img->hauteur)*(img->largeur) * sizeof (unsigned char));
	LUT *temp = *liste_lut;
	if (!temp) {
		imageLUT = img->tabPixel;
		return imageLUT;
	}
	int i;
	for (i = 0; i < 3*(img->hauteur)*(img->largeur) ; i++) {
		imageLUT[i] = (img->tabPixel[i]);
	}	


	for (; temp; temp = temp->nextLUT) {
		if (temp->id != 'g') {
			for (i = 0; i+2 <= 3*(img->hauteur)*(img->largeur) ; i = i+3) {
	 			imageLUT[i+0] = temp->tabLutR[ imageLUT[i+0]];
	 			imageLUT[i+1] = temp->tabLutV[ imageLUT[i+1]];
	 			imageLUT[i+2] = temp->tabLutB[ imageLUT[i+2]];
			}
		} else {
			for (i = 0; i+2 <= 3*(img->hauteur)*(img->largeur) ; i = i+3) {
	 			imageLUT[i+0] = temp->tabLutR[imageLUT[i]];
	 			imageLUT[i+1] = temp->tabLutR[imageLUT[i]];
	 			imageLUT[i+2] = temp->tabLutR[imageLUT[i]];
			}
		}	
	}

	return imageLUT;

}



char supprimerDerniereLUT(LUT** listeLUT) {
	
	char typeLut;

	if ((listeLUT)) {
		LUT *temp = *listeLUT;

		int fini = 0;
		while (temp->nextLUT && !fini) {

			if (!temp->nextLUT->nextLUT) {
				typeLut = temp->nextLUT->id;
				free(temp->nextLUT);
				temp->nextLUT = NULL;
				fini = 1;
				return typeLut;
			}
			else temp = temp->nextLUT;
		}
	}

	typeLut = (*listeLUT)->id;
	free(*listeLUT);
	*listeLUT = NULL;

	return typeLut;
}




int supprimerLUT(LUT** listeLUT, int rep, listeHistorique *historique) {
	
	int nbFree = 0;
	char typeLutSupprimee;

	if (*listeLUT) {

		while ((nbFree < rep || rep == -1) && (*listeLUT)->nextLUT) {

			typeLutSupprimee = supprimerDerniereLUT (listeLUT) ;
			nbFree++;
			ajoutListeHistorique (5, (float)typeLutSupprimee , *historique);
		}
	}
	if ((nbFree < rep || rep == -1) && *listeLUT) {
		ajoutListeHistorique (5, (*listeLUT)->id , *historique);
		free(*listeLUT);
		*listeLUT = NULL;
		nbFree++;
	}

	return nbFree;
}

void supprimerTousLUTsansHistorique(LUT** listeLUT) {

	if (*listeLUT) {
		while ((*listeLUT)->nextLUT) {

			supprimerDerniereLUT (listeLUT) ;
		}
	}
	
	if (*listeLUT) {
		free(*listeLUT);
		*listeLUT = NULL;
	}

}
