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

                sommets.append({ {x,y} , sf::Color::Cyan });
                sommets.append({ {x + taille, y} , sf::Color::Cyan });
                sommets.append({ {x, y + taille} , sf::Color::Cyan });

                sommets.append({ {x + taille, y + taille} , sf::Color::Cyan });
                sommets.append({ {x, y + taille} , sf::Color::Cyan });
                sommets.append({ {x + taille, y } , sf::Color::Cyan });

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

void grille::apparition_piece(Piece piece){
    for (std::array<int,2> coord : piece.position){
        matrice[coord[0]][coord[1]] = 1;
    }
}

void grille::mouvement_piece(Piece& piece, sf::Keyboard::Key touche){
    std::array<std::array<int,2>,4> nouvelle_position;

    effacer_piece(piece);

    switch(touche){
        case sf::Keyboard::Key::Left :
        for (int k = 0; k < 4; ++k){

            int i = piece.position[k][0];
            int j = piece.position[k][1];
            if (j > 0  && matrice[i][j-1] == 0){
                nouvelle_position[k][0] = i;
                nouvelle_position[k][1] = j-1;
            } 

            else{ return; }
        }
        break;
        case sf::Keyboard::Key::Right :
            for (int k = 0; k < 4; ++k){
                
                int i = piece.position[k][0];
                int j = piece.position[k][1];
                if (j < 9  && matrice[i][j+1] == 0){
                    nouvelle_position[k][0] = i;
                    nouvelle_position[k][1] = j+1;
                } 

                else{ return; }
            }
            break;
        case sf::Keyboard::Key::Down :
            for (int k = 0; k < 4; ++k){
                
                int i = piece.position[k][0];
                int j = piece.position[k][1];
                if (i < 21  && matrice[i+1][j] == 0){
                    nouvelle_position[k][0] = i+1;
                    nouvelle_position[k][1] = j;
                } 

                else{ return; }
            }
            break;

    }
    piece.position = nouvelle_position;

}

void grille::rotation_piece(Piece& piece){
    std::array<std::array<int,2>,4> nouvelle_position;
    effacer_piece(piece);
    int k = piece.rotation;
    
    nouvelle_position[0] = {piece.position[0][0]+2*k, piece.position[0][1]+2*k};
    nouvelle_position[1] = {piece.position[1][0]+k, piece.position[1][1]+k};
    nouvelle_position[2] = {piece.position[2][0], piece.position[2][1]};
    nouvelle_position[3] = {piece.position[3][0]-k, piece.position[3][1]-k};
    
    if (emplacement_disponible(nouvelle_position)){
        piece.position = nouvelle_position;
        piece.rotation *= -1;
    }
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

void grille::effacer_piece(Piece& piece){
    for (std::array<int,2> coord : piece.position){
        matrice[coord[0]][coord[1]] = 0; 
    }
}