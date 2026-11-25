// FICHIER ; carte.cpp 
// ROLE : implémenter les fonctions de gestion de la carte
#include <algorithm>
#include <iostream>   
#include <fstream> // Pour la gestion des fichiers (ifstream, ofstream)
#include <string>   
#include "couleurs.hpp"
#include "enregistrement.hpp"
using namespace std;

//---------------------------------------------------------------------------------------
//Role : Charger la carte depuis un fichier texte et initialiser les monstres et équipements
//---------------------------------------------------------------------------------------
Carte charger_carte (const string &nom_fic){
    fstream flux;
    string ligne;// Chaîne temporaire pour stocker  ligne lue
    Carte carte{};

    carte.nb_lignes = 0;// Init le compteur de lignes à 0 
    carte.nb_monstres = 0; // init le nombre de monstres à 0 dès le début
    
    //initialiser tout le tableau avec des espaces pour évite valeurs aléatoires
    for (int i = 0; i < max_l; i++) {
        for (int j = 0; j < max_c; j++) {
            carte.tab[i][j] = ' ';
        }
    }
    
    flux.open(nom_fic, ios::in);
    if(!flux.is_open()){
        // Utilise ncurses pour afficher l'erreur
        ecrire_string("ERREUR: Fichier " + nom_fic + " introuvable!", 0, 0);
        ecrire_string("Appuyez sur une touche pour quitter", 0, 1);
        saisie_bloquante();
        return carte; // Retourne carte vide
    }
    //continue tant qu'il y a des lignes et qu'on n'a pas dépassé MAX_L
    while (carte.nb_lignes < max_l && getline(flux, ligne)){
        if (!ligne.empty() && ligne.back() == '\r') ligne.pop_back();
        // taille de ligne actuelle comme nombnbre de colonnes
        carte.nb_colonnes = std::max(carte.nb_colonnes, std::min(ligne.size(), static_cast<size_t>(max_c)));
        // Copie caractère de ligne dans le tableau
        for (size_t i = 0; i < ligne.size(); i++){
            if(i < max_c){
                carte.tab[carte.nb_lignes][i] = ligne[i];
            }
            
        }
        //vérifier si ligne.size() < max_c avant de remplir les espace vide
        if (ligne.size() < max_c) {
            for (size_t i = ligne.size(); i < max_c ; i++){
                carte.tab[carte.nb_lignes][i] = ' ';
            }
        }
        carte.nb_lignes++; // Passe de ligne suivante
    }
    flux.close();
    

    // ----------- INITIALISATION DES MONSTRES ------------------------------
    // Après le chargement de la carte, on parcourt pour trouver les monstres (A-Z)
    // et on remplit le tableau carte.monstres[] ainsi leurs statistiques
    
    for (int ligne = 0; ligne < carte.nb_lignes; ligne++) {
        for (int colonne = 0; colonne < carte.nb_colonnes; colonne++) {
            char cellule = carte.tab[ligne][colonne];
            
            // Monstre (A-Z)
            if (cellule >= 'A' && cellule <= 'Z') {
                Monstres m{}; 
                m.pos.x = colonne;
                m.pos.y = ligne;
                
                // Statistiques basées sur la lettre (A = faible, Z = fort)
                m.caracter.vie = 40 + (cellule - 'A') * 5;     // A=20, B=25, C=30...
                m.caracter.force = 5 + (cellule - 'A') * 2;    // A=5, B=7, C=9...
                m.caracter.vision = 3 + (cellule - 'A') / 5;   // A=3, F=4, K=5...
                
                // Propriétés d'IA 
                m.actif = true;
                m.typeAI = "aleatoire";
                m.zone_distance = 3;
                
                //Tableau vérif de limite 
                if (carte.nb_monstres < 50) {
                    carte.monstres[carte.nb_monstres] = m;
                    carte.nb_monstres++;
                }
            }
        }
    }// fin monstres



      // ----------- INITIALISATION DES EQUIPEMENTS----------------------
    carte.nb_equipements = 0; 
    for (int y = 0; y < carte.nb_lignes; y++) {
        for (int x = 0; x < carte.nb_colonnes; x++) {
            char c = carte.tab[y][x];
            
            if (c >= 'a' && c <= 'z') {
                Equipement eq{};
                eq.pos.x = x;
                eq.pos.y = y;
                
                // Définir type selon lettre
                if (c == 'a' || c == 'b' || c == 'c') {
                    eq.nom = "Potion de vie";
                    eq.typeObjet = "potion";
                    eq.bonus.vie = 20;
                    eq.bonus.force = 0;
                    eq.bonus.defense = 0;
                    eq.bonus_attaque = 0;
                }
                else if (c == 'd' || c == 'e' || c == 'f') {
                    eq.nom = "Epée";
                    eq.typeObjet = "arme";
                    eq.bonus.vie = 0;
                    eq.bonus.force = 5;
                    eq.bonus.defense = 0;
                    eq.bonus_attaque = 10;
                }
                else if (c == 'g' || c == 'h' || c == 'i') {
                    eq.nom = "Armure";
                    eq.typeObjet = "armure";
                    eq.bonus.vie = 0;
                    eq.bonus.force = 0;
                    eq.bonus.defense = 5;
                    eq.bonus_attaque = 0;
                }
                else if (c == 'j' || c == 'k' || c == 'l') {
                    eq.nom = "Cle rouge";
                    eq.typeObjet = "cle";
                    eq.bonus.vie = 0;
                    eq.bonus.force = 0;
                    eq.bonus.defense = 0;
                    eq.bonus_attaque = 0;
                }
                
                if (carte.nb_equipements < 50) {
                    carte.equipements[carte.nb_equipements] = eq;
                    carte.nb_equipements++;
                }
            }
        }
    }  
    return carte;
}


//------------------------------------------------------------------------------------
//Role : Afficher la carte avec les couleurs appropriées pour chaque type de cellule
//------------------------------------------------------------------------------------
void afficher_carte(const Carte &carte) {
    // Limiter à 80 colonnes pour laisser place aux messages
    int max_colonnes = 80;  
    
    for (size_t i = 0; i < carte.nb_lignes && i < 24; i++) {
        for (size_t j = 0; j < carte.nb_colonnes && j < max_colonnes; j++) {
            char cellule = carte.tab[i][j];
            if (cellule == '#') { changer_couleur(BLEU_SUR_NOIR); }
            else if (cellule == '@') { changer_couleur(COULEURS_PAR_DEFAUT); }
            else if (cellule >= 'A' && cellule <= 'Z') { changer_couleur(ROUGE_SUR_NOIR); }
            else if (cellule >= 'a' && cellule <= 'z') {changer_couleur(VERT_SUR_NOIR); }
            else if (cellule >= '1' && cellule <= '9') { changer_couleur(JAUNE_SUR_NOIR); }
            else { changer_couleur(COULEURS_PAR_DEFAUT); }
            ecrire_char(j, i, cellule);  
        }
    }
    couleur_defaut();
}
