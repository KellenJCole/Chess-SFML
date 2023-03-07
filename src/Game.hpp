#pragma once

#include "PieceMap.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Piece.hpp"

class Game {
private:
    void processEvents();
    void update();
    void render();
    void selectPiece(sf::Vector2i mp);
    void movePiece(sf::Vector2i mp);
private:
    sf::RenderWindow mWindow;
    sf::Texture mBoardTexture;
    sf::Sprite mBoard;
    PieceMap board;
    sf::Sprite tile;
    bool mFirstClick; // Flag to track whether it's the first click or not
    int selectPieceI;
    int selectPieceJ;
    int movePieceI;
    int movePieceJ;
    bool mPieceMoved = false;
public:
    Game();
    void run();
};