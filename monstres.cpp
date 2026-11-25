// FICHIER: monstres.cpp
// ROLE : Implémente l'IA de déplacement des monstres
#include "enregistrement.hpp"
#include "lib_projet_ncurses.hpp"
#include <cstdlib> // pour rand()



//---------------------------------------------------------------------
//Role : IA simple pour déplacement aléatoire des monstres (A-Z)
//------------------------------------------------------------------
void deplacer_monstres(Carte &carte) {
    // Parcourir le tab des monstres pour synchroniser carte.monstres[] et carte.tab[][]
    for (int i = 0; i < carte.nb_monstres; i++) {
        Monstres &m = carte.monstres[i];
        
        // Vérifier si c'est un monstre actif ET 1 chance sur 3 de bouger
        if (m.actif && rand() % 3 == 0) {
            
            // Essayer jusqu'à 4 directions différentes aléatoires
            for (int essai = 0; essai < 4; essai++) {
                int dir = rand() % 4; // 0=haut, 1=bas, 2=gauche, 3=droite
                int new_colonne = m.pos.x;
                int new_ligne = m.pos.y;
                
                // Calculer la nouvelle position selon la direction
                if (dir == 0) new_ligne--;      // haut
                else if (dir == 1) new_ligne++; // bas
                else if (dir == 2) new_colonne--; // gauche
                else if (dir == 3) new_colonne++; // droite
                
                // Vérif 1 : La case dans les limites de la carte 
                if (new_colonne >= 0 && new_colonne < carte.nb_colonnes &&
                    new_ligne >= 0 && new_ligne < carte.nb_lignes) {
                    
                    // utiliser carte.tab pour vérifier le contenu
                    char case_cible = carte.tab[new_ligne][new_colonne];
                    
                    // vérif 2 : La seule case cible autorisé '.', pas de :@,#,$,A-Z,a-z,1-9 
                    if (case_cible == '.') {
                        // synchroniser les deux représentations
                        // Récupérer le symbole du monstre à sa position actuelle
                        char symbole_monstre = carte.tab[m.pos.y][m.pos.x];
                        
                        // Déplacer dans carte.tab
                        carte.tab[new_ligne][new_colonne] = symbole_monstre;
                        carte.tab[m.pos.y][m.pos.x] = '.';
                        
                        // Mettre à jour la position dans le tableau monstres
                        m.pos.x = new_colonne;
                        m.pos.y = new_ligne;
                        
                        break; // Arrêter les essais après un déplacement réussi
                    }
                }
            }
        }
    }
}