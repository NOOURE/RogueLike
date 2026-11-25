#include <string>
#include <vector>
#include "enregistrement.hpp"
#include "couleurs.hpp" 
#include "combat.cpp"
#include "equipement.cpp"
#include "portes.cpp"
using namespace std;

//----------------------------------------------------------------------------
//Role : Initialiser les caractéristique du joueur avec des valeurs par défaut
//-----------------------------------------------------------------------------
Joueur initialiser_joueur() {
    Joueur j{};
    j.pos.x = 0; // Init pos pour maj tard
    j.pos.y = 0;
    
    // Init les caractrestiques dans la sous-structure
    j.caracter.vie = 50;      
    j.caracter.force = 5;    
    j.caracter.defense = 5;   
    j.caracter.vision = 5;
    j.caracter.bonus = 0;
    
    // Init le reste
    j.symbole = '@';
    j.attaque = 5;
    j.nb_equipements = 0;
    
    // Init l'inventaire vide
    for (int i = 0; i < 10; i++) {
        j.inventaire[i] = ' ';
    }
    return j;
}



//---------------------------------------------------------------------------------------
//Role : Afficher les statistiques du joueur (vie, force, défense, attaque, inventaire)
//---------------------------------------------------------------------------------------
void afficher_stats_joueur(const Joueur &joueur) {
    int c_droite = 81;
    int ligne = 1;
    changer_couleur(VERT_SUR_NOIR);
    ecrire_string("Vie: " + to_string(joueur.caracter.vie), c_droite, ligne);
    ecrire_string("Force: " + to_string(joueur.caracter.force), c_droite, ligne + 1);
    ecrire_string("Defense: " + to_string(joueur.caracter.defense), c_droite, ligne + 2);
    ecrire_string("Ataque: " + to_string(joueur.attaque), c_droite, ligne + 3);
    string inv = "Objets: ";
    for (int i = 0; i < joueur.nb_equipements; i++) {
        inv += joueur.inventaire[i];  // inventaire est direct dans Joueur
        inv += " ";
    }
    changer_couleur(VERT_SUR_NOIR);
    ecrire_string(inv, c_droite, ligne + 4);
    couleur_defaut();
}


//---------------------------------------------------------------------------------------
//Role : Déplacer le joueur sur la carte en fonction de la direction et gérer les interactions
//---------------------------------------------------------------------------------------
void deplacer_joueur(Carte &carte, Joueur &joueur, int direction, Position depart_init, vector<string> &msg_eq, int &resultat) {
    
    resultat = 0;
    if (joueur.caracter.vie <= 0) return;
    Position new_pos = joueur.pos;
    
    // Calcul nouvelle position
    if (direction == KEY_UP) new_pos.y--;
    else if (direction == KEY_DOWN) new_pos.y++;
    else if (direction == KEY_LEFT) new_pos.x--;
    else if (direction == KEY_RIGHT) new_pos.x++;
    else return;
    
    // Vérifications
    if (new_pos.x < 0 || new_pos.x >= carte.nb_colonnes || 
        new_pos.y < 0 || new_pos.y >= carte.nb_lignes) return;
    
    char cellule = carte.tab[new_pos.y][new_pos.x];
    if (cellule == '#') return;
    
    //Délégation aux sous_fonction
    if (cellule >= 'A' && cellule <= 'Z') {
        // Trouver monstre
        for (int i = 0; i < carte.nb_monstres; i++) {
            if (carte.monstres[i].pos.x == new_pos.x && 
                carte.monstres[i].pos.y == new_pos.y) {
                bool monstre_tue = combattre_monstre(carte, joueur, i, new_pos, cellule, msg_eq, resultat, depart_init);
                if (monstre_tue) {
                    // Déplacer joueur sur la case du monstre tué
                    carte.tab[joueur.pos.y][joueur.pos.x] = '.';
                    carte.tab[new_pos.y][new_pos.x] = joueur.symbole;
                    joueur.pos = new_pos;
                }
                return;
            }
        }
    }
    else if (cellule >= 'a' && cellule <= 'z') {
        if (joueur.nb_equipements >= 10) {
            msg_eq.push_back("Inventaire plein");
            return;
        }
        ramasser_equipement(carte, joueur, new_pos, cellule, msg_eq);
        carte.tab[joueur.pos.y][joueur.pos.x] = '.';
        carte.tab[new_pos.y][new_pos.x] = joueur.symbole;
        joueur.pos = new_pos;
    }
    else if (cellule >= '1' && cellule <= '9') {
        if (ouvrir_porte(carte, joueur, new_pos, cellule, msg_eq)) {
            carte.tab[joueur.pos.y][joueur.pos.x] = '.';
            carte.tab[new_pos.y][new_pos.x] = joueur.symbole;
            joueur.pos = new_pos;
        }
    }
    else if (cellule == '$') {
        resultat = 2;
        carte.tab[joueur.pos.y][joueur.pos.x] = '.';
        carte.tab[new_pos.y][new_pos.x] = joueur.symbole;
        joueur.pos = new_pos;
    }
    else { // Case vide
        carte.tab[joueur.pos.y][joueur.pos.x] = '.';
        carte.tab[new_pos.y][new_pos.x] = joueur.symbole;
        joueur.pos = new_pos;
    }
}