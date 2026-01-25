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
    std::optional<sf::Text> texte_instruction;
    std::optional<sf::Text> texte_gameover;
    std::optional<sf::Text> texte_niveau;
    int Index;
    int index_souris;

    std::unique_ptr<sf::Texture> fond_ecran_texture;
    std::unique_ptr<sf::Sprite> fond_ecran_sprite;
   

    public :

    Menu(float largeur, float hauteur);
    void mouvement_souris(const sf::Vector2f& sourisPos, bool clicked);
    int clic_souris(const sf::Vector2f& sourisPos );
    void afficher_menu(sf::RenderWindow& fenetre);
    bool loadBackground(const std::string& filename, float largeur, float hauteur);
    void afficher_selection(sf::RenderWindow& fenetre, int niveau_choisi);
    void afficher_fin(sf::RenderWindow& fenetre);

};

#endif