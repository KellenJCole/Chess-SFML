#include "PieceMap.hpp"

void PieceMap::storeTextures() {
    if (!textures[0][0].loadFromFile("Media/Textures/WhitePawn.png"))
        throw std::runtime_error("Failed to load WhitePawn.png");
    if (!textures[0][1].loadFromFile("Media/Textures/BlackPawn.png"))
        throw std::runtime_error("Failed to load BlackPawn.png");
    if (!textures[0][2].loadFromFile("Media/Textures/WhiteKnight.png"))
        throw std::runtime_error("Failed to load WhiteKnight.png");
    if (!textures[0][3].loadFromFile("Media/Textures/BlackKnight.png"))
        throw std::runtime_error("Failed to load BlackKnight.png");
    if (!textures[0][4].loadFromFile("Media/Textures/WhiteBishop.png"))
        throw std::runtime_error("Failed to load WhiteBishop.png");
    if (!textures[0][5].loadFromFile("Media/Textures/BlackBishop.png"))
        throw std::runtime_error("Failed to load BlackBishop.png");
    if (!textures[1][0].loadFromFile("Media/Textures/WhiteRook.png"))
        throw std::runtime_error("Failed to load WhiteRook.png");
    if (!textures[1][1].loadFromFile("Media/Textures/BlackRook.png"))
        throw std::runtime_error("Failed to load BlackRook.png");
    if (!textures[1][2].loadFromFile("Media/Textures/WhiteQueen.png"))
        throw std::runtime_error("Failed to load WhiteQueen.png");
    if (!textures[1][3].loadFromFile("Media/Textures/BlackQueen.png"))
        throw std::runtime_error("Failed to load BlackQueen.png");
    if (!textures[1][4].loadFromFile("Media/Textures/WhiteKing.png"))
        throw std::runtime_error("Failed to load WhiteKing.png");
    if (!textures[1][5].loadFromFile("Media/Textures/BlackKing.png"))
        throw std::runtime_error("Failed to load BlackKing.png");
    if (!emptyTexture.loadFromFile("Media/Textures/EmptySpace.png"))
        throw std::runtime_error("Failed to load EmptySpace.png");
}

void PieceMap::setTextures() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (pieceMap[i][j].getPieceId() == 12) {
                pieceMap[i][j].getSprite().setTexture(emptyTexture);
            }
            else {
                pieceMap[i][j].getSprite().setTexture(textures[getPieceFromMap(i, j)->getPieceId() / 6][getPieceFromMap(i, j)->getPieceId() % 6]);
            }
            pieceMap[i][j].getSprite().setPosition(j * 64.f + 2.f, i * 64.f + 2.f);
            pieceMap[i][j].getSprite().setScale(1, 1);
        }
    }
}

PieceMap::PieceMap() {
    storeTextures();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i == 0) && ((j == 0) || (j == 7))) { // Black Rooks
                pieceMap[i][j].setPieceId(7);
            }
            else if ((i == 0) && ((j == 1) || (j == 6))) { // Black Knights
                pieceMap[i][j].setPieceId(3);
            }
            else if ((i == 0) && ((j == 2) || (j == 5))) { // Black Bishops
                pieceMap[i][j].setPieceId(5);
            }
            else if ((i == 0) && (j == 4)) { // Black Queen
                pieceMap[i][j].setPieceId(9);
            }
            else if ((i == 0) && (j == 3)) { // Black King
                pieceMap[i][j].setPieceId(11);
            }
            else if (i == 1) { // Black Pawns
                pieceMap[i][j].setPieceId(1);
            }
            else if (i == 6) { // White Pawns
                pieceMap[i][j].setPieceId(0);
            }
            else if ((i == 7) && ((j == 0) || (j == 7))) { // White Rooks
                pieceMap[i][j].setPieceId(6);
            }
            else if ((i == 7) && ((j == 1) || (j == 6))) { // White Knights
                pieceMap[i][j].setPieceId(2);
            }
            else if ((i == 7) && ((j == 2) || (j == 5))) { // White Bishops
                pieceMap[i][j].setPieceId(4);
            }
            else if ((i == 7) && (j == 4)) { // White Queen
                pieceMap[i][j].setPieceId(8);
            }
            else if ((i == 7) && (j == 3)) { // White King
                pieceMap[i][j].setPieceId(10);
            }
            else {
                // Default empty piece
                pieceMap[i][j].setPieceId(12);
            }
        }
    }
    setTextures();
}

Piece* PieceMap::getPieceFromMap(int i, int j) {
    return &(pieceMap[i][j]);
}

void PieceMap::updatePiecePosition(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ) {
    Piece* sourcePiece = getPieceFromMap(sPieceI, sPieceJ);
    Piece* movePiece = getPieceFromMap(mPieceI, mPieceJ);

    // If it is White's Turn
    if (whiteTurn) {
        if (sourcePiece->getPieceId() == 0) { // If the piece is a white pawn
            if (checkIfValidPawnMove(sPieceI, sPieceJ, mPieceI, mPieceJ)) { // If the pawn's move is valid
                *movePiece = *sourcePiece; // Move the pawn
                sourcePiece->setPieceId(12);
                sourcePiece->getSprite().setTexture(emptyTexture);
                movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
                whiteTurn = false;
            }
        }
        // If the piece is any other white piece
        else if (sourcePiece->getPieceId() == 2) {// If the piece is a white knight
            if (checkIfValidKnightMove(sPieceI, sPieceJ, mPieceI, mPieceJ)) {
                *movePiece = *sourcePiece; // Move the knight
                sourcePiece->setPieceId(12);
                sourcePiece->getSprite().setTexture(emptyTexture);
                movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
                whiteTurn = false;
            }
        }
        else if (sourcePiece->getPieceId() == 6) { // If the piece is a white rook
            if (checkIfValidRookMove(sPieceI, sPieceJ, mPieceI, mPieceJ)) {
                *movePiece = *sourcePiece; // Move the rook
                sourcePiece->setPieceId(12);
                sourcePiece->getSprite().setTexture(emptyTexture);
                movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
                whiteTurn = false;
            }
        }
        else if ((sourcePiece->getPieceId() == 4) || (sourcePiece->getPieceId() == 8) || (sourcePiece->getPieceId() == 10)) {
            *movePiece = *sourcePiece;
            sourcePiece->setPieceId(12);
            sourcePiece->getSprite().setTexture(emptyTexture);
            movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
            whiteTurn = false;
        }
    }
    // If it is black's turn
    else {
        if (sourcePiece->getPieceId() == 1) { // If the piece is a black pawn
            if (checkIfValidPawnMove(sPieceI, sPieceJ, mPieceI, mPieceJ)) { // If the pawn's move is valid
                *movePiece = *sourcePiece; // Move the pawn
                sourcePiece->setPieceId(12);
                sourcePiece->getSprite().setTexture(emptyTexture);
                movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
                whiteTurn = true; // Flip whiteTurn here
            }
        }

        else if (sourcePiece->getPieceId() == 3) {// If the piece is a black knight
            if (checkIfValidKnightMove(sPieceI, sPieceJ, mPieceI, mPieceJ)) {
                *movePiece = *sourcePiece; // Move the knight
                sourcePiece->setPieceId(12);
                sourcePiece->getSprite().setTexture(emptyTexture);
                movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
                whiteTurn = true;
            }
        }

        else if (sourcePiece->getPieceId() == 7) { // If the piece is a black rook
            if (checkIfValidRookMove(sPieceI, sPieceJ, mPieceI, mPieceJ)) {
                *movePiece = *sourcePiece; // Move the rook
                sourcePiece->setPieceId(12);
                sourcePiece->getSprite().setTexture(emptyTexture);
                movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
                whiteTurn = true;
            }
        }

        else if ((sourcePiece->getPieceId() == 5) || (sourcePiece->getPieceId() == 9) || (sourcePiece->getPieceId() == 11)) {
            *movePiece = *sourcePiece;
            sourcePiece->setPieceId(12);
            sourcePiece->getSprite().setTexture(emptyTexture);
            movePiece->getSprite().setPosition(mPieceJ * 64.f + 2.f, mPieceI * 64.f + 2.f);
            whiteTurn = true;
        }
    }
}

bool PieceMap::getTurnColor() {
    return whiteTurn;
}

bool PieceMap::checkIfValidPawnMove(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ) { // Implements tile by tile and double movement at start
    Piece* sourcePiece = getPieceFromMap(sPieceI, sPieceJ);
    Piece* movePiece = getPieceFromMap(mPieceI, mPieceJ);
    std::cout << "Checking for valid pawn move on piece type " << movePiece->getPieceType() <<std::endl;
    if (sourcePiece->isFirstMove()) {
        std::cout << "It is the first move.\n";
    }
    else {
        std::cout << "It is not the first move.\n";
    }
    std::cout << sourcePiece->getPieceType() << std::endl;
    if (sourcePiece->getPieceId() == 0 && movePiece->getPieceId() != 0) { // If piece is white pawn
        if ((movePiece->getPieceType() == 0) && ((mPieceI == sPieceI - 1) && (mPieceJ == sPieceJ))) {
            sourcePiece->setMoved();
            std::cout << "One step attempt" << std::endl;
            return true;
        } // If desired destination of diagonal to black piece is valid...
        if ((sourcePiece->isFirstMove()) && (mPieceI == sPieceI - 2) && (mPieceJ == sPieceJ) && getPieceFromMap(sPieceI - 1, sPieceJ)->getPieceType() == 0) {
            sourcePiece->setMoved();
            std::cout << "Two step attempt" << std::endl;
            return true;
        }
        if ((movePiece->getPieceType() == 2) && (mPieceI == sPieceI - 1) && ((mPieceJ == sPieceJ - 1) || (mPieceJ == sPieceJ + 1))) {
            std::cout << "Diagonal attempt" << std::endl;
            sourcePiece->setMoved();
            return true;
        } // If desired destination is two steps forward...
        else {
            return false;
        }
    }
    else if (sourcePiece->getPieceId() == 1 && movePiece->getPieceId() != 1) { // If piece is black pawn
        if ((movePiece->getPieceType() == 0) && ((mPieceI == sPieceI + 1) && (mPieceJ == sPieceJ))) {
            sourcePiece->setMoved();
            std::cout << "One step attempt" << std::endl;
            return true;
        } // If desired destination of diagonal to black piece is valid...
        if ((sourcePiece->isFirstMove()) && (mPieceI == sPieceI + 2) && (mPieceJ == sPieceJ) && getPieceFromMap(sPieceI + 1, sPieceJ)->getPieceType() == 0) {
            sourcePiece->setMoved();
            std::cout << "Two step attempt" << std::endl;
            return true;
        }
        if ((movePiece->getPieceType() == 1) && (mPieceI == sPieceI + 1) && ((mPieceJ == sPieceJ - 1) || (mPieceJ == sPieceJ + 1))) {
            std::cout << "Diagonal attempt" << std::endl;
            sourcePiece->setMoved();
            return true;
        } // If desired destination is two steps forward...
        else {
            return false;
        }
    }
}

bool PieceMap::checkIfValidKnightMove(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ) {
    Piece* sourcePiece = getPieceFromMap(sPieceI, sPieceJ);
    Piece* movePiece = getPieceFromMap(mPieceI, mPieceJ);
    std::cout << "Checking for valid knight move on piece type " << movePiece->getPieceType() << std::endl;
    int deltaI = mPieceI - sPieceI;
    int deltaJ = mPieceJ - sPieceJ;
    if ((movePiece->getPieceType() != sourcePiece->getPieceType()) && ((abs(deltaI) == 2 && abs(deltaJ) == 1) || (abs(deltaI) == 1 && abs(deltaJ) == 2))) {
        return true;
    }
    else {
        return false;
    }
}

bool PieceMap::checkIfValidRookMove(int sPieceI, int sPieceJ, int mPieceI, int mPieceJ) {
    Piece* sourcePiece = getPieceFromMap(sPieceI, sPieceJ);
    Piece* movePiece = getPieceFromMap(mPieceI, mPieceJ);
    std::cout << "Checking for valid rook move on piece type " << movePiece->getPieceType() << std::endl;

    // Make sure rook is moving in a straight line
    if ((sPieceI != mPieceI) && (sPieceJ != mPieceJ)) {
        return false;
    }

    // Make sure rook is not jumping over any pieces
    int deltaI = mPieceI - sPieceI;
    int deltaJ = mPieceJ - sPieceJ;

    if (deltaI != 0) {
        deltaI = deltaI > 0 ? 1 : -1;
        for (int i = sPieceI + deltaI; i != mPieceI; i += deltaI) {
            if (getPieceFromMap(i, sPieceJ)->getPieceType() != 0) {
                return false;
            }
        }
    }
    else {
        deltaJ = deltaJ > 0 ? 1 : -1;
        for (int j = sPieceJ + deltaJ; j != mPieceJ; j += deltaJ) {
            if (getPieceFromMap(sPieceI, j)->getPieceType() != 0) {
                return false;
            }
        }
    }
    return true;
}



void PieceMap::printMap() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << getPieceFromMap(i, j)->getPieceId() << " ";
        }
        std::cout << std::endl;
    }
}
