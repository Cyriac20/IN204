#include "menu.hpp"
#include <iostream>

Menu::Menu(float largeur, float hauteur) : Index(0) {
    if (!police.openFromFile("../src/res/poppins1.ttf")) {
        std::cerr << "Erreur : police non trouvée" << std::endl;
    }

    std::vector<std::string> items = {"Jouer", "Options", "Scores", "Quitter"};

    for (size_t i = 0; i < items.size(); i++){
        sf::Text texte(police, items[i], 50);
        texte.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        
        sf::FloatRect textBounds = texte.getLocalBounds();
        texte.setOrigin(sf::Vector2f(textBounds.size.x / 2.f, textBounds.size.y / 2.f));
        texte.setPosition(sf::Vector2f(largeur / 2.f, hauteur / 2.f + i * 80.f - 120.f));

        options.push_back(texte);
    }

}

bool Menu::loadBackground(const std::string& filename, float windowWidth, float windowHeight) {

    fond_ecran_texture = std::make_unique<sf::Texture>();
    if (fond_ecran_texture->loadFromFile(filename)){
        fond_ecran_sprite = std::make_unique<sf::Sprite> (*fond_ecran_texture);

        float scaleX = windowWidth / fond_ecran_texture->getSize().x;
        float scaleY = windowHeight / fond_ecran_texture->getSize().y;
        fond_ecran_sprite->setScale(sf::Vector2f(scaleX, scaleY));

        return true;
    }
    return false;

}

void Menu::dessiner(sf::RenderWindow& window) {
    window.draw(*fond_ecran_sprite);

    for (const auto& option : options) {
        window.draw(option);
    }
}