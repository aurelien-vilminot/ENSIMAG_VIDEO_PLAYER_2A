#include <pthread.h>
#include "synchro.h"
#include "ensitheora.h"


extern bool fini;

/* les variables pour la synchro, ici */
pthread_t draw;
pthread_mutex_t mutex_stream_state;
pthread_mutex_t mutex_fenetre;
pthread_mutex_t mutex_texture;
pthread_cond_t cond_fenetre, cond_fenetre_texture, cond_cons, cond_depo;

int nb_text = 0;
bool texture_prete = false;


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
    while (windowsx == 0 && windowsy == 0) {
        pthread_cond_wait(&cond_fenetre, &mutex_fenetre);
    }
    pthread_mutex_unlock(&mutex_fenetre);
}

void signalerFenetreEtTexturePrete() {
    pthread_mutex_lock(&mutex_fenetre);
    texture_prete = true;
    pthread_cond_signal(&cond_fenetre_texture);
    pthread_mutex_unlock(&mutex_fenetre);
}

void attendreFenetreTexture() {
    pthread_mutex_lock(&mutex_fenetre);
    while (!texture_prete) {
        pthread_cond_wait(&cond_fenetre_texture, &mutex_fenetre);
    }
    pthread_mutex_unlock(&mutex_fenetre);
}

void debutConsommerTexture() {
    pthread_mutex_lock(&mutex_texture);
    while (nb_text == 0) {
        pthread_cond_wait(&cond_cons, &mutex_texture);
    }
    pthread_mutex_unlock(&mutex_texture);
}

void finConsommerTexture() {
    pthread_mutex_lock(&mutex_texture);
    nb_text--;
    pthread_cond_signal(&cond_depo);
    pthread_mutex_unlock(&mutex_texture);
}


void debutDeposerTexture() {
    pthread_mutex_lock(&mutex_texture);
    while (nb_text == NBTEX) {
        pthread_cond_wait(&cond_depo, &mutex_texture);
    }
    pthread_mutex_unlock(&mutex_texture);
}

void finDeposerTexture() {
    pthread_mutex_lock(&mutex_texture);
    nb_text++;

    pthread_cond_signal(&cond_cons);
    pthread_mutex_unlock(&mutex_texture);
}
