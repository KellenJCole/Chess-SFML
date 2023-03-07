#pragma once

#include <SFML/Graphics.hpp>

class Piece {
public:
    Piece();
    Piece(int piece);

    void setPieceId(int piece);
    int getPieceId();

    void setMoved();
    bool isFirstMove();

    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;
    void setPieceType(int t);
    int getPieceType();

private:
    int id;
    sf::Image pImage;
    sf::Sprite pSprite = sf::Sprite();

    sf::Image emptyImage;
    sf::Texture emptyTexture;
    sf::Sprite emptySprite;
    bool hasMoved;
    int pieceType;
};