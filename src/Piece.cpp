#include "Piece.hpp"
#include <iostream>

Piece::Piece() {
	hasMoved = false;
	setPieceId(0);
}

Piece::Piece(int piece) {
	hasMoved = false;
	setPieceId(piece);
}

void Piece::setPieceId(int piece) {
	id = piece;
	setPieceType(id);
}

int Piece::getPieceId() {
	return id;
}

sf::Sprite& Piece::getSprite() {
	return pSprite;
}

const sf::Sprite& Piece::getSprite() const {
	return pSprite;
}

bool Piece::isFirstMove() {
	return !hasMoved;
}

void Piece::setMoved() {
	Piece::hasMoved = true;
}

void Piece::setPieceType(int t) {
	if (t == 12) {
		pieceType = 0;
	}
	else if (t == 0 || t == 2 || t == 4 || t == 6 || t == 8 || t == 10) {
		pieceType = 1;
	}
	else if (t == 1 || t == 3 || t == 5 || t == 7 || t == 9 || t == 11){
		pieceType = 2;
	}
}

int Piece::getPieceType() {
	return pieceType;
}
