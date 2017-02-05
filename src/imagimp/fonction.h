#ifndef _GLIMAGIMP__FONCTION_H___
#define _GLIMAGIMP__FONCTION_H___


#include "image.h"
#include "lut.h"
#include "calque.h"
#include "histogramme.h"
#include "historique.h"
#include "../glimagimp/interface.h"
#include "../glimagimp/outils.h"

// Montre le menu principal
void menuPrincipal();
// Montre l'accueil
void accueil();
// Convertit un nombre flottant en pixel selon le taille de l'affichage
int floatToPixel(float nb, int taille);
// Supprime l'histogramme
void suppressionHistogramme (int *histogramme, Calque **calque_courant, Calque **calqueReferent, listeCalque *liste_calques);
// fonction pour ajouter des LUT
void fonctionAjoutLut(Calque **calqueReferent, int *histogramme,unsigned char* tabHisto,
			 Calque** calque_courant, Image** imgAffichage, listeHistorique *historique, char numOperation);
// fonction pour l'histogramme
void fonctionHistogramme (Calque **calqueReferent, Calque** calque_courant, listeHistorique *historique, 
					unsigned char* tabHisto, int* histogramme, listeCalque *liste_calques, Image **imgAffichage);
// fonction pour changer l'opacité
void fonctionChangerOpacite (Calque **calqueReferent, 
					Calque** calque_courant, listeHistorique *historique);
// fonction pour changer le mélange
void fonctionChangerMelange (Calque **calqueReferent, 
					Calque** calque_courant, listeHistorique *historique);
// Fonction pour revenir en arrière
void annuler (listeHistorique historique, Calque **premierCalque, Calque **calque_courant,
		Calque **calqueReferent, listeCalque *liste_calques, int *histogramme, 
		unsigned char* tabHisto, Image** imgAffichage) ;
// fonction principale, qui appelle le programme à partir du main
void programme();




#endif
