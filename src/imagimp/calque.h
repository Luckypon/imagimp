#ifndef CALQUE_H_
#define CALQUE_H_

#include "image.h"
#include "lut.h"

// structure Calque
typedef struct Calque{
	Image* img;
	struct Calque* precedent;
	struct Calque* suivant;
	float opacite;	// comprise entre 0 et 1
	int melange; // addition (0) ou multiplication (1)
	int num; 		//numéro du calque, la liste commence à 0
	struct LUT* listeLUT;
	int calqueInformation; //indique si le calque est un calque d'information, si oui, les pixel à 0 seront invisibles

}Calque;

typedef Calque* listeCalque;




// CALQUES
// Ajoute le premier calque en début de programme
Calque* ajoutPremierCalque(Image *image, float opacite, int melange);
// Ajoute un calque vierge multiplicatif d'opacite nulle, insertion a la fin de la liste (CAL_1)
Calque* ajoutCalqueVierge(listeCalque listeCalque);
// Navigue dans les calques (CAL_2)
Calque* naviguerDansCalque(Calque *calqueCourant, int direction);
// Modifie le paramètre d'opacité d'un calque (CAL_3)
void opaciteCalque(Calque* calque, float opacite);
// Modifie la fonction de mélange du calque (addition/ajout) (CAL_4)
void melangeCalque(Calque* calque, int melange);
// Supprimer le calque courant (CAL_5)
int supprimeCalqueCourant(Calque** premierCalque, Calque* calque);
// Supprime la liste de calque (a faire en fin de programme)
listeCalque supprimeListeCalque(listeCalque listeCalques);
// Crée l'image finale
Image* creationImageFinale(Calque* premierCalque);
// Affiche la liste de calques
int afficheListeCalques(listeCalque listeCalques, Calque* calqueInitial);
// Donne les infos du calque
void infosCalque(Calque *calqueCourant, int indiceCalqueInitial);
// Crée une image avec l'histogramme imprime dessus
unsigned char* creeImageAvecInfo(Calque *calque_courant, Image *img);



#endif
