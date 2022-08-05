#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "ISW");

	Texture herotexture;
	herotexture.loadFromFile("images/knight_m.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(50, 0, 16, 30));
	herosprite.setPosition(300, 200);

	float CurrentFrame = 0;
	Clock clock;	
	int x = 1;
	while (window.isOpen()) 
	{
		double time = clock.getElapsedTime().asMicroseconds();
		clock.restart(); 
		time = time / 800;

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Event::KeyReleased)
			{
				if (x == 0)
					herosprite.setTextureRect(IntRect(50 + 16, 0, -16, 30));
				if (x == 1)
					herosprite.setTextureRect(IntRect(50, 0, 16, 30));
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{ 
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame))+16, 0, -16, 30));
			herosprite.move(-0.1 * time, 0);
			x = 0;
		} 

		if (Keyboard::isKeyPressed(Keyboard::D)) 
		{
			CurrentFrame += 0.005 * time; 
			if (CurrentFrame > 5) CurrentFrame -= 4; 
			herosprite.setTextureRect(IntRect(50 +(16 * int(CurrentFrame)), 0, 16, 30)); 
			herosprite.move(0.1*time, 0);
			x = 1;
		} 

		if (Keyboard::isKeyPressed(Keyboard::W)) 
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			if (Keyboard::isKeyPressed(Keyboard::A)) herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)) + 16, 0, -16, 30));
			else herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30));
			herosprite.move(0, -0.1*time); 
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) 
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			if (Keyboard::isKeyPressed(Keyboard::A)) herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)) + 16, 0, -16, 30));
			else herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30)); 
			herosprite.move(0, 0.1*time); 
		}
		

		window.clear();
		window.draw(herosprite);
		window.display();
	}
	return 0;
}