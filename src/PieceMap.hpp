#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.hpp"
#include <iostream>

class PieceMap {
private:
    Piece pieceMap[8][8];
    sf::Texture emptyTexture;
    sf::Texture textures[2][6];
    bool whiteTurn = true;
public:
    PieceMap();
    void storeTextures();
    void setTextures();
    Piece* getPieceFromMap(int i, int j);
    void updatePiecePosition(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ);
    bool checkIfValidPawnMove(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ);
    bool checkIfValidKnightMove(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ);
    bool checkIfValidRookMove(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ);
    bool getTurnColor();
    void printMap();

};
