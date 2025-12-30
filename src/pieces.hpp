#ifndef PIECES_HPP
#define PIECES_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

class Piece {
    private:
    
    public:
    //~Piece();
    int rotation;
    std::array<std::array<int,2>,4> position;

    
    Piece();

};



#endif