#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Score {
    private :
    int score;
    sf::Text score_texte;
    sf::Font police;

    public:
    Score();
    void ajout(int points);
    void afficher(sf::RenderWindow& fenetre);

};


#endif