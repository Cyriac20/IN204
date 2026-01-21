#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Score {
    private :
    int score;
    std::optional<sf::Text> score_texte;
    std::optional<sf::Text> niveau_texte;
    sf::Font police;
    void actualisation();

    public:
    Score();
    void calcul(std::array<int,4> lignes);
    void ajout(int points);
    void afficher(sf::RenderWindow& fenetre);
    int niveau;

};


#endif