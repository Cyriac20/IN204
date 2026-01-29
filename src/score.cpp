#include "score.hpp"

// Constructeur du score
Score::Score(float largeur, float hauteur){
    score = 0;
    niveau = 0; 
    nb_ligne_casse = 0;
    if (!police.openFromFile("../src/res/Orbitron-Regular.ttf")) {
        std::cerr << "Erreur : police non trouvée" << std::endl;
    }
    
    score_texte.emplace(police);
    score_texte->setCharacterSize(24);
    score_texte->setFillColor(sf::Color::White);
    score_texte->setPosition({largeur/4.f, hauteur/5.f - 50.f});

    niveau_texte.emplace(police);
    niveau_texte->setCharacterSize(24);
    niveau_texte->setFillColor(sf::Color::White);
    niveau_texte->setPosition({largeur/4.f, hauteur/5.f - 20.f});
    
    int y_offset = 150;
    for (int i = 0; i < 7; ++i){

        sf::Text texte(police);
        //texte.setString(std::to_string(compteurs[i])); // Votre compteur
        texte.setPosition({largeur/(float)3.1 + 20 , hauteur/8 + y_offset});
        textes_stat.push_back(texte);
        y_offset += 65;
    } 

    actualisation();
      
}


// Fonction d'actualisation de l'affichage du score et du niveau choisi
void Score::actualisation(){
    score_texte->setString("SCORE : " + std::to_string(score) );
    niveau_texte->setString("NIVEAU : " + std::to_string(niveau) );
   
}

void Score::actualisation_stat(std::array<int, 7> compteurs){
    for (int i = 0; i < 7; ++i){
        textes_stat[i].setString(std::to_string(compteurs[i])); 
    } 
    
}


// Fonction d'incrémentation du score
void Score::ajout(int points){
    score += points;
    actualisation();
}


// Fonction permettant de détecter lorsque plusieurs lignes sont détruites simultanément 
int Score::combo(std::array<int,4> lignes){
    int s = 0;
    for (int ligne : lignes){
        if (ligne > -1){
            s++;
        }
    }
    return s;
}



// Fonction de calcul du score à ajouter en fonction du niveau de difficulté choisi ainsi que du nombre de lignes détruite simultanément
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

// Fonction de reset 
void Score::reset(){
    score = 0;
    niveau = 0; 
    nb_ligne_casse = 0;
    for (int i = 0; i < 7; ++i){
        compteurs_stat[i] = 0;
    }
    actualisation();
}

// Fonction d'affichage du score et du niveau choisi
void Score::afficher(sf::RenderWindow& fenetre){
    fenetre.draw(*score_texte);
    fenetre.draw(*niveau_texte);
    for (int i = 0; i < 7; ++i){
        fenetre.draw(textes_stat[i]);
    }
}

std::vector<std::vector<std::array<int, 2>>> positions_pieces = {
        // Pièce I
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        
        // Pièce O
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        
        // Pièce T
        {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
        
        // Pièce L
        {{0, 2}, {1, 0}, {1, 1}, {1, 2}},
        
        // Pièce J
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
        
        // Pièce S
        {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
        
        // Pièce Z
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}}
};

const sf::Color couleur[7] = {sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White
    };


void afficherStat(sf::RenderWindow& fenetre, int x, int y, int TAILLE_CASE, int hauteur)
{
    sf::VertexArray sommets(sf::PrimitiveType::Triangles);
    int y_offset = hauteur/8;
    float taille = TAILLE_CASE - 2;

    for (int i = 0; i < 7; i++) {
    
    sf::Color couleurPiece = couleur[i];
    
    for (auto& pos : positions_pieces[i]) {

        float px = x + (pos[1] + 4) * TAILLE_CASE;
        float py = y + y_offset + pos[0] * TAILLE_CASE;
        
        sommets.append({{px, py}, couleurPiece});
        sommets.append({{px + taille, py}, couleurPiece});
        sommets.append({{px, py + taille}, couleurPiece});
        
        
        sommets.append({{px + taille, py}, couleurPiece});
        sommets.append({{px + taille, py + taille}, couleurPiece});
        sommets.append({{px, py + taille}, couleurPiece});
    }

    y_offset += hauteur/14;
    }
    fenetre.draw(sommets);
}