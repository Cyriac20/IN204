#include "grille.hpp"
#include <iostream>
#include <numeric>


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



    

void grille::ligne_complete(int i){
        int somme = std::accumulate(matrice[i].begin(), matrice[i].end(),0);
        if (somme == 10){
            matrice[i] = {0,0,0,0,0,0,0,0,0,0};
        }
}

void grille::set(int i, int j, int valeur){
    matrice[i][j] = valeur;

}

void grille::afficher(sf::RenderWindow& window, int offsetX, int offsetY){

    sf::RectangleShape carre(sf::Vector2f(TAILLE_CASE -1, TAILLE_CASE - 1)); //création de l'objet matrice

    for (int i = 0; i < 22; ++i){
        for (int j = 0; j < 10; ++j)
        {
            carre.setPosition(sf::Vector2f(offsetX + j * TAILLE_CASE, offsetY + i*TAILLE_CASE));
             //position de la matrice
            if ( matrice[i][j] == 0) { // si case vide, couleur noir sinon couleur bleu
                carre.setFillColor(sf::Color(30,30,30)); 
            }
            else {
                carre.setFillColor(sf::Color::Cyan);
            }

            carre.setOutlineThickness(1); // pour les contours de la matrice
            carre.setOutlineColor(sf::Color(50,50,50));
            window.draw(carre);
        }

    }

}



