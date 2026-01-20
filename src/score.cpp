#include "score.hpp"

Score::Score(){
    score = 0;
    if (!police.openFromFile("../src/res/poppins1.ttf")) {
        std::cerr << "Erreur : police non trouvée" << std::endl;
    }

    score_texte.setFont(police);
    score_texte.setCharacterSize(24);
    score_texte.setFillColor(sf::Color::White);
    score_texte.setPosition({10.f, 10.f});
    score_texte.setString("Score : " + std::to_string(score));  
}

void Score::ajout(int points){
    score += points;
}

void Score::afficher(sf::RenderWindow& fenetre){

}