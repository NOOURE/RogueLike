// ROLE : Point d'entrée principal du jeu
//compiler en ajoutant -lncurses  à la commande de compilation
#include <iostream>
#include <string>
#include <vector>
#include "lib_projet_ncurses.hpp"
#include "lib_ncurses.cpp"
#include "couleurs.hpp"
#include"enregistrement.hpp"

#include "carte.cpp"
#include "joueur.cpp"
#include "monstres.cpp"
#include <ctime>   // pour srand(time(NULL))et reinit séquence
using namespace std;


// tableau des couleurs pour chacune des paires de couleurs , à fournir à l'initialisation
const PaireCouleur couleurs[] = {
 {COLOR_WHITE, COLOR_BLACK},   // COULEURS_PAR_DEFAUT = 1;
 {COLOR_RED, COLOR_BLACK},     // ROUGE_SUR_NOIR = 2;
 {COLOR_YELLOW, COLOR_BLACK},  // JAUNE_SUR_NOIR = 3;
 {COLOR_BLUE, COLOR_BLACK},    // BLEU_SUR_NOIR = 4; 
 {COLOR_GREEN, COLOR_BLACK},    // VERT_SUR_NOIR = 5;
 {COLOR_CYAN, COLOR_BLACK},     // CYAN_SUR_NOIR =6;
 {COLOR_MAGENTA, COLOR_BLACK},  // MAGENTA_SUR_NOIR =7;
 {COLOR_WHITE, COLOR_BLACK},    //  BLANC_SUR_NOIR =8;
 {COLOR_MAGENTA, COLOR_BLACK}   //  ROSE_SUR_NOIR = 9

}; 


// -------------------
//Role : Dessiner une ligne horizontale de caractères à une position donnée
void dessiner_ligne(int longueur, int y, char chr) {
    for (int x = 0; x < longueur; x++) {
        ecrire_char(x, y, chr);
    }
}


// -------------------
//----  Fonctionnalites  -----
//-----------------------------------------------------------
//Role : Afficher les instructions du jeu
//-----------------------------------------------------------
void afficher_instructions() {
    changer_couleur(BLEU_SUR_NOIR);
    ecrire_string(" JEU ROGUE-LIKE ", 0, 24);
    changer_couleur(VERT_SUR_NOIR);
    ecrire_string(" Fleches: Deplacer", 20, 24);
    changer_couleur(JAUNE_SUR_NOIR);
    ecrire_string(" Q : Quitter",40 , 24);  
    changer_couleur(COULEURS_PAR_DEFAUT);
    ecrire_string(" Attaquer les monstres : A = plus faible, Z = plus fort", 0, 26);
    ecrire_string(" Portes 1-9 : ouvrez avec cles a-i correspondantes", 0, 27);
}


//---------------------------------------------------------------------------------------
//Role : Afficher la légende des symboles utilisés dans le jeu
//---------------------------------------------------------------------------------------
void afficher_legende() {
    int colonne_droite = 81;
    int ligne = 7;  // Après les stats
    changer_couleur(COULEURS_PAR_DEFAUT);
    ecrire_string("@ : Joueur", colonne_droite, ligne);
    changer_couleur(BLEU_SUR_NOIR);
    ecrire_string("# : Mur", colonne_droite, ligne + 1);
    changer_couleur(ROUGE_SUR_NOIR);
    ecrire_string("A-Z : Monstres", colonne_droite, ligne + 2);
    changer_couleur(VERT_SUR_NOIR);
    ecrire_string("a-z : Objets", colonne_droite, ligne + 3);
    changer_couleur(JAUNE_SUR_NOIR);
    ecrire_string("1-9 : Portes", colonne_droite, ligne + 4);
    changer_couleur(BLANC_SUR_NOIR);
    ecrire_string("$ : Sortie", colonne_droite, ligne + 5);
    couleur_defaut();
}



// ----------------------------
// ------ALGO PRINCIPAL -------
// ----------------------------
//--------------------------------------------------------------------------------
//Role : Fonction principale du jeu - initialise, gère la boucle de jeu et termine
//---------------------------------------------------------------------------------
int main() {

    // Initialisation de la console de couleurs = 9
    if (!initialiser_console(couleurs, 9)) { 
            cout << "ERREUR: impossible d'initialiser la console" << endl;
            return 1;
    }
    // Initialisation de l'aléatoire 
    srand(time(NULL));

    // Chargement de la carte
    string nom_fichier = "level.txt";
    Carte carte = charger_carte(nom_fichier);
    
    // Vérification que la carte est chargée
    if (carte.nb_lignes == 0) {
        ecrire_string("ERREUR: Carte vide!", 0, 20);
        saisie_bloquante();
        fermer_console();
        return 1;
    }

    // Création et initialisation du joueur
    Joueur joueur = initialiser_joueur();
    Position depart_init;
    // Trouver la position initiale du '@' dans la carte
    for (int y = 0; y < carte.nb_lignes; y++) {
        for (int x = 0; x < carte.nb_colonnes; x++) {
            if (carte.tab[y][x] == '@') {
                joueur.pos.x = x;
                joueur.pos.y = y;
                depart_init.x = x;  //Sauvegarder pos depart
                depart_init.y = y; 
            }
        }
    }

    int input = ' '; 
    vector<string> msg_eq; //msg equipement

    // Boucle principale du jeu
    while (input != 'q' && input != 'Q') {
        effacer_console();
        afficher_carte(carte); 
        afficher_stats_joueur(joueur);  // Va écrire sur ligne defini
        afficher_legende();
        afficher_instructions(); 
            
         // Afficher les msg des equipements et garder seulement les 4 derniers msg 
        // 
        if (msg_eq.size() > 4) {
            // Supprime depuis le début jusqu'à taile - 4
            msg_eq.erase(msg_eq.begin(), msg_eq.begin() + (msg_eq.size() - 4));
        } 

        int msg_ligne = 14;
        int msg_colonne = 81;
        changer_couleur(VERT_SUR_NOIR);
        for (size_t i = 0; i < msg_eq.size(); i++) {
            ecrire_string(msg_eq[i], msg_colonne, msg_ligne + i);
        }
        couleur_defaut();
        afficher_danger(carte, joueur) ;
        // Saisie utilisateur
        input = saisie_bloquante();
                
        if (input == KEY_UP || input == KEY_DOWN || 
            input == KEY_LEFT || input == KEY_RIGHT) {
            int resultat;
            deplacer_joueur(carte, joueur, input, depart_init, msg_eq, resultat);
            
            // Gérer la victoire
            int vec_ligne = 10;
            int vec_colonne = 50;
            if (resultat == 2) {  // Victoire codee
                effacer_console();
                changer_couleur(JAUNE_SUR_NOIR);
                ecrire_string("    VICTOIRE ", vec_colonne , vec_ligne);
                ecrire_string("Vous avez atteint la sortie $ !", vec_colonne, vec_ligne +1);
                ecrire_string("r : pour rejouer", vec_colonne, vec_ligne +3);
                ecrire_string("q : pour quitter", vec_colonne, vec_ligne +4);
                couleur_defaut();
                refresh();
                
                // Attendre la décision de gammer
                int choix = saisie_bloquante();
                if (choix == 'r' || choix == 'R') {
                    // Relancer au jeu
                    carte = charger_carte("level.txt");
                    joueur = initialiser_joueur();
                    msg_eq.clear();
                    
                    // Retrouver position départ
                    for (int y = 0; y < carte.nb_lignes; y++) {
                        for (int x = 0; x < carte.nb_colonnes; x++) {
                            if (carte.tab[y][x] == '@') {
                                joueur.pos.x = x;
                                joueur.pos.y = y;
                                depart_init.x = x;
                                depart_init.y = y;
                            }
                        }
                    }
                    continue; // Retour au début de la boucle
                } else {
                    input = 'q'; // Quitter
                    continue; // Passe au tour suivant où while s'arrêtera
                }
            }
            // Si pas victoire ET pas mort les monstres bougent aussi
            if (resultat == 0) {
                deplacer_monstres(carte);
            }
        }
    }
    // Fermeture de la console
    fermer_console();
    cout << "Bien joue !" << endl;
    return 0;
}
