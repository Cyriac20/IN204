#include "score.hpp"

Score::Score(){
    score = 0;
    niveau = 0; 
    nb_ligne_casse = 0;
    if (!police.openFromFile("../src/res/poppins1.ttf")) {
        std::cerr << "Erreur : police non trouvée" << std::endl;
    }
    
    score_texte.emplace(police);
    score_texte->setCharacterSize(24);
    score_texte->setFillColor(sf::Color::White);
    score_texte->setPosition({10.f, 10.f});

    niveau_texte.emplace(police);
    niveau_texte->setCharacterSize(24);
    niveau_texte->setFillColor(sf::Color::White);
    niveau_texte->setPosition({10.f, 40.f});
    actualisation();
      
}

void Score::actualisation(){
    score_texte->setString("Score : " + std::to_string(score) );
    niveau_texte->setString("Niveau : " + std::to_string(niveau) );
}

void Score::ajout(int points){
    score += points;
    actualisation();
}

int Score::combo(std::array<int,4> lignes){
    int s = 0;
    for (int ligne : lignes){
        if (ligne > -1){
            s++;
        }
    }
    return s;
}

void Score::calcul(int nb_lignes){
    
    switch(nb_lignes){
        case 1 : 
            ajout(40 * (niveau + 1));
            break;
        case 2 :
            ajout(100 * (niveau + 1));
            break;
        case 3 :
            ajout(300 * (niveau + 1) );
            break;
        case 4 :
            ajout(1200 * (niveau + 1));
            break;
    }
}

void Score::reset(){
    score = 0;
    niveau = 0; 
    nb_ligne_casse = 0;
    actualisation();
}

void Score::afficher(sf::RenderWindow& fenetre){
    fenetre.draw(*score_texte);
    fenetre.draw(*niveau_texte);
}