#include "fonction.h"

void menuPrincipal(){
	printf("\n-------------------- IMAGE --------------------\n");
	printf("[c] - Charger une image sur un nouveau calque\n");
	printf("[a] - Afficher l'image finale\n");
	printf("[f] - Sauvegarder l'image finale\n");
	printf("-------------------- CALQUES --------------------\n");
	printf("[n] - Ajouter un calque vierge\n");
	printf("[d] - Supprimer le calque courant\n");
	printf("[o] - Modifier l'opacite\n");
	printf("[m] - Modifier le melange des calques\n");
	printf("Fleche haut - Afficher la liste de calques\n");
	printf("Fleche gauche - Aller au calque precedent\n");
	printf("Fleche droite - Aller au calque suivant\n");
	printf("-------------------- HISTOGRAMME--------------------\n");
	printf("[5] - Afficher l'histogramme de l'image\n");
	printf("-------------------- LUT--------------------\n");
	printf("[L] - Augmenter la luminosite\n");
	printf("[l] - Diminuer la luminosite\n");
	printf("[R] - Ajouter du rouge\n");
	printf("[r] - Enlever du rouge\n");
	printf("[V] - Ajouter du vert\n");
	printf("[v] - Enlever du vert\n");
	printf("[B] - Ajouter du bleu\n");
	printf("[b] - Enlever du bleu\n");
	printf("[s] - Mettre en sepia\n");
	printf("[g] - Mettre en noir et blanc\n");
	printf("[i] - Inversion des couleurs\n");
	printf("[+] - Augmenter le contraste\n");
	printf("[-] - Diminuer le contraste\n");
	printf("[9] - Supprimer une ou des LUT\n");
	printf("-------------------------------------------\n");
	printf("[z] - Annuler\n");	
	printf("-------------------------------------------\n");
	printf("[q] - Quitter le programme\n");
	printf("\n----------------------------------------------------------------------\n");
}


void accueil(){
	printf("\n---------------------------------------------\n");
	printf("\nProjet C S2 - Elise RITOUX / Marion VILA\n");
	printf("\n---------------------------------------------\n");
}

int floatToPixel(float nb, int taille){
	int pixel;
	pixel = nb*taille;

	return pixel;
}




void suppressionHistogramme (int *histogramme, Calque **calque_courant, Calque **calqueReferent, listeCalque *liste_calques) {

	if (*histogramme != -1) {

		*calqueReferent = (*calque_courant)->precedent;
		supprimeCalqueCourant(liste_calques, *calque_courant);
		
		*calque_courant = *calqueReferent;
		*histogramme = -1;
	}
}


void fonctionAjoutLut (Calque **calqueReferent, int *histogramme, 
					unsigned char* tabHisto, Calque** calque_courant, Image** imgAffichage, listeHistorique *historique, char c) {

	switch (c) {

		case '+' : 
			printf("-> Augmentation du contraste\n");
			augmenteContraste(&((*calqueReferent)->listeLUT), creationHisto(*calqueReferent, tabHisto, 3), c);
			break;
		case '-' : 
			printf("-> Diminution du contraste\n");
			diminueContraste(&((*calqueReferent)->listeLUT), creationHisto(*calqueReferent, tabHisto, 3), c);
			break;
		case 'L' : 
			printf("-> Augmentation de la luminosite\n");
			augmenteLuminosite(&((*calqueReferent)->listeLUT), c);
			break;
		case 'l' : 
			printf("-> Diminution de la luminosite\n");
			diminueLuminosite(&((*calqueReferent)->listeLUT), c);
			break;
		case 'R' :
			printf("-> Augmentation du rouge\n");
			augmenterRouge(&((*calqueReferent)->listeLUT), c);
			break;
		case 'r' :
			printf("-> Diminution du rouge\n");
			diminuerRouge(&((*calqueReferent)->listeLUT), c);
			break;
		case 'V' :
			printf("-> Augmentation du vert\n");
			augmenterVert(&((*calqueReferent)->listeLUT), c);
			break;
		case 'v' :
			printf("-> Diminution du vert\n");
			diminuerVert(&((*calqueReferent)->listeLUT), c);
			break;
		case 'B' :
			printf("-> Augmentation du bleu\n");
			augmenterBleu(&((*calqueReferent)->listeLUT), c);
			break;
		case 'b' :
			printf("-> Diminution du bleu\n");
			diminuerBleu(&((*calqueReferent)->listeLUT), c);
			break;
		case 's' :
			printf("-> Filtre sepia\n");
			sepia(&((*calqueReferent)->listeLUT), c);
			break;
		case 'g' :
			printf("-> Filtre noir et blanc\n");
			gris(&((*calqueReferent)->listeLUT), c);
			break;
		case 'i' :
			printf("-> Inversion des couleurs\n");
			inversionCouleur(&((*calqueReferent)->listeLUT), c);
			break;
	}

	if (*histogramme != -1) {
		creationHisto(*calqueReferent, tabHisto, *histogramme);
		integreHistoSurImage (afficherHistogramme(tabHisto, (*calque_courant)->img->largeur), *calque_courant, *histogramme);
	}

	actualiseImage(creeImageAvecInfo(*calque_courant, *imgAffichage));				
				
	ajoutListeHistorique (4, c, *historique);
}



void fonctionHistogramme (Calque **calqueReferent, Calque** calque_courant, listeHistorique *historique, 
					unsigned char* tabHisto, int* histogramme, listeCalque *liste_calques, Image** imgAffichage) {
	
	printf("-> Affichage de l'histogramme\n");

	int couleur = couleurHisto();
	creationHisto(*calque_courant, tabHisto, couleur);

	*histogramme = couleur;
	*calqueReferent = *calque_courant;
	*calque_courant = ajoutCalqueVierge(*liste_calques);
	(*calque_courant)->calqueInformation = (*calqueReferent)->num;
	
	integreHistoSurImage (afficherHistogramme(tabHisto, (*calque_courant)->img->largeur), *calque_courant, couleur);

	actualiseImage(creeImageAvecInfo(*calque_courant, *imgAffichage));				
}


void fonctionChangerOpacite (Calque **calqueReferent, Calque** calque_courant, listeHistorique *historique) {
	
	printf("-> Modification de l'opacite du calque courant\n");

	float opacite;
	printf("Veuillez rentrer une valeur entre 0.0 et 1.0 inclue pour changer l'opacite :\n");
	scanf("%f", &opacite);
	char poubelle;
	while((poubelle = getchar ()) != '\n' && poubelle != EOF){}
	if(opacite >= 0.0 && opacite <= 1.0){
		ajoutListeHistorique (2, (*calqueReferent)->melange, *historique);

		opaciteCalque(*calqueReferent, opacite);
		printf("Modification de l'opacite du calque effectue\n");
		actualiseImage(appliqueLUT((*calque_courant)->img, &((*calque_courant)->listeLUT)));
	}else{
		printf("Vous avez rentre une valeur incorrecte\n");
	}
}

void fonctionChangerMelange (Calque **calqueReferent, Calque** calque_courant, listeHistorique *historique) {

	printf("-> Modification du melange du calque courant\n");

	int melange;
	printf("Veuillez 0 pour l'addition et 1 pour la multiplication :\n");
	scanf("%d", &melange);
	char poubelle;
	while((poubelle = getchar ()) != '\n' && poubelle != EOF){}

	if(melange == 0 && melange == 1){
		ajoutListeHistorique (3, (*calqueReferent)->melange, *historique);

		melangeCalque(*calqueReferent, melange);
		printf("Modification du melange du calque effectue\n");
		actualiseImage(appliqueLUT((*calque_courant)->img, &((*calque_courant)->listeLUT)));
	} else {
		printf("Vous avez rentre une valeur incorrecte\n");
	}
}

		
void annuler (listeHistorique historique, Calque **premierCalque, Calque **calque_courant, 
	Calque **calqueReferent, listeCalque *liste_calques, int *histogramme, 
	unsigned char* tabHisto, Image** imgAffichage) {

	if (historique->actionPrecedente) {

		int actionARetablir = historique->actionPrecedente->action;
		float valeurARetablir = historique->actionPrecedente->valeurPrecedente;
		
		/*
			1 : nouveau calque
			2 : retablissement opacité
			3 : retablir melange
			4 : ajout Lut
			5 : retabli les Lut supprimées
			6 : navigue calque gauche
			7 : navigue calque droite
		*/


		switch (actionARetablir) {
			case 1 :	
				printf("Suppression du dernier calque ajoute.\n");
				
				*calque_courant = (*calque_courant)->precedent;	
				supprimeCalqueCourant(premierCalque,(*calque_courant)->suivant);
				calqueReferent = calque_courant;	
				break;
				
			case 2 :
				printf("Retablissement de l'opacite.\n");
				(*calque_courant)->opacite = valeurARetablir;
				break;

			case 3 :
				printf("Retablissement du melange des calques.\n");
				(*calque_courant)->melange = valeurARetablir;
				break;

			case 4 :
				printf("Suppression de la derniere LUT ajoutee.\n");
				supprimerDerniereLUT(&((*calqueReferent)->listeLUT));
				break;

			case 5 :
				printf("Rétablissement des LUT supprimees.\n");

				Historique *temp =  historique->actionPrecedente;
				int nbLutAAjouter = historique->actionPrecedente->valeurPrecedente;
				
				temp = historique->actionPrecedente->actionPrecedente;
				free(historique->actionPrecedente);
				historique->actionPrecedente = temp;

				int i = 0;

				while (i < nbLutAAjouter && temp->action == 5) {

					fonctionAjoutLut(calqueReferent, histogramme, tabHisto, calque_courant, imgAffichage, &historique, (int)temp->valeurPrecedente );
					i++;

					if (i < nbLutAAjouter || temp->actionPrecedente->action == 5) {
						temp = historique->actionPrecedente->actionPrecedente;
						free(historique->actionPrecedente);
						historique->actionPrecedente = temp;
					}
				}

				break;

			case 6 :
				printf("Retour au calque precedent.\n");
				(*calque_courant) = naviguerDansCalque((*calque_courant), 2);
				calqueReferent = calque_courant;
				break;

			case 7 :
				printf("Retour au calque precedent.\n");
				(*calque_courant) = naviguerDansCalque((*calque_courant), 1);
				calqueReferent = calque_courant;
			
		}

		Historique *temp = historique->actionPrecedente->actionPrecedente;
		free(historique->actionPrecedente);
		historique->actionPrecedente = temp;
	}
	else 
		printf("Il n'y a plus d'actions a retablir.\n");
}

void programme(){

	int boucleDebut = 0, i,c, initialisation = 1;
	unsigned int largeurInitial = 0, hauteurInitial = 0;
	unsigned int largeurF = 0, hauteurF = 0;

	int *histogramme = malloc(sizeof(int));
	*histogramme = -1;

	char texte[30][30] = {"supr LUT","contraste -","contraste +","inversion", "noir/blanc","sepia","bleu -","bleu +",
	"vert -","vert +","rouge -","rouge +","lum -","lum +","img finale", "ajout calque", "ajout img",  "supr calque", 
	"melange", "opacite", "infos", "histo", "sav", "annuler"};

	char chemin[100], nom[100], images[100] = "images/";

	accueil();

	Image *image = (Image*)malloc(sizeof(Image));
	Image *imageTest = (Image*)malloc(sizeof(Image));
	Image *imageFinale = (Image*)malloc(sizeof(Image));
	Image *imgAffichage = (Image*)malloc(sizeof(Image));

	listeHistorique historique = initHistorique(historique);

	while(boucleDebut == 0)
		boucleDebut = saisieUtilisateurImage(imageTest, initialisation, largeurInitial, hauteurInitial);

	initialisation = 0;
	
	unsigned char *tabInverse = (unsigned char*)malloc(((imageTest->hauteur)*(imageTest->largeur)*3) * sizeof(unsigned char));
	
	retourneImage(imageTest, tabInverse);
	
	listeCalque liste_calques = ajoutPremierCalque(imageTest, 1, 0);
		
	
	largeurInitial = liste_calques->img->largeur;
	hauteurInitial = liste_calques->img->hauteur;
	largeurF = largeurInitial + largeurInitial*0.5/0.5;
	hauteurF = hauteurInitial;

	Calque *calque_courant = liste_calques;
	Calque* tmpCalque = (Calque*)malloc(sizeof(Calque));

	Calque *calqueReferent = (Calque*)malloc(sizeof(Calque));
	
	//imgAffichage = creationImageFinale(liste_calques);
	
	//actualiseImage(imgAffichage->tabPixel);
	
	calqueReferent = calque_courant;

	
	// GESTION DES TOUCHES

	menuPrincipal();

	unsigned char tabHisto[256]; 

	void saisieClavier(unsigned char c, int x, int y){
		int test = 0;
		char poubelle;
		printf("Touche appuyee : %c\n", c);

		if (c == 'c' || c == 'a' || c == 'f' || c == 'n' || c == 'e' 
			|| c == 'o' || c == 'm') 
 			suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);

		switch(c){
			case 'c':			 
				printf("-> Charger une nouvelle image\n");
				tmpCalque = calque_courant;
				calque_courant = ajoutCalqueVierge(liste_calques);
				opaciteCalque(calque_courant, 1);
				while(test == 0){
	 				test = saisieUtilisateurImage(calque_courant->img,initialisation, largeurInitial, hauteurInitial);
				}
				if(test == 1){ 
					retourneImage(calque_courant->img, tabInverse);
				}else if(test == -1){ // si l'utilisateur veut annuler
					supprimeCalqueCourant(&liste_calques, calque_courant);
					calque_courant = tmpCalque;
				}
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				
				menuPrincipal();
				break;

			case 'a': 
				printf("-> Afficher l'image finale\n");
				imgAffichage = creationImageFinale(liste_calques);
				printf("Toute autre action enlevera cette affichage\n");

				actualiseImage(imgAffichage->tabPixel);
				menuPrincipal();

				break;

			case 'f': 
				printf("-> Sauvegarde de l'image finale\n");
				imgAffichage = creationImageFinale(liste_calques);

				printf("Comment voulez-vous nommer l'image ?\n");
				scanf("%s",nom);
				while((poubelle = getchar ()) != '\n' && poubelle != EOF){}
				retourneImage(imgAffichage, tabInverse);
				strcpy(chemin,images);
				strcat(chemin,strcat(nom,".ppm"));
				
				// Creation de l'image dans une image.ppm
				if(sauvegarderImage(imgAffichage, chemin) == 1){
					printf("\nL'image a bien ete enregistree sous : %s\n", chemin);
				}
				else{
					printf("\nErreur : l'image ne s'est pas enregistree\n");
				}
				retourneImage(imgAffichage, tabInverse);
				while((c = getchar ()) != '\n' && c != EOF){}

				actualiseImage(imgAffichage->tabPixel);
				printf("Toute autre action enlevera cette affichage\n");
				menuPrincipal();

				break;

			case 'n':
				printf("-> Ajout d'un calque vierge\n");					
				ajoutListeHistorique (1, (float)calqueReferent->num,historique);
				calque_courant = ajoutCalqueVierge(liste_calques);
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				menuPrincipal();
				break;


			case 'd': 
				printf("-> Suppression du calque courant\n");

				supprimerLUT(&(calqueReferent->listeLUT), -1, &historique);
				tmpCalque = calque_courant;
				int indiceSuppressionCalque = supprimeCalqueCourant(&liste_calques, calque_courant);

				if(indiceSuppressionCalque == 1){ 
					calque_courant = tmpCalque->suivant;
				}
				else if(indiceSuppressionCalque == 2){
					calque_courant = tmpCalque->precedent;
				}
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				menuPrincipal();
				break;

			case 'o':
				fonctionChangerOpacite (&calqueReferent, &calque_courant, &historique);
				menuPrincipal();
				break;

			case 'm':
				fonctionChangerMelange (&calqueReferent, &calque_courant, &historique);
				menuPrincipal();

				break;

			case '5' : 
				if (*histogramme >= 0) {
					suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);
					actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));

				}
				else
					fonctionHistogramme (&calqueReferent, &calque_courant, &historique,
								 tabHisto, histogramme, &liste_calques, &imgAffichage );


				menuPrincipal();

				break;

			case '+':
			case '-':
			case 'L': 
			case 'l': 
			case 'R': 
			case 'r': 
			case 'V': 
			case 'v': 
			case 'B': 
			case 'b': 
			case 'g':
			case 's': 
			case 'i': 

				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, c);
				menuPrincipal();

				break;

			case '9': 
				printf("-> Suppression de LUT\n");

				if (calqueReferent->listeLUT) {
					int rep;

					if (calqueReferent->listeLUT->nextLUT) {
						printf("Combien de LUT voulez vous supprimer ? (pour toutes les supprimer indiquez -1)\n");
						scanf("%d", &rep);
						while((poubelle = getchar ()) != '\n' && poubelle != EOF){}
					} else rep = 1;

					int nbLutSupprimees = 0;
					nbLutSupprimees = supprimerLUT(&(calqueReferent->listeLUT), rep, &historique);
					ajoutListeHistorique (5, nbLutSupprimees, historique);
				}
				
				else 
					printf("Aucun LUT n'est applique sur ce calque.\n");

				if (*histogramme != -1) {
					creationHisto(calqueReferent, tabHisto, *histogramme);
					integreHistoSurImage (afficherHistogramme(tabHisto, calque_courant->img->largeur), calque_courant, *histogramme);
				}

				actualiseImage(creeImageAvecInfo(calque_courant, imgAffichage));				
				menuPrincipal();
				break;


			case 'q':
				if (histogramme)
					free(histogramme);
				if (image)
					libererImage(image);

				if (imgAffichage->tabPixel)
					free(imgAffichage->tabPixel);
				free(imgAffichage);
				if(imageFinale != NULL)
					libererImage(imageFinale);
				if (liste_calques)
					liste_calques = supprimeListeCalque(liste_calques);
				if(tabInverse != NULL) free(tabInverse);
				printf("Fin du programme\n");
				exit(0);
				break;

			case 'z':
				annuler(historique, &liste_calques, &calque_courant, &calqueReferent, 
							&liste_calques, histogramme, tabHisto, &imgAffichage);
				
				if (*histogramme != -1) {
					creationHisto(calqueReferent, tabHisto, *histogramme);
					integreHistoSurImage (afficherHistogramme(tabHisto, calque_courant->img->largeur), calque_courant, *histogramme);
				}
				
				actualiseImage(creeImageAvecInfo(calque_courant, imgAffichage));				
				menuPrincipal();

				break;

			default:
				printf("Touche inutile\n");
		}
	}

	void saisieClavierSpecial(int c, int x, int y){

		/* la touche SHITF a pour valeur 'q' ou 'p', si on appuie sur shitf , on ne supprime pas l'HISTOGRAMME*/
		if (c != 'q' && c != 'p') {
 			suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);
		}
		printf("%c\n", c);
		switch(c){

			case GLUT_KEY_UP:
			
				printf("-> Affichage des calques\n");

				if(afficheListeCalques(liste_calques, calque_courant));
				
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				menuPrincipal();
			break;

			case GLUT_KEY_LEFT:
				printf("-> Deplacement sur le calque precedent\n");

				calque_courant = naviguerDansCalque(calque_courant, 1);
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				ajoutListeHistorique (6, 0,historique);
				menuPrincipal();
				break;

			case GLUT_KEY_RIGHT:
				printf("-> Deplacement sur le calque suivant\n");
				calque_courant = naviguerDansCalque(calque_courant, 2);
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				ajoutListeHistorique (7, 0, historique);
				menuPrincipal();
				break;
			default:
				printf("Touche inutile\n");
		}
	}
	
	void clickMouse(int button,int state,int x,int y){

		int test = 0;
		char poubelle;
		
		if (state == GLUT_UP)
			{
			if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(0./12.,hauteurF) && y < floatToPixel(1./12.,hauteurF)) {
				/* 	Augmente le rouge	 */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'R');
				menuPrincipal();
			}

			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(1./12.,hauteurF) && y < floatToPixel(2./12.,hauteurF)) {
				/* 	Diminue le rouge	 */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'r');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(2./12.,hauteurF) && y < floatToPixel(3./12.,hauteurF)) {
				/* 	Augmente le vert	 */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'V');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(3./12.,hauteurF) && y < floatToPixel(4./12.,hauteurF)) {
				/* 	Diminue le vert	 */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'v');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(4./12.,hauteurF) && y < floatToPixel(5./12.,hauteurF)) {
				/*	Aumgente le bleu  */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'B');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(5./12.,hauteurF) && y < floatToPixel(6./12.,hauteurF)) {
				/* 	Diminue le bleu	 */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'b');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(6./12.,hauteurF) && y < floatToPixel(7./12.,hauteurF)) {
				/* 	Met en sepia	 */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 's');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(7./12.,hauteurF) && y < floatToPixel(8./12.,hauteurF)) {
				/* 	Met en noir et blanc */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'g');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(8./12.,hauteurF) && y < floatToPixel(9./12.,hauteurF)) {
				/* 	Inversion des couleurs */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'i');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(9./12.,hauteurF) && y < floatToPixel(10./12.,hauteurF)) {
				/* 	Augmente le contraste */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, '+');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(10./12.,hauteurF) && y < floatToPixel(11./12.,hauteurF)) {
				/* 	Diminue le contraste */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, '-');
				menuPrincipal();
			}
			else if(x > largeurInitial && x < floatToPixel(0.75,largeurF) && y > floatToPixel(11./12.,hauteurF) && y < floatToPixel(12./12.,hauteurF)) {
				printf("-> Suppression de LUT\n");
				
				if (calqueReferent->listeLUT) {
					int rep;

					if (calqueReferent->listeLUT->nextLUT) {
						printf("Combien de LUT voulez vous supprimer ? (pour toutes les supprimer indiquez -1)\n");
						scanf("%d", &rep);
						while((poubelle = getchar ()) != '\n' && poubelle != EOF){}
					} else rep = 1;

					int nbLutSupprimees = 0;
					nbLutSupprimees = supprimerLUT(&(calqueReferent->listeLUT), rep, &historique);
					ajoutListeHistorique (5, nbLutSupprimees, historique);
				}
				
				else 
					printf("Aucun LUT n'est applique sur ce calque.\n");

				if (*histogramme != -1) {
					creationHisto(calqueReferent, tabHisto, *histogramme);
					integreHistoSurImage (afficherHistogramme(tabHisto, calque_courant->img->largeur), calque_courant, *histogramme);
				}

				actualiseImage(creeImageAvecInfo(calque_courant, imgAffichage));	
				menuPrincipal();
				
			}
			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(0./12.,hauteurF) && y < floatToPixel(1./12.,hauteurF)) {
				printf("-> Annuler\n");				
				annuler (historique, &liste_calques, &calque_courant, &calqueReferent, &liste_calques, histogramme, tabHisto, &imgAffichage);
				
				if (*histogramme != -1) {
					creationHisto(calqueReferent, tabHisto, *histogramme);
					integreHistoSurImage (afficherHistogramme(tabHisto, calque_courant->img->largeur), calque_courant, *histogramme);
				}
				
				actualiseImage(creeImageAvecInfo(calque_courant, imgAffichage));				

				menuPrincipal();
		
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(1./12.,hauteurF) && y < floatToPixel(2./12.,hauteurF)) {
 				suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);

				printf("-> Sauvegarde de l'image finale\n");
				imgAffichage = creationImageFinale(liste_calques);

				printf("Comment voulez-vous nommer l'image ?\n");
				scanf("%s",nom);
				while((poubelle = getchar ()) != '\n' && poubelle != EOF){}
				retourneImage(imgAffichage, tabInverse);
				strcpy(chemin,images);
				strcat(chemin,strcat(nom,".ppm"));
				
				// Creation de l'image dans une image.ppm
				if(sauvegarderImage(imgAffichage, chemin) == 1){
					printf("\nL'image a bien ete enregistree sous : %s\n", chemin);
				}
				else{
					printf("\nErreur : l'image ne s'est pas enregistree\n");
				}
				retourneImage(imgAffichage, tabInverse);
				while((c = getchar ()) != '\n' && c != EOF){}

				actualiseImage(imgAffichage->tabPixel);
				printf("Toute autre action enlevera cette affichage\n");
				menuPrincipal();
				
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(2./12.,hauteurF) && y < floatToPixel(3./12.,hauteurF)) {
	 			/* 	Affiche l'histogramme */
				if (*histogramme >= 0) {
					suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);
					actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));

				}
				else
					fonctionHistogramme (&calqueReferent, &calque_courant, &historique,
								 tabHisto, histogramme, &liste_calques, &imgAffichage );

				menuPrincipal();
				
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(3./12.,hauteurF) && y < floatToPixel(4./12.,hauteurF)) {

				printf("-> Affichage des calques\n");

				if(afficheListeCalques(liste_calques, calque_courant));
				menuPrincipal();
				
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(4./12.,hauteurF) && y < floatToPixel(5./12.,hauteurF)) {
				/* 	Modifie l'opacite */
				suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);
				fonctionChangerOpacite (&calqueReferent, &calque_courant, &historique);
				menuPrincipal();
				
				
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(5./12.,hauteurF) && y < floatToPixel(6./12.,hauteurF)) {
				/* 	Modifie le melange */
				suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);
				fonctionChangerMelange (&calqueReferent, &calque_courant, &historique);
				menuPrincipal();
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(6./12.,hauteurF) && y < floatToPixel(7./12.,hauteurF)) {

				printf("-> Suppression du calque courant\n");
				supprimerLUT(&(calqueReferent->listeLUT), -1, &historique);

				tmpCalque = calque_courant;
				int indiceSuppressionCalque = supprimeCalqueCourant(&liste_calques, calque_courant);

				if(indiceSuppressionCalque == 1){ 
					calque_courant = tmpCalque->suivant;
				}
				else if(indiceSuppressionCalque == 2){
					calque_courant = tmpCalque->precedent;
				}
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				menuPrincipal();
				
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(7./12.,hauteurF) && y < floatToPixel(8./12.,hauteurF)) {
 				suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);

				printf("-> Charger une nouvelle image\n");
				tmpCalque = calque_courant;
				calque_courant = ajoutCalqueVierge(liste_calques);
				opaciteCalque(calque_courant, 1);
				while(test == 0){
	 				test = saisieUtilisateurImage(calque_courant->img,initialisation, largeurInitial, hauteurInitial);
				}
				if(test == 1){ 
					retourneImage(calque_courant->img, tabInverse);
				}else if(test == -1){ // si l'utilisateur veut annuler
					supprimeCalqueCourant(&liste_calques, calque_courant);
					calque_courant = tmpCalque;
				}
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));
				
				menuPrincipal();		
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(8./12.,hauteurF) && y < floatToPixel(9./12.,hauteurF)) {
	 			suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);

				printf("-> Ajout d'un calque vierge\n");				
			
				ajoutListeHistorique (1, (float)calqueReferent->num,historique);
				calque_courant = ajoutCalqueVierge(liste_calques);
				calqueReferent = calque_courant;
				actualiseImage(appliqueLUT(calque_courant->img, &(calque_courant->listeLUT)));

				menuPrincipal();
	
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(9./12.,hauteurF) && y < floatToPixel(10./12.,hauteurF)) {
	 			suppressionHistogramme (histogramme, &calque_courant, &calqueReferent, &liste_calques);

				printf("-> Afficher l'image finale\n");
				imgAffichage = creationImageFinale(liste_calques);
				printf("Toute autre action enlevera cette affichage\n");

				actualiseImage(imgAffichage->tabPixel);
				menuPrincipal();
			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(10./12.,hauteurF) && y < floatToPixel(11./12.,hauteurF)) {
				/* augmente la luminosite */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'L');
				menuPrincipal();

			}

			else if(x > floatToPixel(0.75,largeurF) && x < largeurF && y > floatToPixel(11./12.,hauteurF) && y < floatToPixel(12./12.,hauteurF)) {
				/*	diminue la lumosite */
				fonctionAjoutLut(&calqueReferent, histogramme, tabHisto, &calque_courant, &imgAffichage, &historique, 'l');
				menuPrincipal();
				
	
			}

		}	
	}



	void saisieDessin(){
	
		fixeCouleur(1,1,1);
		for(i = 0; i < 12; i++){
			drawCarreVide(0.5, i/12. , 0.75, (i+1)/12.);
			writeString(0.52, i/12. + 0.028, texte[i]);
		} 

		for(i = 0; i < 12; i++){
			drawCarreVide(0.75, i/12. , 1, (i+1)/12.);
			writeString(0.77, i/12. + 0.03, texte[i+12]);
		} 
	}
	

	fixeFonctionClavier(saisieClavier);

	fixeFonctionClavierSpecial(saisieClavierSpecial);

	fixeFonctionDessin(saisieDessin);

	fixeFonctionClicSouris(clickMouse);

	initGLIMAGIMP_IHM(largeurInitial, hauteurInitial ,liste_calques->img->tabPixel, largeurF, hauteurF);


	if (histogramme)
		free(histogramme);
	if (image)
		libererImage(image);
	if (imageFinale)
		libererImage(imageFinale);
	if (imgAffichage)
		libererImage(imgAffichage);
	if (liste_calques)
		liste_calques = supprimeListeCalque(liste_calques);
	if(tabInverse != NULL) free(tabInverse);

}
