// LIBRAIRIE SIMPLIFIEE POUR UTILISER NCURSES - A UTILISER IMPERATIVEMENT - NE PAS MODIFIER
#pragma once
#include <string>


// Utilisés pour attendre un nombre voulu de millisecondes
#include <chrono>
#include <thread>

// ncurses est une librairie permettant une manipulation du terminal plus avancée que de simples cin et cout
#include <curses.h>



// ------------------------
// ----- CONSOLE SIZE -----
// ------------------------
const int CONSOLE_X_SIZE = 80;
const int CONSOLE_Y_SIZE = 24;
// -------------------

// ----- TYPES -----
// ncurses fonctionne en enregistrant une par une des paires de couleurs et en faisant référence à leur indice (commençant à 1) pour les utiliser 
struct PaireCouleur{
  short texte;  // couleur du texte
  short fond;   // couleur du fond
};


// ----- FONCTIONS ----- 

// Initialise la console de Curses avec un tableau de PaireCouleur et son nombre d'éléments
bool initialiser_console(const PaireCouleur colorlist[], int nb_couleurs );

// Efface la console
void effacer_console();

// Ferme la console de Curses
void fermer_console();


// ----- saisies et pause -----

// lire une valeur au clavier (bloquant) 
int saisie_bloquante();

// lire une valeur au clavier (non-bloquant) 
int saisie_non_bloquante();

// Pause durant ms millisecondes
void attendre_millisecondes(int ms);


// ----- curseur et écriture -----

// Bouge le curseur console à l'emplacement (x, y)
void bouger_curseur(int x, int y);

// Ecrit un caractère chr à l'emplacement (x, y)
void ecrire_char(int x, int y, char chr);

// Ecrit une chaine de caractère à partir de l'emplacement (x, y)
void ecrire_string(const std::string& message, int x, int y);

// Remet les couleurs par défaut pour les affichages (blanc sur noir)
void couleur_defaut();

// Choisi une couleur pour les affichages
void changer_couleur(int indice);


