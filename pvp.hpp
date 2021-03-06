#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
namespace GameEngine{
	class pvp : public State{
	public:
		pvp(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void InitGridPieces();
		void checkAndPlacePiece();
		void checkPlayerHasWon(int turn);
		void Check3PiecesForMatch(int x1, int y1 , int x2, int y2 ,int x3, int y3 ,int pieceToCheck);
	private:
		
		GameDataRef _data;
		sf::Sprite _pauseButton;
		sf::Sprite gridSprite;
		sf::Sprite showCurrentPlayer;
		sf::Text turnText;
		sf::Sprite gridPieces[3][3];
		int gridArray[3][3];
        int turn;
        int gamestate; 
		sf::Sprite _retryButton;
		sf::Sprite _homeButton;
		int temp;
		sf::Clock timer;
	};
}