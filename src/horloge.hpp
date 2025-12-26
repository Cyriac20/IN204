#ifndef HORLOGE_HPP
#define HORLOGE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Horloge : public sf::Clock{
    private:
    sf::Font police;
    sf::Clock horloge;
    public:
    Horloge() : sf::Clock() {if (!police.openFromFile("../src/res/poppins1.ttf")) { std::cerr << "Erreur : police non trouvée" << std::endl;};};
    void dessiner_horloge(sf::RenderWindow& fenetre, int largeur, int hauteur);
    
    
};

#endif
