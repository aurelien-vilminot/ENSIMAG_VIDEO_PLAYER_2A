#include <pthread.h>
#include "synchro.h"
#include "ensitheora.h"


extern bool fini;

/* les variables pour la synchro, ici */
pthread_t draw;
pthread_mutex_t mutex_stream_state;
pthread_mutex_t mutex_fenetre;
pthread_cond_t cond_fenetre, cond_fenetre_texture;


/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&mutex_fenetre);
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;
    pthread_cond_signal(&cond_fenetre);
    pthread_mutex_unlock(&mutex_fenetre);
}

void attendreTailleFenetre() {
    pthread_mutex_lock(&mutex_fenetre);
    pthread_cond_wait(&cond_fenetre, &mutex_fenetre);
    pthread_mutex_unlock(&mutex_fenetre);
}

void signalerFenetreEtTexturePrete() {
    pthread_mutex_lock(&mutex_fenetre);
    pthread_cond_signal(&cond_fenetre_texture);
    pthread_mutex_unlock(&mutex_fenetre);
}

void attendreFenetreTexture() {
    pthread_mutex_lock(&mutex_fenetre);
    pthread_cond_wait(&cond_fenetre_texture, &mutex_fenetre);
    pthread_mutex_unlock(&mutex_fenetre);
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
