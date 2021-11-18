#include <pthread.h>
#include "synchro.h"
#include "ensitheora.h"


extern bool fini;

/* les variables pour la synchro, ici */
pthread_t draw;
pthread_mutex_t mutexStreamState;


/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;
}

void attendreTailleFenetre() {
}

void signalerFenetreEtTexturePrete() {
}

void attendreFenetreTexture() {
    pthread_join(draw, NULL);
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
