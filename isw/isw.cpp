#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;

class Player { // класс Игрока
public:
	float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 1; //направление (direction) движения игрока
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

	Player(String F, float X, float Y, float W, float H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(w, h, w, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
		sprite.setPosition(300, 200);
	}

};

int main()
{
	RenderWindow window(VideoMode(640, 480), "ISW");

	//Texture herotexture;
	//herotexture.loadFromFile("images/knight_m.png");
	//Sprite herosprite;
	//herosprite.setTexture(herotexture);
	//herosprite.setTextureRect(IntRect(50, 0, 16, 30));
	//herosprite.setPosition(300, 200);

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом	

	Player p("knight_m.png", 50, 0, 16, 30);

	float CurrentFrame = 0;
	Clock clock;	

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
				if (p.dir == 0)
					p.sprite.setTextureRect(IntRect(50 + 16, 0, -16, 30));
				if (p.dir == 1)
					p.sprite.setTextureRect(IntRect(50, 0, 16, 30)); 
			}
			
		}
		
		if (Keyboard::isKeyPressed(Keyboard::A))
		{ 
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame))+16, 0, -16, 30));
			p.sprite.move(-0.1 * time, 0);
			p.dir = 0;
		} 

		if (Keyboard::isKeyPressed(Keyboard::D)) 
		{
			CurrentFrame += 0.005 * time; 
			if (CurrentFrame > 5) CurrentFrame -= 4; 
			p.sprite.setTextureRect(IntRect(50 +(16 * int(CurrentFrame)), 0, 16, 30)); 
			p.sprite.move(0.1*time, 0);
			p.dir = 1;
		} 

		if (Keyboard::isKeyPressed(Keyboard::W)) 
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			if (p.dir == 0) p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)) + 16, 0, -16, 30));
			else p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30));
			p.sprite.move(0, -0.1*time); 
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) 
		{
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			if (p.dir == 0) p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)) + 16, 0, -16, 30));
			else p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30)); 
			p.sprite.move(0, 0.1*time); 
		}
		

		window.clear();
		//карта
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(13, 60, 16, 16)); //пол
				//if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//стена


				s_map.setPosition(j * 16, i * 16);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран
			}

		window.draw(p.sprite);
		window.display();
	}
	return 0;
}