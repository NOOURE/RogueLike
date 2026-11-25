// portes.cpp
// ROLE : implémente le système d'ouverture des portes avec clés
#include "enregistrement.hpp"
#include "couleurs.hpp"
#include <vector>
#include <string>
#include <unistd.h> // pour usleep
using namespace std;


//-----------------------------------------------------------------------------
//Role : Faire une pause pendant l'ouverture de porte avec rafraîchissement 
//----------------------------------------------------------------------------
void sleep_porte(){
    refresh();  
    usleep(600000); // Pause 0.6 sec
}


//--------------------------------------------------------------------------------------
//Role : Ouvrir une porte si le joueur possede la cle correspondante
//------------------------------------------------------------------------------------
bool ouvrir_porte(Carte &carte, Joueur &joueur, Position pos, char cellule, vector<string> &msg_eq) {
    char cle_requise = 'a' + (cellule - '1');
    int c_droite = 100;
    int ligne = 9;
    
    for (int i = 0; i < joueur.nb_equipements; i++) {
        if (joueur.inventaire[i] == cle_requise) {
            changer_couleur(COULEURS_PAR_DEFAUT);
            ecrire_string("Porte " + string(1, cellule) + " ouverte!", c_droite, ligne);
            sleep_porte();
            
            // Supprimer clé
            for (int j = i; j < joueur.nb_equipements - 1; j++) {
                joueur.inventaire[j] = joueur.inventaire[j + 1];
            }
            joueur.nb_equipements--;
            return true; // Porte ouverte
        }
    }
    
    changer_couleur(COULEURS_PAR_DEFAUT);
    ecrire_string("Porte " + string(1, cellule) + " verrouillee", c_droite, ligne + 1);
    sleep_porte();
    ecrire_string("Cle " + string(1, cle_requise) + " requise", c_droite, ligne + 2);
    sleep_porte();
    return false; // Porte fermée
}