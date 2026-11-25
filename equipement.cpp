// equipement.cpp
// ROLE : implémente le système de ramassage d'équipements
#include "enregistrement.hpp"
#include "couleurs.hpp"
#include <vector>
#include <string>
using namespace std;


//---------------------------------------------------------------------------------------
//Role : Ramasser un équipement et appliquer ses bonus au joueur
//---------------------------------------------------------------------------------------
void ramasser_equipement(Carte &carte, Joueur &joueur, Position pos, char cellule, vector<string> &msg_eq) {
    
    for (int i = 0; i < carte.nb_equipements; i++) {
        Equipement &eq = carte.equipements[i];
        if (eq.pos.x == pos.x && eq.pos.y == pos.y) {
            // Appliquer bonus
            joueur.caracter.vie += eq.bonus.vie;
            joueur.caracter.force += eq.bonus.force;
            joueur.caracter.defense += eq.bonus.defense;
            joueur.attaque += eq.bonus_attaque;
            
            string nom_affiche = eq.nom;
            if (eq.bonus.vie > 0) nom_affiche += " = " + to_string(eq.bonus.vie) + "V";
            if (eq.bonus.force > 0) nom_affiche += " = " + to_string(eq.bonus.force) + "F";
            if (eq.bonus.defense > 0) nom_affiche += " = " + to_string(eq.bonus.defense) + "D";
            if (eq.bonus_attaque > 0) nom_affiche += " = " + to_string(eq.bonus_attaque) + "A";
            
            msg_eq.push_back(nom_affiche);
            joueur.inventaire[joueur.nb_equipements] = cellule;
            joueur.nb_equipements++;
            
            // Retirer de la carte
            for (int j = i; j < carte.nb_equipements - 1; j++) {
                carte.equipements[j] = carte.equipements[j + 1];
            }
            carte.nb_equipements--;
            break;
        }
    }
}