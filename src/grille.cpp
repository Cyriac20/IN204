#include "grille.hpp"
#include <iostream>
#include <numeric>

const sf::Color couleur[7] = {sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White
};

grille::grille() : matrice(
    {{   
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0} }}) {}; 

int grille::valeur(int i, int j){
    return matrice[i][j];
}

    

void grille::ligne_complete(int i){
        int somme = std::accumulate(matrice[i].begin(), matrice[i].end(),0);
        if (somme == 10){
            matrice[i] = {0,0,0,0,0,0,0,0,0,0};
        }
}

void grille::set(int i, int j, int valeur){
    matrice[i][j] = valeur;

}

void grille::afficher(sf::RenderWindow& fenetre, int offsetX, int offsetY){

    sf::VertexArray sommets(sf::PrimitiveType::Triangles);
    sf::VertexArray lignes(sf::PrimitiveType::Lines);


    for (int i = 0; i < 22; ++i){

        for (int j = 0; j < 10; ++j)
        {
            
            if ( matrice[i][j] != 0) { // si case vide, couleur noir sinon couleur bleu
                
                float x = offsetX + j * TAILLE_CASE;
                float y = offsetY + i * TAILLE_CASE;
                float taille = TAILLE_CASE - 1;
                int indice = matrice[i][j] - 1;
                sommets.append({ {x,y} , couleur[indice] });
                sommets.append({ {x + taille, y} , couleur[indice] });
                sommets.append({ {x, y + taille} , couleur[indice] });

                sommets.append({ {x + taille, y + taille} , couleur[indice] });
                sommets.append({ {x, y + taille} , couleur[indice] });
                sommets.append({ {x + taille, y } , couleur[indice] });

            }
        }


    }
    for (int i = 0; i <= 22; i++){
            float y_ligne = offsetY + i * TAILLE_CASE;
            lignes.append( {{offsetX, y_ligne }, sf::Color(50,50,50) } );
            lignes.append( {{offsetX + 10 * TAILLE_CASE, y_ligne}, sf::Color(50,50,50)} );
        
    }

    for (int j = 0; j <= 10; j++){

        float x_ligne = offsetX + j * TAILLE_CASE;
        lignes.append( {{x_ligne, offsetY }, sf::Color(50,50,50)});
        lignes.append( {{x_ligne, offsetY + 22 * TAILLE_CASE}, sf::Color(50,50,50)});
    }
    fenetre.draw(sommets);
    fenetre.draw(lignes);


}





bool grille::emplacement_disponible(std::array<std::array<int,2>,4> position){

    for (std::array<int,2> coord : position){
        int i = coord[0];
        int j = coord[1];
        if (i > 21 || i < 0 || j > 9 || j < 0 || matrice[i][j] != 0){
            return false;
        }
    }
    return true;

}
