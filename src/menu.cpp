#include "menu.hpp"
#include <iostream>

Menu::Menu(float largeur, float hauteur) : Index(0) {
    if (!police.openFromFile("../src/res/poppins1.ttf")) {
        std::cerr << "Erreur : police non trouvée" << std::endl;
    }

    std::vector<std::string> items = {"Jouer", "Options", "Scores", "Quitter"};

    for (size_t i = 0; i < items.size(); i++){
        sf::Text texte(police, items[i], 50);
        texte.setFillColor(sf::Color::White);
        
        sf::FloatRect textBounds = texte.getLocalBounds();
        texte.setOrigin(sf::Vector2f(textBounds.size.x / 2.f, textBounds.size.y / 2.f));
        texte.setPosition(sf::Vector2f(largeur / 2.f, hauteur / 2.f + i * 80.f - 120.f));

        options.push_back(texte);
    }

    texte_gameover.emplace(police);
    texte_gameover->setString("Game Over");
    texte_gameover->setCharacterSize(80);
    texte_gameover->setFillColor(sf::Color::Red);

    texte_instruction.emplace(police);
    texte_instruction->setString("<-  ->  choisir | Entree  valider");
    texte_instruction->setCharacterSize(30);
    texte_instruction->setFillColor(sf::Color(180,180,180));

    texte_niveau.emplace(police);
    texte_niveau->setCharacterSize(60);
    texte_niveau->setFillColor(sf::Color::White);

}

bool Menu::loadBackground(const std::string& filename, float largeur, float hauteur) {

    texte_instruction->setPosition(sf::Vector2f(largeur / 2.f - 220.f, hauteur / 2.f));
    texte_niveau->setPosition(sf::Vector2f(largeur / 2.f - 140.f, hauteur / 2.f - 80.f));
    texte_gameover->setPosition(sf::Vector2f(largeur / 2.f - 200.f, hauteur / 2.f - 80.f));

    fond_ecran_texture = std::make_unique<sf::Texture>();
    if (fond_ecran_texture->loadFromFile(filename)){
        fond_ecran_sprite = std::make_unique<sf::Sprite> (*fond_ecran_texture);

        float scaleX = largeur / fond_ecran_texture->getSize().x;
        float scaleY = hauteur / fond_ecran_texture->getSize().y;
        fond_ecran_sprite->setScale(sf::Vector2f(scaleX, scaleY));

        return true;
    }
    return false;

}

void Menu::afficher_menu(sf::RenderWindow& fenetre) {
    fenetre.draw(*fond_ecran_sprite);

    for (auto& option : options) {
        fenetre.draw(option);
    }
}

void Menu::afficher_selection(sf::RenderWindow& fenetre, int niveau_choisi){
    texte_niveau->setString("Niveau : " + std::to_string(niveau_choisi));
    fenetre.draw(*texte_instruction);
    fenetre.draw(*texte_niveau);
}

void Menu::afficher_fin(sf::RenderWindow& fenetre){
    
    fenetre.draw(*texte_gameover);
}

void Menu::mouvement_souris(const sf::Vector2f& sourisPos, bool clicked) {
    int old_index_souris = index_souris;
    index_souris = -1;
    
    for (size_t i = 0; i < options.size(); i++){
        sf::FloatRect bornes = options[i].getGlobalBounds();

        if (bornes.contains(sourisPos)) {
            index_souris = static_cast<int>(i);
            break;
        }
    }

    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == index_souris){
            if (clicked) {options[i].setFillColor(sf::Color::Green);}
            else {options[i].setFillColor(sf::Color::Red); }
        }
        else {
            options[i].setFillColor(sf::Color::White);
        }
    }

}    


int Menu::clic_souris(const sf::Vector2f& sourisPos) {
    for (size_t i = 0; i < options.size(); i++) {
        sf::FloatRect bornes = options[i].getGlobalBounds();

        if (bornes.contains(sourisPos)){
            Index = static_cast<int>(i);
            options[i].setFillColor(sf::Color::Green);
            return Index;
        }
    }
    
    return -1; // aucune option cliquée
}

