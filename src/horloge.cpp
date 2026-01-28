#include "horloge.hpp"

// Fonction d'affichage du temps lors d'une partie
void Horloge::dessiner_horloge(sf::RenderWindow& fenetre, int largeur , int hauteur){
    
    sf::Text texte(police);     
    std::string temps = std::to_string( int(getElapsedTime().asSeconds()) );
    texte.setString ("TEMPS : " + temps + "s");
    texte.setCharacterSize(20);
    texte.setFillColor(sf::Color::White);

    texte.setPosition(sf::Vector2f(largeur - 450.f, hauteur - 180.f));
    fenetre.draw(texte);
    

}



