#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "pieces.hpp"

class grille {
private:
    std::array<std::array<int,10>, 22> matrice;
    static constexpr int TAILLE_CASE = 30;
    
public:
    grille();
    void afficher(sf::RenderWindow& window, int offsetX = 50, int offsetY = 50);
    void set(int ligne, int colonne, int valeur);
    void apparition_piece(Piece& piece);
    void ligne_complete(int i);
    bool emplacement_disponible(std::array<std::array<int,2>,4> position);
    void effacer_piece(Piece& piece);
};

#endif