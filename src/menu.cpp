#include "menu.hpp"
#include <iostream>

// Palette de couleur pour le menu
    std::vector<sf::Color> couleurs = {
        sf::Color(255, 60, 60),   // Rouge
        sf::Color(255, 220, 60),  // Jaune
        sf::Color(60, 180, 255)   // Bleu
    };

// Constructeur du menu (permet de préparer tout ce qui sera affiché dans le menu)
Menu::Menu(float largeur, float hauteur) : Index(0) {

    // Chargement de la police utilisée pour tous les textes du menu
    if (!police.openFromFile("../src/res/Orbitron-Medium.ttf")) {
        std::cerr << "Erreur : police non trouvée" << std::endl;
    }

    // Liste des options principales affichées dans le menu
    std::vector<std::string> items = {"Jouer", "Commandes", "Quitter"};


     // Création et placement de chaque option du menu
    for (size_t i = 0; i < items.size(); i++){
        sf::Text texte(police, items[i], 50);
        texte.setFillColor(couleurs[i]);
        
        sf::FloatRect textBounds = texte.getLocalBounds();
        texte.setOrigin(sf::Vector2f(textBounds.size.x / 2.f, textBounds.size.y / 2.f));
        texte.setPosition(sf::Vector2f(largeur / 2.f, hauteur / 2.f + i * 80.f - 30.f));

        options.push_back(texte);
    }

    // Texte affiché en cas de défaite (écran Game Over)
    texte_gameover.emplace(police);
    texte_gameover->setString("Game Over");
    texte_gameover->setCharacterSize(80);
    texte_gameover->setFillColor(sf::Color::Red);

    // Texte d'instructions pour la sélection du niveau
    texte_instruction.emplace(police);
    texte_instruction->setString("<-  ->  choisir | Entree  valider");
    texte_instruction->setCharacterSize(30);
    texte_instruction->setFillColor(sf::Color(180,180,180));

    // Texte utilisé pour afficher le niveau sélectionné dans l'écran de sélection du niveau
    texte_niveau.emplace(police);
    texte_niveau->setCharacterSize(60);
    texte_niveau->setFillColor(sf::Color::White);

    // Textes pour l'écran des commandes

    texte_commandes.emplace(police);
    texte_commandes->setString(
        "Fleche GAUCHE  :  Deplacer a gauche\n\n"
        "Fleche DROITE  :  Deplacer a droite\n\n"
        "Fleche BAS     :  Descente rapide\n\n"
        "Fleche HAUT    :  Rotation\n\n"
        "ENTREE         :  Valider\n\n"
        "ECHAP          :  Retour au menu"
    );
    texte_commandes->setCharacterSize(30);
    texte_commandes->setFillColor(sf::Color(200,200,200));

}


//Fonction servant à charger et configurer l’image de fond du menu
bool Menu::loadBackground(const std::string& filename, float largeur, float hauteur) {

    texte_instruction->setPosition(sf::Vector2f(largeur / 2.f - 220.f, hauteur / 2.f));
    texte_niveau->setPosition(sf::Vector2f(largeur / 2.f - 140.f, hauteur / 2.f - 80.f));
    texte_gameover->setPosition(sf::Vector2f(largeur / 2.f - 200.f, hauteur / 2.f - 80.f));
    texte_commandes->setPosition(sf::Vector2f(largeur / 2.f - 250.f, hauteur / 2.f - 100.f));

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


//Fonction servant à charge et configurer l'image de fond du menu "COMMANDES"

bool Menu::loadCommandesBackground(const std::string& filename, float largeur, float hauteur) {

    fond_commandes_texture = std::make_unique<sf::Texture>();
    if (fond_commandes_texture->loadFromFile(filename)){
        fond_commandes_sprite = std::make_unique<sf::Sprite> (*fond_commandes_texture);

        float scaleX = largeur / fond_commandes_texture->getSize().x;
        float scaleY = hauteur / fond_commandes_texture->getSize().y;
        fond_commandes_sprite->setScale(sf::Vector2f(scaleX, scaleY));

        return true;
    }
    return false;

}

// Fonction d'affichage du menu principal
void Menu::afficher_menu(sf::RenderWindow& fenetre) {
    fenetre.draw(*fond_ecran_sprite);

    for (auto& option : options) {
        fenetre.draw(option);
    }
}

// Fonction d'affichage de la fenêtre de commandes
void Menu::afficher_commandes(sf::RenderWindow& fenetre)
{
    if (fond_commandes_sprite)
        fenetre.draw(*fond_commandes_sprite);

    // Ensuite tu dessines ton texte COMMANDES + les touches
    fenetre.draw(*texte_commandes);
}


// Fonction d'affichage du menu de selection de niveau en amont de la partie
void Menu::afficher_selection(sf::RenderWindow& fenetre, int niveau_choisi){
    texte_niveau->setString("Niveau : " + std::to_string(niveau_choisi));
    fenetre.draw(*texte_instruction);
    fenetre.draw(*texte_niveau);
}

// Fonction d'affichage du Game Over en cas de fin de partie
void Menu::afficher_fin(sf::RenderWindow& fenetre){
    
    fenetre.draw(*texte_gameover);
}

// Fonction servant à gérer l’interaction dynamique de la souris avec le menu
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
            if (clicked) {options[i].setFillColor(sf::Color(60, 255, 160));}
            else {options[i].setFillColor(sf::Color(180, 70, 255)); }
        }
        else {
            options[i].setFillColor(couleurs[i]);
        }
    }

}    

// Fonction permettant de détecter sur quel bouton du menu le joueur a cliqué
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

