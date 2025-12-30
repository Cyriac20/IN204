#ifndef PIECES2_HPP
#define PIECES2_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

class Piece {
    protected:
        Piece(); //On ne crée pas directement la pièce dans la classe mère
    
    public:
        std::array<std::array<int,2>,4> position;
    
    
        virtual ~Piece() = default; //évite les fuites mémoires
        
        virtual void rotate() = 0; //indique que la rotation des pièces est propre à chaque pièce

};


// Pièce I
class PieceI : public Piece {
public:
    PieceI();
    void rotate() override; // rotation spécifique
};

// Pièce O
class PieceO : public Piece {
public:
    PieceO();
    void rotate() override; // rotation spécifique (pas de rotation)
};

// Pièce T
class PieceT : public Piece {
public:
    PieceT();
    void rotate() override; // rotation spécifique
};

// Pièce L
class PieceL : public Piece {
public:
    PieceL();
    void rotate() override; // rotation spécifique
};

// Pièce J
class PieceJ : public Piece {
public:
    PieceJ();
    void rotate() override; // rotation spécifique
};

// Pièce Z
class PieceZ : public Piece {
public:
    PieceZ();
    void rotate() override; // rotation spécifique
};

// Pièce S
class PieceS : public Piece {
public:
    PieceS();
    void rotate() override; // rotation spécifique
};
#endif