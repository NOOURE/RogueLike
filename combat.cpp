// combat.cpp
// ROLE : implémente le systeme de combat entre le joueur et les monstres
#include "enregistrement.hpp"
#include "couleurs.hpp"
#include <vector>
#include <string>
#include <unistd.h> // pour usleep
using namespace std;

//---------------------------------------------------------------------------
//Role : Faire une pause pendant le combat avec rafraîchissement de l'écran
//----------------------------------------------------------------------------
void sleep_combat(){
    refresh();  
    usleep(800000); // Pause 0.8 sec
}


//------------------------------------------------------------------------------
//Role : Gérer un combat entre le joueur et un monstre
//-----------------------------------------------------------------------------
bool combattre_monstre(Carte &carte, Joueur &joueur, int monstre_index, Position new_pos, char cellule, vector<string> &msg_eq, int &resultat, Position depart_init) {
    
    Monstres &m = carte.monstres[monstre_index];
    int c_droite = 105;
    int ligne = 17;
    
    // Afficher infos combat
    changer_couleur(COULEURS_PAR_DEFAUT);
    ecrire_string("Combat vs " + string(1, cellule), c_droite, ligne); sleep_combat();
    ecrire_string("Force joueur: " + to_string(joueur.caracter.force + joueur.attaque), c_droite, ligne + 1); sleep_combat();
    ecrire_string("Force monstre: " + to_string(m.caracter.force), c_droite, ligne + 2); sleep_combat();
    
    int force_joueur = joueur.caracter.force + joueur.attaque;
    int force_monstre = m.caracter.force;
    
    if (force_joueur > force_monstre) {
        // Joueur gagne
        changer_couleur(VERT_SUR_NOIR);
        msg_eq.push_back("Monstre " + string(1, cellule) + " mort!");
        msg_eq.push_back("+1 force");
        joueur.caracter.force += 1;
        
        // Supprimer monstre
        for (int j = monstre_index; j < carte.nb_monstres - 1; j++) {
            carte.monstres[j] = carte.monstres[j + 1];
        }
        carte.nb_monstres--;
        carte.tab[new_pos.y][new_pos.x] = '.';
        resultat = 3;
        return true; // Monstre tué
    }
    else {
        // Monstre gagne
        changer_couleur(ROUGE_SUR_NOIR);
        ecrire_string("VOUS ETES MORT!", c_droite, ligne + 3);
        msg_eq.push_back("Monstre trop fort !");
        msg_eq.push_back("Vous etes mort !");
        joueur.caracter.vie = 0;
        carte.tab[joueur.pos.y][joueur.pos.x] ='.';

        // Réapparition
        if (depart_init.x < carte.nb_colonnes && depart_init.y < carte.nb_lignes &&
            carte.tab[depart_init.y][depart_init.x] == '.') {
            carte.tab[depart_init.y][depart_init.x] = joueur.symbole;
            joueur.pos = depart_init;
            joueur.caracter.vie = 50;
        } else {
            carte.tab[0][0] = joueur.symbole;
            joueur.pos.x = 0;
            joueur.pos.y = 0;
            joueur.caracter.vie = 50;
        }
        sleep_combat();
        resultat = 1;
        return false; // Joueur mort
    }
}


//-----------------------------------------------------------------------------------------------
//Role : Afficher un message de danger quand un monstre plus fort est à proximité 3 case du joueur
//----------------------------------------------------------------------------------------------
void afficher_danger(const Carte &carte, const Joueur &joueur) {
    int col = 105;
    int ligne = 15;
    
    for (int i = 0; i < carte.nb_monstres; i++) {
        const Monstres &m = carte.monstres[i]; 
        int dx = m.pos.x - joueur.pos.x;
        int dy = m.pos.y - joueur.pos.y;
        
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        int distance = dx + dy;
        
        if (distance <= 3) {
            int force_monstre = m.caracter.force;
            int force_joueur = joueur.caracter.force + joueur.attaque;

            if (force_monstre > force_joueur) {
                changer_couleur(ROUGE_SUR_NOIR);
                char symbole_monstre = carte.tab[m.pos.y][m.pos.x];
                ecrire_string("DANGER: " + string(1, symbole_monstre) +  " plus fort!", col, ligne);
                ligne++;
            }
        }
    }
    
    couleur_defaut();
}
