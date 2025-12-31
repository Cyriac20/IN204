#ifndef PIECES2_HPP
#define PIECES2_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "grille.hpp"


class Piece {
    protected:
        Piece(); //On ne crée pas directement la pièce dans la classe mère
        sf::Color couleur;  // couleur de la pièce

    public:
        std::array<std::array<int,2>,4> position;
        
    
        virtual ~Piece() = default; //évite les fuites mémoires
        void mouvement_piece(grille& matrice, sf::Keyboard::Key touche);
        virtual void rotate(grille& matrice) = 0; //indique que la rotation des pièces est propre à chaque pièce

        sf::Color getColor() { return couleur; }
};


// Pièce I
class PieceI : public Piece {
public:
    PieceI();
    void rotate(grille& matrice) override; // rotation spécifique
};

// Pièce O
class PieceO : public Piece {
public:
    PieceO();
    void rotate(grille& matrice) override; // rotation spécifique (pas de rotation)
};

// Pièce T
class PieceT : public Piece {
public:
    PieceT();
    void rotate(grille& matrice) override; // rotation spécifique
};

// Pièce L
class PieceL : public Piece {
public:
    PieceL();
    void rotate(grille& matrice) override; // rotation spécifique
};

// Pièce J
class PieceJ : public Piece {
public:
    PieceJ();
    void rotate(grille& matrice) override; // rotation spécifique
};

// Pièce Z
class PieceZ : public Piece {
public:
    PieceZ();
    void rotate(grille& matrice) override; // rotation spécifique
};

// Pièce S
class PieceS : public Piece {
public:
    PieceS();
    void rotate(grille& matrice) override; // rotation spécifique
};
#endif