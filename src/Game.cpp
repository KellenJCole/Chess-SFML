#include "Game.hpp"

Game::Game() : mWindow(sf::VideoMode(512, 512), "Chess") {
	mFirstClick = true;
	selectPieceI = -1;
	selectPieceJ = -1;
	movePieceI = -1;
	movePieceJ = -1;

	std::string imagePath = std::string(__FILE__);
	imagePath = imagePath.substr(0, imagePath.rfind('\\')) + "\\Media\\Textures\\Board.png";
	std::cout << imagePath << std::endl;
	if (!mBoardTexture.loadFromFile(imagePath))
		throw std::runtime_error("Board image not loaded successfully.");

	mBoard.setTexture(mBoardTexture);
	mBoard.setPosition(0.f, 0.f);
	board.printMap();
}

void Game::run() {
	while (mWindow.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::selectPiece(sf::Vector2i mp) {
	selectPieceJ = mp.x / 64;
	selectPieceI = mp.y / 64;
	
	if (board.getTurnColor()) {
		if (board.getPieceFromMap(selectPieceI, selectPieceJ)->getPieceType() != 1 && board.getPieceFromMap(selectPieceI, selectPieceJ)->getPieceType() != 0) {
			mFirstClick = true;
		}
	}
	else {
		if (board.getPieceFromMap(selectPieceI, selectPieceJ)->getPieceType() != 2 && board.getPieceFromMap(selectPieceI, selectPieceJ)->getPieceType() != 0) {
			mFirstClick = true;
		}
	}
}


void Game::movePiece(sf::Vector2i mp) {

	movePieceJ = mp.x / 64;
	movePieceI = mp.y / 64;
	std::cout << "Destination selected: " << board.getPieceFromMap(movePieceI, movePieceJ)->getPieceType() << std::endl;
	std::cout << "Destination coords: " << movePieceI << ", " << movePieceJ << std::endl;

	if (board.getPieceFromMap(movePieceI, movePieceJ)->getPieceType() == board.getPieceFromMap(selectPieceI, selectPieceJ)->getPieceType()) {
		std::cout << "Destination is same color as origin\n";
		mFirstClick = true;
		mPieceMoved = false;
	}
	else {
		mPieceMoved = true;
	}
}

void Game::processEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			mWindow.close();
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
			if (mFirstClick) {
				// Call first function with mouse position
				selectPiece(mousePos);
				mFirstClick = false;
			}
			else {
				// Call second function with mouse position
				movePiece(mousePos);
				mFirstClick = true;
			}
		}
	}
}

void Game::update() {

	if (mPieceMoved) {
		board.printMap();
		board.updatePiecePosition(selectPieceI, selectPieceJ, movePieceI, movePieceJ);
		mPieceMoved = false;
	}
}

void Game::render() {
	mWindow.clear();
	mWindow.draw(mBoard);

	// Draw each piece sprite on the board
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			mWindow.draw(board.getPieceFromMap(y, x)->getSprite());
		}
	}
	mWindow.display();
}
