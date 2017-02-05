#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "calque.h"


Calque* ajoutPremierCalque(Image* image, float opacite, int melange){
	Calque* nouveauCalque = (Calque*)malloc(sizeof(Calque));	
	
	nouveauCalque->opacite = opacite;
	nouveauCalque->melange = melange;
	nouveauCalque->num = 0;
	nouveauCalque->calqueInformation = -1;
	
	nouveauCalque->img = image;

	nouveauCalque->precedent = NULL;
	nouveauCalque->suivant = NULL;
	nouveauCalque->listeLUT = NULL;
	return nouveauCalque;
}

Calque* ajoutCalqueVierge(listeCalque listeCalque){
	int numeroTmp = 1;
	Calque* nouveauCalque = (Calque*)malloc(sizeof(Calque));
	Image* nouvelleImage = (Image*)malloc(sizeof(Image));

	nouvelleImage->hauteur = listeCalque->img->hauteur;
	nouvelleImage->largeur = listeCalque->img->largeur;	

	(nouvelleImage->tabPixel) = (unsigned char*)malloc(((nouvelleImage->hauteur)*(nouvelleImage->largeur)*3) * sizeof(unsigned char));
	
	// Remplissage du tableau en blanc
	int i;
	for(i=0; i<(nouvelleImage->hauteur*nouvelleImage->largeur*3); i++){
		nouvelleImage->tabPixel[i] = 255;
	}

	nouveauCalque->img = nouvelleImage;
	nouveauCalque->precedent = NULL;
	nouveauCalque->suivant = NULL;

	nouveauCalque->opacite = 0;
	nouveauCalque->melange = 1;
	nouveauCalque->listeLUT=NULL;

	nouveauCalque->calqueInformation = -1; 	/*	contient des informations sur le calque numero numero*/

	// Ajout à la fin de la liste chainée
	if(listeCalque->suivant != NULL){
		Calque* tmp = listeCalque;
		while(tmp->suivant != NULL){
			tmp = tmp->suivant;
			numeroTmp++;
		}
		nouveauCalque->precedent = tmp;
		tmp->suivant = nouveauCalque;
		nouveauCalque->num = numeroTmp;
	}else{
		nouveauCalque->precedent = listeCalque;
		listeCalque->suivant = nouveauCalque;
		nouveauCalque->num = numeroTmp;
	}

	return nouveauCalque;
}


Calque* naviguerDansCalque(Calque *calqueCourant, int direction){
	// Aller au calque précédent
	if(direction == 1){
		if(calqueCourant->precedent == NULL){
			printf("Il n'y a pas de calque precedent, vous ne pouvez pas vous deplacer\nVous restez au calque %d\n", calqueCourant->num);
			return calqueCourant;
		}else{
			printf("Vous avez recule d'un calque\nVous etes au calque %d\n", calqueCourant->precedent->num);
			return calqueCourant->precedent;
		}
		
	}
	// Aller au calque suivant
	else if(direction == 2){
		if(calqueCourant->suivant == NULL){
			printf("Il n'y a pas de calque suivant, vous ne pouvez pas vous deplacer\nVous restez au calque %d\n", calqueCourant->num);
			return calqueCourant;
		}else{
			printf("Vous avez avance d'un calque\nVous etes au calque %d\n", calqueCourant->suivant->num);
			return calqueCourant->suivant;
		}
	}
	// Erreur
	else{
		printf("Erreur, Vous restez au calque %d\n", calqueCourant->num);
		return calqueCourant;
	}
	

}

void opaciteCalque(Calque* calque, float opacite){
	calque->opacite = opacite;
}

void melangeCalque(Calque* calque, int melange){	
	calque->melange = melange;
}

int supprimeCalqueCourant(Calque** premierCalque, Calque* calque){
	if(calque == NULL){
		printf("Erreur suppression du calque\n");
		return -1;
	}
	if(calque->precedent == NULL){
		//On est sur le premier calque
		if(calque->suivant == NULL){
			printf("La suppression est impossible s'il ne reste qu'un calque\n");
			return 0;
		}else{
			// on veut supprimer le premier calque
			Calque* tmp = calque->suivant;
			while(tmp->suivant != NULL){
				(tmp->num)--;
				tmp = tmp->suivant;
			}
			(tmp->num)--;
			*premierCalque = calque->suivant;
			calque->suivant->precedent = NULL;

			free(calque->img->tabPixel);
			free(calque->img);
			free(calque);

			printf("Le calque courant a ete supprime\n");
			return 1;
		}	
	}else{
		if(calque->suivant == NULL){
			// on veut supprimer le dernier calque
			calque->precedent->suivant = NULL;
			free(calque->img->tabPixel);
			free(calque->img);
			free(calque);
		}else{
			Calque* tmp = calque->suivant;
			while(tmp->suivant != NULL){
				(tmp->num)--;
				tmp = tmp->suivant;
			}
			(tmp->num)--;
			calque->precedent->suivant = calque->suivant;
			calque->suivant->precedent = calque->precedent;
			free(calque->img->tabPixel);
			free(calque->img);
			free(calque);
		}
		printf("Le calque courant a ete supprime\n");
		return 2;
	}
}

listeCalque supprimeListeCalque(listeCalque listeCalques){

	if(listeCalques->suivant == NULL){

		printf("La suppression s'est bien passee\n");
		return NULL;
	}else {
		Calque *tmp;
		tmp = listeCalques->suivant;
		libererImage(listeCalques->img);
		free(listeCalques);
		return supprimeListeCalque(tmp);
	}
}

Image* creationImageFinale(Calque* premierCalque) {
	int i;
	
	Calque* tmp = (Calque*)malloc(sizeof(Calque));
	Image* image = (Image*)malloc(sizeof(Image));

	
	// Creation de la structure de l'image finale
	strcpy(image->numVar,premierCalque->img->numVar);
	image->largeur = premierCalque->img->largeur;
	image->hauteur = premierCalque->img->hauteur;
	image->valMax = premierCalque->img->valMax;
	(image->tabPixel) = (unsigned char*)malloc( ((image->hauteur)*(image->largeur)*3) * sizeof(unsigned char));
		

	image->tabPixel = appliqueLUT(premierCalque->img, &(premierCalque->listeLUT));
  
	tmp = premierCalque;


	// Tant qu'il y a un calque suivant
	while(tmp->suivant != NULL){
		tmp = tmp->suivant;
		tmp->img->tabPixel = appliqueLUT(tmp->img, &(tmp->listeLUT));  
		supprimerTousLUTsansHistorique(&(tmp->listeLUT));

		// Si le melange est égale à 0 on applique la formule d'addition
		if(tmp->melange == 0){
			for(i=0; i < (premierCalque->img->largeur*premierCalque->img->hauteur)*3 ; i+=3){
				image->tabPixel[i+0] = image->tabPixel[i+0] + tmp->opacite * tmp->img->tabPixel[i];
				image->tabPixel[i+1] = image->tabPixel[i+1] + tmp->opacite * tmp->img->tabPixel[i+1];
				image->tabPixel[i+2] = image->tabPixel[i+2] + tmp->opacite * tmp->img->tabPixel[i+2];
			}
		}
		// Sinon, on applique la formule de multiplication
		else{
			for(i=0; i < (premierCalque->img->largeur*premierCalque->img->hauteur)*3 ; i+=3){
				image->tabPixel[i+0] = (1-tmp->opacite)*image->tabPixel[i+0] + (tmp->opacite * tmp->img->tabPixel[i]);
				image->tabPixel[i+1] = (1-tmp->opacite)*image->tabPixel[i+1] + (tmp->opacite * tmp->img->tabPixel[i+1]);
				image->tabPixel[i+2] = (1-tmp->opacite)*image->tabPixel[i+2] + (tmp->opacite * tmp->img->tabPixel[i+2]);
			}
		}
	}
	return image;
}

int afficheListeCalques(listeCalque listeCalques, Calque* calqueInitial){
	if(listeCalques == NULL || calqueInitial == NULL)
		return -1;

	int nbCalques = 1, indiceCalqueInitial = 0;	
	Calque* calqueCourant = listeCalques;

	while(calqueCourant->suivant) {
		if(calqueCourant == calqueInitial)
			indiceCalqueInitial = 1;
		else
			indiceCalqueInitial = 0;
		infosCalque(calqueCourant, indiceCalqueInitial);
		calqueCourant = calqueCourant->suivant;
		nbCalques++;
	}
	if(calqueCourant == calqueInitial)
		indiceCalqueInitial = 1;
	else
		indiceCalqueInitial = 0;
	infosCalque(calqueCourant, indiceCalqueInitial);
	printf("--> Nombre de calques : %d\n", nbCalques);

	return 1;
}

void infosCalque(Calque *calqueCourant, int indiceCalqueInitial){
	if(calqueCourant != NULL){
		if(indiceCalqueInitial == 1)
			printf("SELECTIONNE : Calque numero : %d, opacite : %.2f, melange : %d (0 = addition, 1 = multiplication)\n", calqueCourant->num, calqueCourant->opacite, calqueCourant->melange);
		else
			printf("Calque numero : %d, opacite : %.2f, melange : %d (0 = addition, 1 = multiplication)\n", calqueCourant->num, calqueCourant->opacite, calqueCourant->melange);	
	}else{
		printf("Le calque n'existe pas\n");
	}
}

				
unsigned char* creeImageAvecInfo(Calque *calque_courant, Image *imgAffichage) {

	if (calque_courant->calqueInformation >= 0) {
		int i,j,k, numPixel;
		int ImageLargeur =  calque_courant->img->largeur;
		int ImageHauteur =  calque_courant->img->hauteur;
		imgAffichage->largeur = ImageLargeur;
		imgAffichage->hauteur = ImageHauteur;

		if (imgAffichage->tabPixel == NULL)
			imgAffichage->tabPixel = (unsigned char*)malloc(3*((imgAffichage->hauteur)*(imgAffichage->largeur)) * sizeof(unsigned char));

		Calque *calqueReferent = calque_courant;

		if (calque_courant->calqueInformation >= 0) {
			if (calqueReferent->num > calque_courant->calqueInformation) {
				while(calqueReferent->precedent != NULL && calqueReferent->num != calque_courant->calqueInformation){
					calqueReferent = calqueReferent->precedent;
				}
			}
			else if (calqueReferent->num < calque_courant->calqueInformation) {
				while(calqueReferent->suivant != NULL && calqueReferent->num != calque_courant->calqueInformation){
					calqueReferent = calqueReferent->suivant;
				}
			}
		}

		unsigned char* imgLutImageReferente = appliqueLUT(calqueReferent->img, &(calqueReferent->listeLUT));	

		for (i = 0; i+2 <= 3*(ImageHauteur)*(ImageLargeur) ; i = i+3) {
 			
 			imgAffichage->tabPixel[i+0] = imgLutImageReferente[i+0];
 			imgAffichage->tabPixel[i+1] = imgLutImageReferente[i+1];
 			imgAffichage->tabPixel[i+2] = imgLutImageReferente[i+2];
		}

		int gris;

		for (i = 0; i +2 <= 3*(ImageLargeur); i = i+3) {
			for (j = 0; j+3 < 3*(ImageHauteur); j = j+3) {

				numPixel = 3*(i%ImageLargeur)+(j * ImageLargeur);
				gris = (calque_courant->img->tabPixel[numPixel] + calque_courant->img->tabPixel[numPixel+1] + calque_courant->img->tabPixel[numPixel +2]) / 3;

				if (gris != 255) { 

						for (k = 0 ; k <  3; k++)
							imgAffichage->tabPixel[numPixel+k] = calque_courant->img->tabPixel[numPixel+k];
				}
			}
		}

		return imgAffichage->tabPixel;
	}
	return appliqueLUT(calque_courant->img, &(calque_courant->listeLUT));

}


