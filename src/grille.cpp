#include <iostream>
#include <array>
#include <numeric>
#include <SFML/Graphics.hpp>

class grille {
    private : 
    std::array< std::array<int,10>, 22> matrice;
    static constexpr int TAILLE_CASE = 30;
    public :
    grille() : matrice(
        
    {{   {0,0,0,0,0,0,0,0,0,0},
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
        {0,0,0,0,0,0,0,0,0,0} }}) {}

    void ligne_complete(int i){
            int somme = std::accumulate(matrice[i].begin(), matrice[i].end(),0);
            if (somme == 10){
                matrice[i] = {0,0,0,0,0,0,0,0,0,0};
            }
    }

    void set(int i, int j, int valeur){
        matrice[i][j] = valeur;

    }
    void afficher(sf::RenderWindow& window, int offsetX = 50, int offsetY = 50){
        sf::RectangleShape carre(sf::Vector2f(TAILLE_CASE -1, TAILLE_CASE - 1));

        for (int i = 0; i < 22; ++i){
            
        }

    }

};

int main(){
    grille matrice;
    for (int j = 0; j < 10; ++j){
        matrice.set(4,j,1);
    }
    matrice.afficher();
    matrice.ligne_complete(4);
    matrice.afficher();
    
}