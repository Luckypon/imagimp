
#ifndef _GLIMAGIMP__HISTOGRAMME_H___
#define _GLIMAGIMP__HISTOGRAMME_H___

#include "image.h"
#include "calque.h"


int couleurHisto();
float* creationHisto(Calque *calqueCourant, unsigned char *tabHisto, int couleur);
Image *afficherHistogramme (unsigned char *tabHisto, int taille);
void integreHistoSurImage (Image *histo, Calque *calqueCourant, int couleur);

#endif
