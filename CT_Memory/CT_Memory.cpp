// CT_Memory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main(int argc, _TCHAR* argv[])
{
	Game::Start();

	//sf::RenderWindow window(sf::VideoMode(1280, 768), "SPACE to Flip!");

	//sf::Texture front;
	//front.loadFromFile("../data/front.png");

	//sf::Texture back;
	//back.loadFromFile("../data/back.png");

	//sf::Sprite cardFace(front);
	//cardFace.setOrigin(64, 95); // Move origin to center of card
	//cardFace.setPosition(640, 384); // Move card to center of window

	//sf::Sprite cardBack(back);
	//cardBack.setOrigin(64, 95); // Move origin to center of card
	//cardBack.setPosition(640, 384); // Move card to center of window
	//
	//
	//// Used to determine current status
	//bool frontShown = false;
	//char spindir = 0; // 0 -> don't spin, 1 -> show, -1 -> hide
	//sf::Time currentTime = sf::Time::Zero;


	//const sf::Time spinTime = sf::seconds(1);
	//const sf::Time halfSpinTime = spinTime / 2.f;
	//const float pi = std::acos(-1);

	//sf::Event event;
	//sf::Clock clock;
	//while (window.isOpen()) {
	//	while (window.pollEvent(event)) {
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !spindir) {
	//			if (frontShown)
	//				spindir = -1;
	//			else
	//				spindir = 1;
	//		}
	//	}
	//	window.clear(sf::Color(0, 127, 127));
	//	sf::Time delta = clock.restart();
	//	if (spindir == 1) {
	//		if (currentTime < spinTime - delta)
	//			currentTime += delta;
	//		else {
	//			currentTime = spinTime;
	//			spindir = 0;
	//		}
	//	}
	//	else if (spindir == -1) {
	//		if (currentTime > delta)
	//			currentTime -= delta;
	//		else {
	//			currentTime = sf::Time::Zero;
	//			spindir = 0;
	//		}
	//	}

	//	frontShown = currentTime >= spinTime / 2.f;

	//	if (frontShown) {
	//		// Just scale the sprite based on time:
	//		float scale = (currentTime - halfSpinTime) / halfSpinTime;

	//		// The upscaling is really optional
	//		cardFace.setScale(std::sin(scale * pi / 2), 1);
	//		window.draw(cardFace);
	//	}
	//	else {
	//		// Same here
	//		float scale = 1.f - currentTime / halfSpinTime;
	//		cardBack.setScale(std::sin(scale * pi / 2), 1);
	//		window.draw(cardBack);
	//	}

	//	window.display();
	//}

	return 0;
}

