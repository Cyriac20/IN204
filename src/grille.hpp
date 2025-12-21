#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <SFML/Graphics.hpp>
#include <array>

class grille {
private:
    std::array<std::array<int,10>, 22> matrice;
    static constexpr int TAILLE_CASE = 30;
    
public:
    grille();
    void afficher(sf::RenderWindow& window, int offsetX = 50, int offsetY = 50);
    void set(int ligne, int colonne, int valeur);
    void ligne_complete(int i);
};

#endif