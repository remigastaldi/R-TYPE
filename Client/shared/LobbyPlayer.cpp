#include "LobbyPlayer.hpp"

LobbyPlayer::LobbyPlayer(GUI::Manager& guiManager, EventManager::Manager &eventManager)
	: _guiManager(guiManager),
	_eventManager(eventManager)
{

}

void	LobbyPlayer::onEnter()
{
	_resources.load<Texture>("../../Client/media/img/lobbiesBackground.jpg");
	_resources.load<Texture>("../../Client/media/img/playerLobby/window_whole.png");
	_resources.load<Texture>("../../Client/media/img/playerLobby/window_bottom.png");
	_resources.load<Texture>("../../Client/media/img/playerLobby/playersSpaceships.png");
	_resources.load<Font>("../../Client/media/font/neuropol.ttf");
	
	sf::Font &font = _resources.getContent<Font>("../../Client/media/font/neuropol.ttf");
	sf::Texture &waitingTexture = _resources.getContent<Texture>("../../Client/media/img/playerLobby/window_whole.png");
	sf::Texture &playerSlot = _resources.getContent<Texture>("../../Client/media/img/playerLobby/window_bottom.png");
	sf::Texture &playersSpaceships = _resources.getContent<Texture>("../../Client/media/img/playerLobby/playersSpaceships.png");

	sf::Sprite waitingSprite(waitingTexture);
	waitingSprite.setScale(1, 0.7);
	sf::Sprite centerSlotSprite(playerSlot);
	centerSlotSprite.setScale(0.25, 0.25);

	sf::Vector2f center((_guiManager.getWindowSize().x / 2) - (waitingSprite.getGlobalBounds().width / 2), (_guiManager.getWindowSize().y / 2) - (waitingSprite.getGlobalBounds().height / 2));
	sf::Vector2f centerSlot((_guiManager.getWindowSize().x / 2) - (centerSlotSprite.getGlobalBounds().width / 2), (_guiManager.getWindowSize().y / 2) - (centerSlotSprite.getGlobalBounds().height / 2));

	_guiManager.addElement<GUI::Image>("Background", sf::Vector2f(0, 0), _resources.getContent<Texture>("../../Client/media/img/lobbiesBackground.jpg"), sf::Vector2f(1,1));
	_guiManager.addElement<GUI::Image>("lobbyTitleSprite", sf::Vector2f(center.x, 0), waitingTexture, sf::Vector2f(1, 0.7));
	_guiManager.addElement<GUI::Text>("lobbyTitle", sf::Vector2f(780, 120), "Waiting for players...", font, 30);

	_guiManager.addElement<GUI::Image>("spaceshipPlayer1Sprite", sf::Vector2f(centerSlot.x, centerSlot.y), playersSpaceships, sf::IntRect(160, 0, 160, 160), sf::Vector2f(0.9, 0.9));
	_guiManager.addElement<GUI::Image>("slotPlayer1Sprite", sf::Vector2f(450, (_guiManager.getWindowSize().y / 2) - 290), playerSlot, sf::Vector2f(0.25, 0.25));
	_guiManager.addElement<GUI::Text>("player1Name", sf::Vector2f(centerSlot.x, centerSlot.y), "nomjoueur1", font, 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("slotPlayer1Sprite", "player1Name", 15, -15);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Image>("slotPlayer1Sprite", "spaceshipPlayer1Sprite", 15, 150);

	_guiManager.addElement<GUI::Image>("spaceshipPlayer2Sprite", sf::Vector2f(centerSlot.x, centerSlot.y), playersSpaceships, sf::IntRect(320, 0, 160, 160), sf::Vector2f(0.9, 0.9));
	_guiManager.addElement<GUI::Image>("slotPlayer2Sprite", sf::Vector2f(1070, (_guiManager.getWindowSize().y / 2) - 290), playerSlot, sf::Vector2f(0.25, 0.25));
	_guiManager.addElement<GUI::Text>("player2Name", sf::Vector2f(centerSlot.x, centerSlot.y), "nomjoueur2", font, 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("slotPlayer2Sprite", "player2Name", 15, -15);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Image>("slotPlayer2Sprite", "spaceshipPlayer2Sprite", 15, 150);

	_guiManager.addElement<GUI::Image>("spaceshipPlayer3Sprite", sf::Vector2f(centerSlot.x, centerSlot.y), playersSpaceships, sf::IntRect(0, 0, 160, 160), sf::Vector2f(0.9, 0.9));
	_guiManager.addElement<GUI::Image>("slotPlayer3Sprite", sf::Vector2f(450, (_guiManager.getWindowSize().y / 2) + 50), playerSlot, sf::Vector2f(0.25, 0.25));
	_guiManager.addElement<GUI::Text>("player3Name", sf::Vector2f(centerSlot.x, centerSlot.y), "nomjoueur3", font, 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("slotPlayer3Sprite", "player3Name", 15, -15);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Image>("slotPlayer3Sprite", "spaceshipPlayer3Sprite", 15, 150);

	_guiManager.addElement<GUI::Image>("spaceshipPlayer4Sprite", sf::Vector2f(centerSlot.x, centerSlot.y), playersSpaceships, sf::IntRect(480, 0, 160, 160), sf::Vector2f(0.9, 0.9));
	_guiManager.addElement<GUI::Image>("slotPlayer4Sprite", sf::Vector2f(1070, (_guiManager.getWindowSize().y / 2) + 50), playerSlot, sf::Vector2f(0.25, 0.25));
	_guiManager.addElement<GUI::Text>("player4Name", sf::Vector2f(centerSlot.x, centerSlot.y), "nomjoueur4", font, 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("slotPlayer4Sprite", "player4Name", 15, -15);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Image>("slotPlayer4Sprite", "spaceshipPlayer4Sprite", 15, 150);

}

void	LobbyPlayer::onExit()
{

}

void	LobbyPlayer::update(const float time, ECS::Manager &ecs, EventManager::Manager &event)
{
	(void)time;
	(void)ecs;
	(void)event;
}
