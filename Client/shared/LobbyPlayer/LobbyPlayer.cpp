/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-20T21:13:21+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-16T11:40:59+01:00
 */


#include "LobbyPlayer.hpp"

LobbyPlayer::LobbyPlayer(ResourcesManager &resourceManager, GUI::Manager& guiManager, EventManager::Manager &eventManager)
	: _name("LobbyPlayer"),
	_guiManager(guiManager),
	_eventManager(eventManager),
	_resources(resourceManager),
	_players(0)
{

}

void	LobbyPlayer::playerJoin(const std::string &name)
{
	_players++;

	sf::Texture &playerSlot = _resources.getContent<Texture>("window_bottom");
	sf::Texture &playersSpaceships = _resources.getContent<Texture>("playersSpaceships");
	sf::Texture &readyLobbyTexture = _resources.getContent<Texture>("readyButtonState");
	sf::Font &font = _resources.getContent<Font>("neuropol");

	sf::Sprite centerSlotSprite(_resources.getContent<Texture>("window_bottom"));
	centerSlotSprite.setScale(0.25, 0.25);

	sf::Vector2f centerSlot((_guiManager.getWindowSize().x / 2) - (centerSlotSprite.getGlobalBounds().width / 2), (_guiManager.getWindowSize().y / 2) - (centerSlotSprite.getGlobalBounds().height / 2));

	float slotPlayerX = _players == 1 || _players == 3 ? 450 : 1070;
	float slotPlayerY = _players < 3 ? -290 : 50;

	_guiManager.addElement<GUI::Image>("spaceshipPlayer" + name + "Sprite", sf::Vector2f(centerSlot.x, centerSlot.y), playersSpaceships, sf::IntRect(160 * (_players - 1), 0, 160, 160), sf::Vector2f(0.9, 0.9));
	_guiManager.addElement<GUI::Image>("slotPlayer" + name + "Sprite", sf::Vector2f(slotPlayerX, (_guiManager.getWindowSize().y / 2) + slotPlayerY), playerSlot, sf::Vector2f(0.25, 0.25));
	_guiManager.addElement<GUI::Image>("readyButton" + name + "Sprite", sf::Vector2f(0, 0), readyLobbyTexture, sf::IntRect(0, 0, 76, 76), sf::Vector2f(0.5, 0.5));
	_guiManager.addElement<GUI::Image>("readyButtonState" + name + "Sprite", sf::Vector2f(0, 0), readyLobbyTexture, sf::IntRect(152, 0, 76, 76), sf::Vector2f(0.5, 0.5));
	_guiManager.addElement<GUI::Text>("player" + name + "Name", sf::Vector2f(centerSlot.x, centerSlot.y), name, font, 30);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Text>("slotPlayer" + name + "Sprite", "player" + name + "Name", 15, -15);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Image>("slotPlayer" + name + "Sprite", "readyButton" + name + "Sprite", -220, 0);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Image>("slotPlayer" + name + "Sprite", "readyButtonState" + name + "Sprite", -220, 0);
	_guiManager.centerElementWithAnOther<GUI::Image, GUI::Image>("slotPlayer" + name + "Sprite", "spaceshipPlayer" + name + "Sprite", 15, 150);

}

void	LobbyPlayer::playerLeave(const std::string &name)
{
	_players--;

	_guiManager.release("spaceshipPlayer" + name + "Sprite");
	_guiManager.release("slotPlayer" + name + "Sprite");
	_guiManager.release("readyButton" + name + "Sprite");
	_guiManager.release("readyButtonState" + name + "Sprite");
	_guiManager.release("player" + name + "Name");
}

void	LobbyPlayer::onEnter()
{
	_players = 0;
	_resources.load<Texture>("lobbiesBackground", "../../Client/media/img/lobbiesBackground.jpg");
	_resources.load<Texture>("window_whole", "../../Client/media/img/playerLobby/window_whole.png");
	_resources.load<Texture>("window_bottom", "../../Client/media/img/playerLobby/window_bottom.png");
	_resources.load<Texture>("playersSpaceships", "../../Client/media/img/ship/allies/playersSpaceships.png");
	_resources.load<Texture>("exitButton", "../../Client/media/img/playerLobby/exitButton.png");
	_resources.load<Texture>("readyButtonState", "../../Client/media/img/playerLobby/readyButtonState.png");
	_resources.load<Texture>("readyButton", "../../Client/media/img/playerLobby/readyButton.png");
	_resources.load<Font>("neuropol", "../../Client/media/font/neuropol.ttf");


	_eventManager.listen<void, const std::string &>("PlayerJoinEvent", [&](const std::string &name){this->playerJoin(name);});
	_eventManager.listen<void>("exitLobbyEvent", [&](){this->closeLobby();});

	sf::Font &font = _resources.getContent<Font>("neuropol");
	sf::Texture &waitingTexture = _resources.getContent<Texture>("window_whole");
	sf::Texture &exitLobbyTexture = _resources.getContent<Texture>("exitButton");
	sf::Texture &readyButtonLobbyTexture = _resources.getContent<Texture>("readyButton");

	sf::Sprite waitingSprite(waitingTexture);
	waitingSprite.setScale(1, 0.7);
	sf::Sprite centerSlotSprite(_resources.getContent<Texture>("window_bottom"));
	centerSlotSprite.setScale(0.25, 0.25);
	sf::Sprite exitLobbySprite(exitLobbyTexture);
	exitLobbySprite.setScale(0.7, 0.7);
	sf::Sprite readyToPlaySprite(readyButtonLobbyTexture);

	sf::Vector2f center((_guiManager.getWindowSize().x / 2) - (waitingSprite.getGlobalBounds().width / 2), (_guiManager.getWindowSize().y / 2) - (waitingSprite.getGlobalBounds().height / 2));
	sf::Vector2f centerSlot((_guiManager.getWindowSize().x / 2) - (centerSlotSprite.getGlobalBounds().width / 2), (_guiManager.getWindowSize().y / 2) - (centerSlotSprite.getGlobalBounds().height / 2));

	_guiManager.addElement<GUI::Image>("Background", sf::Vector2f(0, 0), _resources.getContent<Texture>("lobbiesBackground"), sf::Vector2f(1,1));
	_guiManager.addElement<GUI::Image>("lobbyTitleSprite", sf::Vector2f(center.x, 0), waitingTexture, sf::Vector2f(1, 0.7));
	_guiManager.addElement<GUI::Text>("lobbyTitle", sf::Vector2f(780, 120), "Waiting for players...", font, 30);

	_guiManager.addElement<GUI::Button>("readyToPlayButton", _eventManager, "readyToPlayEvent", sf::Vector2f(centerSlot.x + 80, 1000), readyToPlaySprite, readyToPlaySprite);
	_guiManager.addElement<GUI::Text>("readyButtonText", sf::Vector2f(centerSlot.x, centerSlot.y), "Ready ?", font, 30);
	_guiManager.centerElementWithAnOther<GUI::Button, GUI::Text>("readyToPlayButton", "readyButtonText", 0, -5);

	_guiManager.addElement<GUI::Button>("exitLobbyButton", _eventManager, "exitLobbyEvent", sf::Vector2f(10, 950), exitLobbySprite, exitLobbySprite);
}

void	LobbyPlayer::onExit()
{
	_resources.release("lobbiesBackground");
	_resources.release("window_whole");
	_resources.release("window_bottom");
	_resources.release("playersSpaceships");
	_resources.release("exitButton");
	_resources.release("readyButtonState");
	_resources.release("readyButton");
	_resources.release("neuropol");
	_guiManager.releaseAll();
}

void LobbyPlayer::closeLobby()
{
	_eventManager.fire<void, std::string const &>("changeScene", "StartPage");
}

void	LobbyPlayer::update(const float time, ECS::Manager &ecs, EventManager::Manager &event)
{
	(void)time;
	(void)ecs;
	(void)event;
}
