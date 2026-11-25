// lib_projet_ncurses.cpp
// FICHIER : Implémentation des fonctions de la bibliothèque ncurses
// NE PAS MODIFIER LE .hpp - toutes les implémentations sont ici

#include "lib_projet_ncurses.hpp"  // Inclure les déclarations
#include <chrono>
#include <thread>

// ----- FONCTIONS - IMPLEMENTATION ----- 
bool initialiser_console(const PaireCouleur colorlist[], int nb_couleurs ) {
    // Starts ncurse
    WINDOW* win = nullptr;
    win = initscr();
    keypad(stdscr, TRUE);
    // Prevent from immediately drawing on screen
    noecho();

    // Invisible cursor
    curs_set(0);

    if (has_colors()) {
        start_color();
        PaireCouleur coul ;
        
        for (short i = 0 ; i < nb_couleurs ; i++) {
            coul = colorlist[i];
                init_pair(i+1, coul.texte, coul.fond); 
        }
        

    }

    else {
        addstr("WARNING! Your console does not support colours.");
        getch();
        // TODO: print message
    }

    return (win != nullptr);
}

void effacer_console() {
    erase();
}

void fermer_console() {
    endwin();
}

// ----- saisies et pause -----

// lire une valeur au clavier (bloquant) 
int saisie_bloquante(){
    timeout(-1);
    return getch();
}

// lire une valeur au clavier (non-bloquant) 
int saisie_non_bloquante(){
    timeout(0);
    return getch();
}

void attendre_millisecondes(int ms){
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));

} 

// ----- curseur et écriture -----


void ecrire_char(int x, int y, char chr) {
    mvaddch(y, x, chr);
}

void bouger_curseur(int x, int y) {
    move(y, x);
}

void changer_couleur (int indice_paire){
    attron(COLOR_PAIR(indice_paire));
}

void couleur_defaut() {
    attron(COLOR_PAIR(1));
}


void ecrire_string(const std::string& message, int x, int y) {
    bouger_curseur(x, y);
    printw("%s", message.c_str());
}



