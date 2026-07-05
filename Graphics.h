#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

enum class State
{
    Menu,
    Playing,
    Result
};

class Graphics
{
private:
    State state;
    sf::RenderWindow window;
    sf::Vector2f cellCenter[3][3];
    Game game;

    sf::Texture backgroundTexture;
    sf::Texture boardTexture;
    sf::Texture xTexture;
    sf::Texture oTexture;
    sf::Texture xWinTexture;
    sf::Texture oWinTexture;
    sf::Texture titleTexture;
    sf::Texture pvpTexture;
    sf::Texture pvaiTexture;
    sf::Texture xActiveTexture;
    sf::Texture xInactiveTexture;
    sf::Texture oActiveTexture;
    sf::Texture oInactiveTexture;
    sf::Texture winnerXTexture;
    sf::Texture winnerOTexture;
    sf::Texture drawTexture;
    sf::Texture replayTexture;
    sf::Texture homeTexture;
    sf::Texture cursorTexture;

    sf::Sprite backgroundSprite;
    sf::Sprite boardSprite;
    sf::Sprite xSprite;
    sf::Sprite oSprite;
    sf::Sprite titleSprite;
    sf::Sprite pvpSprite;
    sf::Sprite pvaiSprite;
    sf::Sprite xActiveSprite;
    sf::Sprite xInactiveSprite;
    sf::Sprite oActiveSprite;
    sf::Sprite oInactiveSprite;
    sf::Sprite winnerXSprite;
    sf::Sprite winnerOSprite;
    sf::Sprite drawSprite;
    sf::Sprite replaySprite;
    sf::Sprite homeSprite;
    sf::Sprite xWinSprite;
    sf::Sprite oWinSprite;
    sf::Sprite cursorSprite;

public:

    Graphics();
    void run();
    void processEvents();
    void update();
    void render();
    void loadTextures();
    void drawMenu();
    void drawGame();
    void drawResult();
    void menuEvents(sf::Event& event);
    void gameEvents(sf::Event& event);
    void resultEvents(sf::Event& event);
    int getRow(float mouseY);
    int getCol(float mouseX);
};