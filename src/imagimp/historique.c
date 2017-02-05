#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "historique.h"


void ajoutListeHistorique (int action, float valeur, listeHistorique liste) {
	Historique* nouvelleAction = (Historique*)malloc(sizeof(Historique));

	nouvelleAction->action = action;
	nouvelleAction->valeurPrecedente = valeur;
	nouvelleAction->actionPrecedente = liste->actionPrecedente;
	(liste->actionPrecedente) = nouvelleAction;
}


Historique* initHistorique (listeHistorique historique) {

	Historique* premiereAction = (Historique*)malloc(sizeof(Historique));
		
	premiereAction->action = -1;
	premiereAction->valeurPrecedente = -1;
	
	premiereAction->actionPrecedente = NULL;

	return premiereAction;
}
