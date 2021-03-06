#include <sstream>
#include "playOptionState.hpp"
#include "DEFINITIONS.hpp"

#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "pvp.hpp"
#include "unbeatable.hpp"
namespace GameEngine{
	PlayOptionState::PlayOptionState(GameDataRef data) : _data(data){ }
	void PlayOptionState::Init(){
		/*
			For loading data
		*/
    //For title
    this->tytle.setFont(this->_data->assets.GetFont("Felt"));
    this->tytle.setPosition(20,50);
    this->tytle.setFillColor(sf::Color(245,170,66));
    this->tytle.setScale(2,2);
    this->tytle.setString("CHOOSE A GAME MODE");
    //For pvp button
        this->pvpButton.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->pvpText.setFont(this->_data->assets.GetFont("Felt"));
        this->pvpText.setString("      PVP      ");
        this->pvpButton.setPosition(200,300);
        this->pvpText.setPosition(this->pvpButton.getPosition().x + 45,this->pvpButton.getPosition().y + 5);
        //For Easy AI
        this->easyAI.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->easyAI_text.setFont(this->_data->assets.GetFont("Felt"));
        this->easyAI_text.setString("Easy AI");
        this->easyAI.setPosition(200,450);
        this->easyAI_text.setPosition(this->easyAI.getPosition().x + 70 ,this->easyAI.getPosition().y + 5);
        //for unbeatable AI
        this->unbeatable_mode.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->unbeatable_mode_text.setFont(this->_data->assets.GetFont("Felt"));
        this->unbeatable_mode_text.setString("Unbeatable AI");
        this->unbeatable_mode.setPosition(200,600);
        this->unbeatable_mode_text.setPosition(this->unbeatable_mode.getPosition().x + 20,this->unbeatable_mode.getPosition().y + 5);
        //FOr Back button
        this->back_button.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->back_button.setPosition(350,825);
        this->back_TXT.setFont(this->_data->assets.GetFont("Felt"));
        this->back_TXT.setString("BACK");
        this->back_TXT.setPosition(this->back_button.getPosition().x + 75,this->back_button.getPosition().y + 5);
    }
	void PlayOptionState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
            if(this->unbeatable_mode.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->unbeatable_mode.setScale(1.25,1.25);
			}
			else{
				this->unbeatable_mode.setScale(1,1);
			}
            if(this->easyAI.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->easyAI.setScale(1.25,1.25);
			}
			else{
				this->easyAI.setScale(1,1);
			}
            if(this->pvpButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->pvpButton.setScale(1.25,1.25);
			}
			else{
				this->pvpButton.setScale(1,1);
			}
            if(this->back_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->_data->window)))){
				this->back_button.setScale(1.25,1.25);
			}
			else{
				this->back_button.setScale(1,1);
			}
            if (this->_data->input.IsSpriteClicked(this->back_button, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
			}
            if (this->_data->input.IsSpriteClicked(this->easyAI, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(_data)),true);
			}
            if (this->_data->input.IsSpriteClicked(this->pvpButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new pvp(_data)),true);
			}
			if( this->_data->input.IsSpriteClicked(this->unbeatable_mode,sf::Mouse::Left,this->_data->window)){
				this->_data->machine.AddState(StateRef(new unbeatable(_data)),true);
			}
		}
	}
	void PlayOptionState::Update(float dt)
	{
		
	}
	void PlayOptionState::Draw(float dt)
	{
		if(this->_data->isdefaultTheme){
			this->_data->window.clear(sf::Color(this->_data->themeDefault->getMainMenuR(),this->_data->themeDefault->getMainMenuG(),this->_data->themeDefault->getMainMenuB()));
		}else{
			this->_data->window.clear(sf::Color(this->_data->themeNew->getMainMenuR(),this->_data->themeNew->getMainMenuG(),this->_data->themeNew->getMainMenuB()));
		}
        this->_data->window.draw(this->tytle);
        this->_data->window.draw(this->easyAI);
        this->_data->window.draw(this->easyAI_text);
        this->_data->window.draw(this->unbeatable_mode);
        this->_data->window.draw(this->unbeatable_mode_text);
        this->_data->window.draw(this->pvpButton);
        this->_data->window.draw(this->pvpText);
        this->_data->window.draw(this->back_button);
        this->_data->window.draw(this->back_TXT);
		this->_data->window.display();
	}
}