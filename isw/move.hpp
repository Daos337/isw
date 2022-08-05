#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

Event event;
{
if (Keyboard::isKeyPressed(Keyboard::A))
{
	CurrentFrame += 0.005 * time;
	if (CurrentFrame > 5) CurrentFrame -= 4;
	herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)) + 16, 0, -16, 30));
	herosprite.move(-0.1 * time, 0);

}

if (Keyboard::isKeyPressed(Keyboard::D))
{
	CurrentFrame += 0.005 * time;
	if (CurrentFrame > 5) CurrentFrame -= 4;
	herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30));
	herosprite.move(0.1 * time, 0);

}

if (Keyboard::isKeyPressed(Keyboard::W))
{
	CurrentFrame += 0.005 * time;
	if (CurrentFrame > 5) CurrentFrame -= 4;
	herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30));
	herosprite.move(0, -0.1 * time);
}

if (Keyboard::isKeyPressed(Keyboard::S))
{
	CurrentFrame += 0.005 * time;
	if (CurrentFrame > 5) CurrentFrame -= 4;
	herosprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30));
	herosprite.move(0, 0.1 * time);
}
}