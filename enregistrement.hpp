// Fichier : enregistrement.hpp
// ROLE : Déclare toutes les structures utilisées dans le jeu

#ifndef ENREGISTREMENT_HPP  // Début de la protection contre les inclusions multiples
#define ENREGISTREMENT_HPP
#include <string>  

using namespace std;

const int max_l = 30;  // Taille maximale des lignes de la carte
const int max_c = 100;

//---------------------------------------
//Role: enregistrement golobl qui definit la position de chaque stucture du jeu
// pré : x et y >= 0
struct Position{
    int x;
    int y;
};


//---------------------------------------------
//Role: enregistrement qui definit le position de chaque porte
struct Porte {
    Position pos;
    int cle_requise;
    bool ouverte;  
};


//---------------------------------------------
//Role: enregistrement qui definit les caractéristique du Joueur
//pré : vie, force, defanse, bonus, vision >= 0
struct Cara_joueur {
    int vie;      
    int force;    
    int defense;
    int bonus;
    int vision;
};

//---------------------------------------------
//Role: enregistrement qui definit les caractéristique du monstres
//pré : vie, force, vision >= 0
struct Cara_monstres {
    int vie;      
    int force; 
    int vision;
};

//---------------------------------------------
//Role: enregistrement qui definit le joueur et les elements principal du jeu
struct Joueur {
    Position pos;
    Position depart;
    char symbole;
    Cara_joueur caracter;  // Statistiques
    int attaque;
    char inventaire[10];   // Équipements ramassés (lettres a-z)
    int nb_equipements;    // Nb d'équipements actuels 
};

//---------------------------------------------
//Role: enregistrement qui definit le type de monstre 
struct Monstres {
    Position pos;
    Cara_monstres caracter;
    bool actif;
    string typeAI;       //"aleatoire, poursuite"
    int zone_distance;  //pré : zonde distance >=0
};

//---------------------------------------------
//Role: enregistrement qui definit les différents équipements
struct Equipement {
    Position pos;
    string nom;
    string typeObjet;   //" Arme , Armure, potion, clé "
    Cara_joueur bonus;
    int bonus_attaque;  //pré : bonus_attaque >= 0 
    
    
};

//----------------------------------------------------------------------
/*Role : cet enregistrement definit les dimensiions de la carte qui est la base de la jeu
        laquelle sera placé differents elements tel que le Joeur, Monstres, Porte ..*/
//Pré : CONST max_l, max_c
struct Carte{
    size_t nb_lignes;
    size_t nb_colonnes;
    char tab[max_l][max_c];
//--------------
    Monstres monstres[50]; // Tableau de monstres
    int nb_monstres;       // Nb de monstres
    Equipement equipements[50];
    int nb_equipements;
    Porte portes[20];
    int nb_portes;
};



#endif // ENREGISTREMENT_HPP      // Fin de la protection