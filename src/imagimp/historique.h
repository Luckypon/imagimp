#ifndef _GLIMAGIMP__HISTORIQUE_H___
#define _GLIMAGIMP__HISTORIQUE_H___

typedef struct Historique {
	/*
		1 : nouveau calque
		2 : retablissement opacité
		3 : retablir melange
		4 : ajout Lut
		
		//5 : retablir lut supprimee 
		6 : navigue calque gauche
		7 : navigue calque droite

	*/
	int action; 
	float valeurPrecedente;
	struct Historique *actionPrecedente;

} Historique;

typedef Historique* listeHistorique;


void ajoutListeHistorique (int action, float valeur, listeHistorique liste);
Historique* initHistorique (listeHistorique historique);



#endif
