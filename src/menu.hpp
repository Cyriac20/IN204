#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

class Menu {
    private: 
    sf::Font police;
    std::vector<sf::Text> options;
    int Index;

    std::unique_ptr<sf::Texture> fond_ecran_texture;
    std::unique_ptr<sf::Sprite> fond_ecran_sprite;
   

    public :

    Menu(float largeur, float hauteur);
    void dessiner(sf::RenderWindow& window);
    bool loadBackground(const std::string& filename, float windowWidth, float windowHeight);

};

#endif