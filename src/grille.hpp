#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <SFML/Graphics.hpp>
#include <array>


class grille {
private:
    std::array<std::array<int,10>, 22> matrice;
    static constexpr int TAILLE_CASE = 34;
    
public:
    grille();
    void afficher(sf::RenderWindow& window, int offsetX = 50, int offsetY = 50);
    int valeur(int i , int j);
    void set(int ligne, int colonne, int valeur);
    
    
    std::array<int,4> ligne_complete();
    void actualisation(std::array<int,4>);
    bool emplacement_disponible(std::array<std::array<int,2>,4> position);
    
};

#endif