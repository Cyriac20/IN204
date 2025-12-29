#include "horloge.hpp"


void Horloge::dessiner_horloge(sf::RenderWindow& fenetre, int largeur , int hauteur){
    
    sf::Text texte(police);     
    std::string temps = std::to_string( int(getElapsedTime().asSeconds()) );
    texte.setString ("Temps : " + temps + "s");
    texte.setCharacterSize(20);
    texte.setFillColor(sf::Color::White);

    texte.setPosition(sf::Vector2f(largeur - 100.f, hauteur -100.f));
    fenetre.draw(texte);
    

}



