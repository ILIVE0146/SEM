

#include <sstream>
#include "unbeatableGameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "gameWonState.hpp"
#include "gameDrawState.hpp"
#include "unbeatableAI.hpp"
#include <iostream>

namespace GameEngine
{
	unbeatableGameState::unbeatableGameState(GameDataRef data) : _data(data)
	{

	}

	void unbeatableGameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->ai = new unbeatableAI(turn, this->_data);

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));
	
		InitGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridArray[x][y] = Empty_piece_number;
			}
		}
	}

	void unbeatableGameState::HandleInput() 
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				// Switch To Game State
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
			{
				if (STATE_PLAYING == gameState)
				{
					this->CheckAndPlacePiece();
				}
			}
		}
	}

	void unbeatableGameState::Update(float dt)
	{
		if (State_Draw == gameState || State_lose == gameState || State_won == gameState)
		{
			if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER)
			{
				if(gameState == State_lose){
					this->_data->machine.AddState(StateRef(new GameOverState(_data)), true);
				}else if(State_Draw == gameState){
					this->_data->machine.AddState(StateRef(new GameDrawState(_data)), true);
				}else{
					this->_data->machine.AddState(StateRef(new GameWonState(_data)), true);
				}
			}
		}
	}

	void unbeatableGameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(250,181,127));


		this->_data->window.draw( this->_pauseButton );

		this->_data->window.draw( this->_gridSprite );

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
		}

		this->_data->window.display();
	}

	void unbeatableGameState::InitGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void unbeatableGameState::CheckAndPlacePiece()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

		//std::cout << gridLocalTouchPos.x << ", " << gridLocalTouchPos.y << std::endl;

		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column, row;

		// Check which column the user has clicked
		if (gridLocalTouchPos.x < gridSectionSize.x) // First Column
		{
			column = 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2) // Second Column
		{
			column = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width) // Third Column
		{
			column = 3;
		}

		// Check which row the user has clicked
		if (gridLocalTouchPos.y < gridSectionSize.y) // First Row
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2) // Second Row
		{
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height) // Third Row
		{
			row = 3;
		}

		if (_gridArray[column - 1][row - 1] == Empty_piece_number)
		{
			_gridArray[column - 1][row - 1] = turn;

			if (PLAYER_PIECE == turn)
			{
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));

				this->CheckHasPlayerWon(turn);
			}

			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void unbeatableGameState::CheckHasPlayerWon(int player)
	{
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

		if (State_won != gameState)
		{
			gameState = State_AI_playing;

			ai->PlacePiece(&_gridArray, _gridPieces, &gameState);

			Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_piece);
			Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_piece);
			Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_piece);
			Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_piece);
			Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_piece);
			Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_piece);
			Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_piece);
			Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_piece);
		}

		int emptyNum = 9;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (Empty_piece_number != _gridArray[x][y])
				{
					emptyNum--;
				}
			}
		}

		// check if the game is a draw
		if (0 == emptyNum && (State_won != gameState) && (State_lose != gameState))
		{
			gameState = State_Draw;
		}

		// check if the game is over
		if (State_Draw == gameState || State_lose == gameState || State_won == gameState)
		{
			// show game over
			this->_clock.restart( );
		}

		std::cout << gameState << std::endl;
	}

	void unbeatableGameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
	{
		if (pieceToCheck == _gridArray[x1][y1] && pieceToCheck == _gridArray[x2][y2] && pieceToCheck == _gridArray[x3][y3])
		{
			std::string winningPieceStr;

			if (O_piece_number == pieceToCheck)
			{
				winningPieceStr = "O Winning Piece";
			}
			else
			{
				winningPieceStr = "X Winning Piece";
			}

			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));


			if (PLAYER_PIECE == pieceToCheck)
			{
				gameState = State_won;
			}
			else
			{
				gameState = State_lose;
			}
		}
	}
}