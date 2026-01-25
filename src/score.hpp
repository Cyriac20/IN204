#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <optional>

class Score {
    private :
    int score;
    std::optional<sf::Text> score_texte;
    std::optional<sf::Text> niveau_texte;
    sf::Font police;
    

    public:
    Score();
    void actualisation();
    int combo(std::array<int,4> lignes);
    void calcul(int nb_lignes);
    void ajout(int points);
    void afficher(sf::RenderWindow& fenetre);
    void reset();
    int niveau;
    int nb_ligne_casse; // pour savoir quand on passe au niveau suivant

};


#endif