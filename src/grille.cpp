#include "grille.hpp"
#include <iostream>
#include <numeric>

const sf::Color couleur[7] = {sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White
};


//Définition de la grille : 22 lignes et 10 colonnes 
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


// Fonction permettant d'extraire facilement les valeurs des emplacements de la grille
int grille::valeur(int i, int j){
    return matrice[i][j];
}

    
// Fonction de repérage des lignes complètes (en vue de leur destruction)
std::array<int,4> grille::ligne_complete(){
    std::array<int,4> lignes = {-1, -1, -1, -1};
    int nb = 0;
    for (int i = 0; i < 22; ++i){
        for (int j = 0; j < 10; ++j){
            if (matrice[i][j] == 0){ break; }

            else if (j == 9)  {
                for (int k = 0; k < 10; k++){
                    matrice[i][k] = 0;
                }
                lignes[nb] = i; 
                nb++;
            }      
        }
    }
    return lignes;
}


// Fonction d'actualisation de la grille après destruction d'une ligne
void grille::actualisation(std::array<int,4> lignes){
    for (int n = 0; n < 4; ++n){
        if (lignes[n] > 0){
            int k = lignes[n];
            for (int i = k; i >= 0; --i){
                for (int j = 0; j < 10; ++j){
                    if (i > 0){
                        matrice[i][j] = matrice[i-1][j];
                    }
                }
            }
        }
    }
}

// Fonction de modification d'une case de la grille
void grille::set(int i, int j, int valeur){
    matrice[i][j] = valeur;

}


// Fonction d'affichage de la grille
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




// Fonction vérifiant la disponibilité d'un emplacement : permet de s'assurer de toujours rester dans les limites de la grille 
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
