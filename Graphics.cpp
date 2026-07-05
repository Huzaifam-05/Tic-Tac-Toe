#include "Graphics.h"
#include <stdexcept>

Graphics::Graphics(): window(sf::VideoMode(1280, 720), "Tic Tac Toe")
{
	loadTextures();
	window.setMouseCursorVisible(false);
	state = State::Menu;
}

void Graphics::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Graphics::processEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		switch (state)
		{
		case State::Menu:
			menuEvents(event);
			break;

		case State::Playing:
			gameEvents(event);
			break;

		case State::Result:
			resultEvents(event);
			break;
		}
	}
}

void Graphics::menuEvents(sf::Event& event)
{
	if (event.type != sf::Event::MouseButtonPressed)
		return;

	if (event.mouseButton.button != sf::Mouse::Left)
		return;

	sf::Vector2f mouse(event.mouseButton.x,event.mouseButton.y);

	if (pvpSprite.getGlobalBounds().contains(mouse))
	{
		game.reset(false);
		state = State::Playing;
	}
	if (pvaiSprite.getGlobalBounds().contains(mouse))
	{
		game.reset(true);
		state = State::Playing;
	}
}

void Graphics::gameEvents(sf::Event& event)
{
	if (event.type != sf::Event::MouseButtonPressed)
		return;

	if (event.mouseButton.button != sf::Mouse::Left)
		return;

	int row = getRow(event.mouseButton.y);
	int col = getCol(event.mouseButton.x);

	if (row != -1 && col != -1)
	{
		game.makeMove(row, col);
	}
}

void Graphics::resultEvents(sf::Event& event)
{
	if (event.type != sf::Event::MouseButtonPressed)
		return;

	if (event.mouseButton.button != sf::Mouse::Left)
		return;

	sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),static_cast<float>(event.mouseButton.y));

	if (replaySprite.getGlobalBounds().contains(mouse))
	{
		game.reset(game.getMode());
		state = State::Playing;
	}

	if (homeSprite.getGlobalBounds().contains(mouse))
	{
		state = State::Menu;
	}
}

void Graphics::update()
{
	if (state == State::Playing)
	{
		if (game.getGameOver())
		{
			state = State::Result;
		}
	}
}

void Graphics::render()
{
	window.clear();

	switch (state)
	{
	case State::Menu:
		drawMenu();
		break;

	case State::Playing:
		drawGame();
		break;

	case State::Result:
		drawResult();
		break;
	}

	window.display();
}

void Graphics::loadTextures()
{
	//Image Loading
	if (!backgroundTexture.loadFromFile("Assets/Background.png"))
	{
		throw std::runtime_error("Failed to load Background.png");
	}

	if (!boardTexture.loadFromFile("Assets/Game Board.png"))
	{
		throw std::runtime_error("Failed to load Game Board.png");
	}

	if (!xTexture.loadFromFile("Assets/X Normal.png"))
	{
		throw std::runtime_error("Failed to load X Normal.png");
	}

	if (!oTexture.loadFromFile("Assets/O Normal.png"))
	{
		throw std::runtime_error("Failed to load O Normal.png");
	}
	if (!titleTexture.loadFromFile("Assets/Title.png"))
	{
		throw std::runtime_error("Failed to load Title.png");
	}

	if (!pvpTexture.loadFromFile("Assets/Human vs Human.png"))
	{
		throw std::runtime_error("Failed to load Player vs Player Button.png");
	}

	if (!pvaiTexture.loadFromFile("Assets/Human vs Computer.png"))
	{
		throw std::runtime_error("Failed to load Player vs Computer Button.png");
	}
	if (!xActiveTexture.loadFromFile("Assets/Player X Active.png"))
	{
		throw std::runtime_error("Failed to load X Active.png");
	}

	if (!xInactiveTexture.loadFromFile("Assets/Player X Inactive.png"))
	{
		throw std::runtime_error("Failed to load X Inactive.png");
	}

	if (!oActiveTexture.loadFromFile("Assets/Player O Active.png"))
	{
		throw std::runtime_error("Failed to load O Active.png");
	}

	if (!oInactiveTexture.loadFromFile("Assets/Player O Inactive.png"))
	{
		throw std::runtime_error("Failed to load O Inactive.png");
	}

	if (!winnerXTexture.loadFromFile("Assets/Winner X.png"))
	{
		throw std::runtime_error("Failed to load Winner X.png");
	}

	if (!winnerOTexture.loadFromFile("Assets/Winner O.png"))
	{
		throw std::runtime_error("Failed to load Winner O.png");
	}

	if (!drawTexture.loadFromFile("Assets/Draw.png"))
	{
		throw std::runtime_error("Failed to load Draw.png");
	}

	if (!replayTexture.loadFromFile("Assets/Replay Button.png"))
	{
		throw std::runtime_error("Failed to load Replay Button.png");
	}

	if (!homeTexture.loadFromFile("Assets/Home Button.png"))
	{
		throw std::runtime_error("Failed to load Home Button.png");
	}

	if (!xWinTexture.loadFromFile("Assets/X Win.png"))
	{
		throw std::runtime_error("Failed to load X Win.png");
	}

	if (!oWinTexture.loadFromFile("Assets/O Win.png"))
	{
		throw std::runtime_error("Failed to load O Win.png");
	}

	if (!cursorTexture.loadFromFile("Assets/Cursor Hover.png"))
	{
		throw std::runtime_error("Failed to load Cursor Hover.png");
	}


	//set Texture
	backgroundSprite.setTexture(backgroundTexture);
	boardSprite.setTexture(boardTexture);
	xSprite.setTexture(xTexture);
	oSprite.setTexture(oTexture);
	titleSprite.setTexture(titleTexture);
	pvpSprite.setTexture(pvpTexture);
	pvaiSprite.setTexture(pvaiTexture);
	xActiveSprite.setTexture(xActiveTexture);
	xInactiveSprite.setTexture(xInactiveTexture);
	oActiveSprite.setTexture(oActiveTexture);
	oInactiveSprite.setTexture(oInactiveTexture);
	winnerXSprite.setTexture(winnerXTexture);
	winnerOSprite.setTexture(winnerOTexture);
	drawSprite.setTexture(drawTexture);
	replaySprite.setTexture(replayTexture);
	homeSprite.setTexture(homeTexture);
	xWinSprite.setTexture(xWinTexture);
	oWinSprite.setTexture(oWinTexture);
	cursorSprite.setTexture(cursorTexture);

	backgroundSprite.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,static_cast<float>(window.getSize().y) /backgroundTexture.getSize().y);

	sf::FloatRect xBounds = xSprite.getLocalBounds();
	xSprite.setOrigin(xBounds.width / 2.f,xBounds.height / 2.f);
	sf::FloatRect oBounds = oSprite.getLocalBounds();
	oSprite.setOrigin(oBounds.width / 2.f,oBounds.height / 2.f);
	sf::FloatRect boardBounds = boardSprite.getLocalBounds();
	sf::FloatRect bounds;

	bounds = titleSprite.getLocalBounds();
	titleSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = pvpSprite.getLocalBounds();
	pvpSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = pvaiSprite.getLocalBounds();
	pvaiSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = xActiveSprite.getLocalBounds();
	xActiveSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = xInactiveSprite.getLocalBounds();
	xInactiveSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = oActiveSprite.getLocalBounds();
	oActiveSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = oInactiveSprite.getLocalBounds();
	oInactiveSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = winnerXSprite.getLocalBounds();
	winnerXSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = winnerOSprite.getLocalBounds();
	winnerOSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = drawSprite.getLocalBounds();
	drawSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	float cx = window.getSize().x / 2.f;
	float cy = window.getSize().y / 2.f;

	winnerXSprite.setPosition(cx, cy);
	winnerOSprite.setPosition(cx, cy);
	drawSprite.setPosition(cx, cy);

	bounds = replaySprite.getLocalBounds();
	replaySprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = homeSprite.getLocalBounds();
	homeSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	sf::FloatRect winBounds;

	winBounds = xWinSprite.getLocalBounds();
	xWinSprite.setOrigin(
		winBounds.width / 2.f,
		winBounds.height / 2.f
	);

	winBounds = oWinSprite.getLocalBounds();
	oWinSprite.setOrigin(
		winBounds.width / 2.f,
		winBounds.height / 2.f
	);
	sf::FloatRect cursorBounds = cursorSprite.getLocalBounds();

	cursorSprite.setOrigin(
		cursorBounds.width / 2.f,
		cursorBounds.height / 2.f
	);

	titleSprite.setPosition(640.f, 140.f);
	pvpSprite.setPosition(640.f, 340.f);
	pvaiSprite.setPosition(640.f, 480.f);
	xActiveSprite.setPosition(520.f, 80.f);
	xInactiveSprite.setPosition(520.f, 80.f);

	oActiveSprite.setPosition(760.f, 80.f);
	oInactiveSprite.setPosition(760.f, 80.f);


	float zx = window.getSize().x / 2.f;
	float zy = window.getSize().y / 2.f;

	replaySprite.setPosition(zx - 70.f, zy + 30.f);
	homeSprite.setPosition(zx + 70.f, zy + 30.f);
	boardSprite.setOrigin(
		boardBounds.width / 2.f,
		boardBounds.height / 2.f
	);

	boardSprite.setPosition(
		window.getSize().x / 2.f,
		window.getSize().y / 2.f
	);

	float boardLeft = boardSprite.getPosition().x - boardBounds.width / 2.f;
	float boardTop = boardSprite.getPosition().y - boardBounds.height / 2.f;

	float cellSize = boardBounds.width / 3.f;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			cellCenter[r][c].x = boardLeft + c * cellSize + cellSize / 2.f;
			cellCenter[r][c].y = boardTop + r * cellSize + cellSize / 2.f;
		}
	}
}

int Graphics::getRow(float mouseY)
{
	float boardTop = boardSprite.getPosition().y - boardTexture.getSize().y / 2.f;

	if (mouseY < boardTop || mouseY > boardTop + boardTexture.getSize().y)
		return -1;

	return static_cast<int>((mouseY - boardTop) / (boardTexture.getSize().y / 3.f));
}

int Graphics::getCol(float mouseX)
{
	float boardLeft = boardSprite.getPosition().x - boardTexture.getSize().x / 2.f;

	if (mouseX < boardLeft || mouseX > boardLeft + boardTexture.getSize().x)
		return -1;

	return static_cast<int>((mouseX - boardLeft) / (boardTexture.getSize().x / 3.f));
}

void Graphics::drawMenu()
{
	window.draw(backgroundSprite);

	window.draw(titleSprite);

	window.draw(pvpSprite);

	window.draw(pvaiSprite);

	sf::Vector2i mouse = sf::Mouse::getPosition(window);

	cursorSprite.setPosition(
		static_cast<float>(mouse.x),
		static_cast<float>(mouse.y)
	);

	window.draw(cursorSprite);
}

void Graphics::drawGame()
{
	window.draw(backgroundSprite);

	window.draw(boardSprite);
	if (game.getPlayer() == 'X')
	{
		window.draw(xActiveSprite);
		window.draw(oInactiveSprite);
	}
	else
	{
		window.draw(xInactiveSprite);
		window.draw(oActiveSprite);
	}

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			char cell = game.getCell(r, c);

			if (cell == 'X')
			{
				if (game.isWinningCell(r, c))
				{
					xWinSprite.setPosition(cellCenter[r][c]);
					window.draw(xWinSprite);
				}
				else
				{
					xSprite.setPosition(cellCenter[r][c]);
					window.draw(xSprite);
				}
			}
			else if (cell == 'O')
			{
				if (game.isWinningCell(r, c))
				{
					oWinSprite.setPosition(cellCenter[r][c]);
					window.draw(oWinSprite);
				}
				else
				{
					oSprite.setPosition(cellCenter[r][c]);
					window.draw(oSprite);
				}
			}
		}
	}
	sf::Vector2i mouse = sf::Mouse::getPosition(window);

	cursorSprite.setPosition(
		static_cast<float>(mouse.x),
		static_cast<float>(mouse.y)
	);

	window.draw(cursorSprite);
}

void Graphics::drawResult()
{
	window.draw(backgroundSprite);

	if (game.getWinner() == 'X')
		window.draw(winnerXSprite);
	else if (game.getWinner() == 'O')
		window.draw(winnerOSprite);
	else
		window.draw(drawSprite);

	window.draw(replaySprite);
	window.draw(homeSprite);

	sf::Vector2i mouse = sf::Mouse::getPosition(window);

	cursorSprite.setPosition(
		static_cast<float>(mouse.x),
		static_cast<float>(mouse.y));

	window.draw(cursorSprite);
}