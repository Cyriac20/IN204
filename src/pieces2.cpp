#include "pieces2.hpp"
#include "grille.hpp"

Piece::Piece() {};

void Piece::mouvement_piece(grille& matrice, sf::Keyboard::Key touche){
    std::array<std::array<int,2>,4> nouvelle_position = position;

    matrice.effacer_piece(*this);

    switch(touche){
        case sf::Keyboard::Key::Left :
        for (int k = 0; k < 4; ++k){

            int i = position[k][0];
            int j = position[k][1];
            if (j > 0  && matrice[i][j-1] == 0){
                nouvelle_position[k][0] = i;
                nouvelle_position[k][1] = j-1;
            } 

            else{ return; }
        }
        break;
        case sf::Keyboard::Key::Right :
            for (int k = 0; k < 4; ++k){
                
                int i = position[k][0];
                int j = position[k][1];
                if (j < 9  && matrice[i][j+1] == 0){
                    nouvelle_position[k][0] = i;
                    nouvelle_position[k][1] = j+1;
                } 

                else{ return; }
            }
            break;
        case sf::Keyboard::Key::Down :
            for (int k = 0; k < 4; ++k){
                
                int i = position[k][0];
                int j = position[k][1];
                if (i < 21  && matrice[i+1][j] == 0){
                    nouvelle_position[k][0] = i+1;
                    nouvelle_position[k][1] = j;
                } 

                else{ return; }
            }
            break;

    }
    // Si la nouvelle position est valide, MAJ de la position de la pièce
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;  // Appliquer la nouvelle position
        matrice.apparition_piece(*this);  
    } else {
        // Si l'emplacement n'est pas valide, réafficher la pièce à son ancienne position
        matrice.apparition_piece(*this);
    }

}

//----------------------- Piece O ---------------------------

PieceO::PieceO(){
    position = {{
                {0,4}, {0,5}, 
                {1,4}, {1,5}
            }};

    couleur = sf::Color::Red;
}

void PieceO::rotate(grille& matrice) {}; //La rotation n'a pas d'effet



//----------------------- Piece I ----------------------------

PieceI::PieceI(){
    position = {{
                {0,3}, {0,4}, {0,5}, {0,6}
            }};

    couleur = sf::Color::Cyan;
}

void PieceI::rotate(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position = position;

    //effacement de la pièce
    matrice.effacer_piece(*this);

    //calcul de la nouvelle position
    int pivotX = position[1][1]; 
    int pivotY = position[1][0]; 

    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX; // colonne relative
        int y = position[i][0] - pivotY; // ligne relative

        // On effectue la rotation de 90° autour du pivot
        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;


    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
        matrice.apparition_piece(*this);
    } else {
        matrice.apparition_piece(*this);
    }
}}


//----------------------- Piece T ---------------------------
PieceT::PieceT(){
    position = {{ {0,4}, {1,3}, {1,4}, 
                        {1,5} }};

    couleur = sf::Color::Yellow;
}

void PieceT::rotate(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position = position;

    //effacement de la pièce
    matrice.effacer_piece(*this);

    //calcul de la nouvelle position
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
        matrice.apparition_piece(*this);
    } else {
        matrice.apparition_piece(*this);
    }
}

//----------------------- Piece L ---------------------------
PieceL::PieceL(){
    position = {{ {0,4}, {1,4}, {2,4}, 
                {2,5} }};

    couleur = sf::Color::Magenta;
}

void PieceL::rotate(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position = position;

    //effacement de la pièce
    matrice.effacer_piece(*this);

    //calcul de la nouvelle position
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
        matrice.apparition_piece(*this);
    } else {
        matrice.apparition_piece(*this);
    }
}

//----------------------- Piece J ---------------------------
PieceJ::PieceJ(){
    position = {{ {0,4}, {1,4}, {2,4}, 
                                {2,3} }};

    couleur = sf::Color::Green;
}

void PieceJ::rotate(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position = position;

    //effacement de la pièce
    matrice.effacer_piece(*this);

    //calcul de la nouvelle position
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
        matrice.apparition_piece(*this);
    } else {
        matrice.apparition_piece(*this);
    }
}

//----------------------- Piece S ---------------------------
PieceS::PieceS(){
    position = {{ {0,4}, {0,5}, 
        {1,3}, {1,4} }};

    couleur = sf::Color::Blue;
}

void PieceS::rotate(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position = position;

    //effacement de la pièce
    matrice.effacer_piece(*this);

    //calcul de la nouvelle position
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
        matrice.apparition_piece(*this);
    } else {
        matrice.apparition_piece(*this);
    }
}

//----------------------- Piece Z ---------------------------
PieceZ::PieceZ(){
    position = {{ {0,4}, {0,5}, 
                        {1,5}, {1,6} }};

    couleur = sf::Color::White;
}

void PieceZ::rotate(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position = position;

    //effacement de la pièce
    matrice.effacer_piece(*this);

    //calcul de la nouvelle position
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
        matrice.apparition_piece(*this);
    } else {
        matrice.apparition_piece(*this);
    }
}