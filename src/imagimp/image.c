#include "image.h"

int saisieUtilisateurImage(Image* img, int initialisation, unsigned int largeurInitial, unsigned int hauteurInitial){
	int test;
	char name[100], nameFull[100] = "images/";
	char poubelle;

	printf("Veuillez saisir le nom de l'image situé dans le dossier 'images' a charger (ex : TeaPot.512.ppm)\nPour annuler, taper 'e'\n");
	if(!initialisation)
		printf("Attention, cette nouvelle image doit avoir la même taille que l'image initiale\n"); 
	scanf("%s",name);
	while((poubelle = getchar ()) != '\n' && poubelle != EOF){}
	if(*name == 'e')
		return -1;
	strcat(nameFull,name);
	test = chargerImage(img, nameFull, initialisation, largeurInitial, hauteurInitial);
	return test;
}

int chargerImage(Image* img, char* nom, int initialisation, unsigned int largeurInitial, unsigned int hauteurInitial){	
	FILE* file;
	unsigned int hauteurTmp, largeurTmp, ValMaxTmp;

	file = fopen(nom,"r");
	if(file == NULL){
		printf("Erreur dans l'image\n");
		return 0;
	}
	else{
		// Numéro de variante
		fscanf(file,"%c%c", &(img->numVar[0]), &(img->numVar[1]));
		// Hauteur et Largeur
		if(!initialisation){
			fscanf(file,"%d %d\n%d\n",&largeurTmp, &hauteurTmp, &ValMaxTmp);
			if(largeurTmp != largeurInitial && hauteurTmp != hauteurInitial){
				printf("L'image n'a pas la bonne taille, elle est donc supprimee\n");
				fflush(file);
				fclose(file);
				return -1;
			}else{
				img->largeur = largeurTmp;
				img->hauteur = hauteurTmp;
			}
		}else{
			fscanf(file,"%d %d\n%d\n",&(img->largeur), &(img->hauteur), &(img->valMax));
		}
		
		// On alloue la mémoire en fonction de la taille de l'image
		(img->tabPixel) = (unsigned char*)malloc( ((img->hauteur)*(img->largeur)*3) * sizeof(unsigned char));
		// On récupère tous les pixels dans le tableau tabPixel
		fread (img->tabPixel, sizeof(unsigned char),(img->hauteur)*(img->largeur)*3,file);	
		
		// On ferme le vide le buffer et on ferme le fichier
		fflush(file);
		fclose(file);
		return 1;
	}
}

int sauvegarderImage(Image* img, char* nomImg){
	FILE* file = NULL;
	// On ouvre le fichier avec le droit d'écriture
	file = fopen(nomImg,"w+");
	if(file == NULL){
		printf("Probleme pour sauvegarder l'image\n");
		return 0;
	}
	else{

		// Numéro de variante
		fprintf(file,"%s\n",img->numVar);
		// Hauteur et Largeur , ValMax
		fprintf(file,"%d %d\n%d\n", img->largeur, img->hauteur, img->valMax);
		// On écrit tous les pixels dans l'images à partir du tableau tabPixel
		fwrite(img->tabPixel, sizeof(unsigned char),(img->hauteur)*(img->largeur)*3,file);
		// On ferme le fichier
		fclose(file);
		return 1;
	}
}

int retourneImage(Image *img, unsigned char *tab){
	int i, j=0;
	
	int taille= img->largeur*img->hauteur*3;

	// On parcourt les lignes du tableau à l'envers
	for(i=(img->hauteur); i>0; i--){
		// puis on parcourt les colonnes du tableau
		for(j=0; j<(img->largeur); j++){
			// On retourne le tableau de l'image de haut en bas
			tab[taille - i*img->largeur*3+j*3 +0] = img->tabPixel[i*img->largeur*3+j*3+0];
			tab[taille - i*img->largeur*3+j*3 +1] = img->tabPixel[i*img->largeur*3+j*3+1];
			tab[taille - i*img->largeur*3+j*3 +2] = img->tabPixel[i*img->largeur*3+j*3+2];
	
		}
	}
	
	for (i = 0; i < taille; i++) {
		img->tabPixel[i] = tab[i];
	}
	
	return 1;
}



int libererImage(Image* img){
	if (img) {
		if (img->tabPixel != NULL)
			free(img->tabPixel);
	}

	if(img != NULL){
		free(img);
		return 1;
	}
	else return 0;
}	
