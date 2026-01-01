#ifndef PIECES2_HPP
#define PIECES2_HPP

#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "grille.hpp"


class Piece {
    protected:
        Piece(); //On ne crée pas directement la pièce dans la classe mère
        int id;  // couleur de la pièce

    public:
        std::array<std::array<int,2>,4> position;
        
        void apparition(grille& matrice);
        void effacer(grille& matrice);
        virtual ~Piece() = default; //évite les fuites mémoires
        void mouvement(grille& matrice, sf::Keyboard::Key touche);
        virtual void rotation(grille& matrice) = 0; //indique que la rotation des pièces est propre à chaque pièce

};


// Pièce I
class PieceI : public Piece {
private:
    int etat_rotation;
public:
    PieceI();
    ~PieceI() override{};
    void rotation(grille& matrice) override; // rotation spécifique
};

// Pièce O
class PieceO : public Piece {

public:
    PieceO();
    ~PieceO() override {};
    void rotation(grille& matrice) override; // rotation spécifique (pas de rotation)
};

// Pièce T
class PieceT : public Piece {

public:
    PieceT();
    ~PieceT() override {};
    void rotation(grille& matrice) override; // rotation spécifique
};

// Pièce L
class PieceL : public Piece {

public:
    PieceL();
    ~PieceL() override {};
    void rotation(grille& matrice) override; // rotation spécifique
};

// Pièce J
class PieceJ : public Piece {

public:
    PieceJ();
    ~PieceJ() override {};
    void rotation(grille& matrice) override; // rotation spécifique
};

// Pièce Z
class PieceZ : public Piece {
private : 
    int etat_rotation;
    
public:
    PieceZ();
    ~PieceZ() override {};
    void rotation(grille& matrice) override; // rotation spécifique
};

// Pièce S
class PieceS : public Piece {
private: 
    
    int etat_rotation;
public:
    PieceS();
    ~PieceS() override {};
    void rotation(grille& matrice) override; // rotation spécifique
};

std::unique_ptr<Piece> piece_aleatoire();
#endif