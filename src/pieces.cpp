#include "pieces.hpp"
#include "grille.hpp"

Piece::Piece() {};

void Piece::apparition(grille& matrice){
    for (std::array<int,2> coord : position){
        matrice.set(coord[0], coord[1], id);
    }
}

void Piece::effacer(grille& matrice){
    for (std::array<int,2> coord : position){
        matrice.set(coord[0], coord[1], 0); 
    }
}

bool Piece::mouvement(grille& matrice, sf::Keyboard::Key touche){
    std::array<std::array<int,2>,4> nouvelle_position = position;

    effacer(matrice);

    switch(touche){
        case sf::Keyboard::Key::Left :
        for (int k = 0; k < 4; ++k){

            int i = position[k][0];
            int j = position[k][1];
            if (j > 0  && matrice.valeur(i,j-1) == 0){
                nouvelle_position[k][0] = i;
                nouvelle_position[k][1] = j-1;
            } 

            else{ apparition(matrice); //s'il y a un emplacement qui n'est pas dispo on return et in remet la pièce là ou elle était
                return 0; }
        }
        break;
        case sf::Keyboard::Key::Right :
            for (int k = 0; k < 4; ++k){
                
                int i = position[k][0];
                int j = position[k][1];
                if (j < 9  && matrice.valeur(i,j+1) == 0){
                    nouvelle_position[k][0] = i;
                    nouvelle_position[k][1] = j+1;
                } 

                else{ apparition(matrice);
                    return 0; }
            }
            break;
        case sf::Keyboard::Key::Down :
            for (int k = 0; k < 4; ++k){
                
                int i = position[k][0];
                int j = position[k][1];
                if (i < 21  && matrice.valeur(i+1, j) == 0){
                    nouvelle_position[k][0] = i+1;
                    nouvelle_position[k][1] = j;
                } 

                else{apparition(matrice); 
                    return 0; }
            }
            break;
    }
    
    position = nouvelle_position;  // Appliquer la nouvelle position
    apparition(matrice);
    return 1;
    

}

//----------------------- Piece O ---------------------------

PieceO::PieceO(){
    position = {{
                {0,4}, {0,5}, 
                {1,4}, {1,5}
            }};
    id = 1;
    
}

void PieceO::rotation(grille& matrice) {}; //La rotation n'a pas d'effet



//----------------------- Piece I ----------------------------

PieceI::PieceI(){
    position = {{
                {0,3}, {0,4}, {0,5}, {0,6}
            }};
    etat_rotation = 1;
    id = 2;
}

void PieceI::rotation(grille& matrice){
    std::array<std::array<int,2>,4> nouvelle_position;
    effacer(matrice);
    int k = etat_rotation;
    
    nouvelle_position[0] = {position[0][0] - k, position[0][1] + k};
    nouvelle_position[1] = {position[1][0], position[1][1]};
    nouvelle_position[2] = {position[2][0] + k, position[2][1] - k};
    nouvelle_position[3] = {position[3][0] + 2*k, position[3][1]- 2*k};
    
    if (matrice.emplacement_disponible(nouvelle_position)){
        position = nouvelle_position;
        etat_rotation *= -1;
    }
    apparition(matrice);
}


//----------------------- Piece T ---------------------------
PieceT::PieceT(){
    position = {{ {0,4}, {1,3}, {1,4}, 
                        {1,5} }};
    id = 3;

}

void PieceT::rotation(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position;

    //effacement de la pièce
    effacer(matrice);

    //calcul de la nouvelle position
    int pivotX = position[2][1];
    int pivotY = position[2][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        nouvelle_position[i][1] = pivotX + y;
        nouvelle_position[i][0] = pivotY - x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
    }
    apparition(matrice);
    
}

//----------------------- Piece L ---------------------------
PieceL::PieceL(){
    position = {{ {0,3}, {0,4}, {0,5}, 
                {1,3} }};

    id = 4;
}

void PieceL::rotation(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position;

    //effacement de la pièce
    effacer(matrice);

    //calcul de la nouvelle position
    int pivotX = position[1][1];
    int pivotY = position[1][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        nouvelle_position[i][1] = pivotX + y;
        nouvelle_position[i][0] = pivotY - x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
    }
    apparition(matrice);
}

//----------------------- Piece J ---------------------------
PieceJ::PieceJ(){
    position = {{ {0,3}, {1,3}, {1,4}, 
                                {1,5} }};

    id = 5;
}

void PieceJ::rotation(grille& matrice) {
    //save de la position actuelle de la pièce
    std::array<std::array<int, 2>, 4> nouvelle_position;

    //effacement de la pièce
    effacer(matrice);

    //calcul de la nouvelle position
    int pivotX = position[2][1];
    int pivotY = position[2][0];
    for (int i = 0; i < 4; ++i) {
        int x = position[i][1] - pivotX;
        int y = position[i][0] - pivotY;

        nouvelle_position[i][1] = pivotX + y;
        nouvelle_position[i][0] = pivotY - x;
    }

    //On vérifie que le nouvel emplacement est valide, et on l'affiche le cas échéant
    if (matrice.emplacement_disponible(nouvelle_position)) {
        position = nouvelle_position;
    }
    apparition(matrice);
}

//----------------------- Piece S ---------------------------
PieceS::PieceS(){
    position = {{ {0,4}, {0,5}, 
        {1,3}, {1,4} }};
    etat_rotation = 1;
    id = 6;
}

void PieceS::rotation(grille& matrice){

    std::array<std::array<int,2>,4> nouvelle_position;
    effacer(matrice);
    int k = etat_rotation;
    
    nouvelle_position[0] = {position[0][0] , position[0][1] };
    nouvelle_position[1] = {position[1][0] - k, position[1][1] - k};
    nouvelle_position[2] = {position[2][0] , position[2][1] + 2*k};
    nouvelle_position[3] = {position[3][0] - k , position[3][1] + k};
    
    if (matrice.emplacement_disponible(nouvelle_position)){
        position = nouvelle_position;
        etat_rotation *= -1;
    }
    apparition(matrice);
}

//----------------------- Piece Z ---------------------------
PieceZ::PieceZ(){
    position = {{ {0,4}, {0,5}, 
                        {1,5}, {1,6} }};
    etat_rotation = 1;
    id = 7;
}

void PieceZ::rotation(grille& matrice){

    std::array<std::array<int,2>,4> nouvelle_position;
    effacer(matrice);
    int k = etat_rotation;
    
    nouvelle_position[0] = {position[0][0] + k, position[0][1] + k };
    nouvelle_position[1] = {position[1][0] , position[1][1] };
    nouvelle_position[2] = {position[2][0] - k , position[2][1] + k};
    nouvelle_position[3] = {position[3][0] - 2*k , position[3][1] };
    
    if (matrice.emplacement_disponible(nouvelle_position)){
        position = nouvelle_position;
        etat_rotation *= -1;
    }
    apparition(matrice);
}


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1,7);

std::unique_ptr<Piece> piece_aleatoire(){
    int choix = distrib(gen);
    switch(choix){
        case 1:
            return std::make_unique<PieceI>();
        case 2:
            return std::make_unique<PieceO>();
        case 3:
            return std::make_unique<PieceT>();
        case 4:
            return std::make_unique<PieceL>();
        case 5:
            return std::make_unique<PieceJ>();
        case 6:
            return std::make_unique<PieceS>();
        case 7:
            return std::make_unique<PieceZ>();
    }
    return nullptr;

}

bool Piece::gravite(sf::Clock& horloge, grille& matrice, float niveau){
    float limite = (48-5*niveau)/60;
    if (horloge.getElapsedTime().asSeconds() > limite){
        horloge.restart();
        return mouvement(matrice, sf::Keyboard::Key::Down);
    }
    return 1;
}