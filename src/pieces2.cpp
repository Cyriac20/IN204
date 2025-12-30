#include "pieces2.hpp"

Piece::Piece() {};

//----------------------- Piece O ---------------------------

PieceO::PieceO(){
    position = {{
                {0,4}, {0,5}, 
                {1,4}, {1,5}
            }};
}

void PieceO::rotate() {}; //La rotation n'a pas d'effet


//----------------------- Piece I ----------------------------

PieceI::PieceI(){
    position = {{
                {0,3}, {0,4}, {0,5}, {0,6}
            }};
}

void PieceI::rotate() {
    //On doit définir un pivot de rotation (ici c'est le deuxième de la ligne)

    int pivotX = position[1][1]; 
    int pivotY = position[1][0]; 

    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX; // colonne relative
        int y = position[i][0] - pivotY; // ligne relative

        // On effectue la rotation de 90° autour du pivot
        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;

}


//----------------------- Piece T ---------------------------
PieceT::PieceT(){
    position = {{ {0,4}, {1,3}, {1,4}, 
                        {1,5} }};
}

void PieceT::rotate() {
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }
}

//----------------------- Piece L ---------------------------
PieceL::PieceL(){
    position = {{ {0,4}, {1,4}, {2,4}, 
                {2,5} }};
}

void PieceL::rotate() {
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }
}

//----------------------- Piece J ---------------------------
PieceJ::PieceJ(){
    position = {{ {0,4}, {1,4}, {2,4}, 
                                {2,3} }};
}

void PieceJ::rotate() {
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }
}

//----------------------- Piece S ---------------------------
PieceS::PieceS(){
    position = {{ {0,4}, {0,5}, 
        {1,3}, {1,4} }};
}

void PieceS::rotate() {
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }
}

//----------------------- Piece Z ---------------------------
PieceZ::PieceZ(){
    position = {{ {0,4}, {0,5}, 
                        {1,5}, {1,6} }};
}

void PieceZ::rotate() {
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        position[i][1] = pivotX - y;
        position[i][0] = pivotY + x;
    }
}