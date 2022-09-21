#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;

class Player  { // класс Игрока
private:
	float x, y;
public:
	float w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int playerScore, health; // счет / здоровье
	bool life, isMove;
	int dir = 1; //направление право лево для анимации
	int course; // направление для хотьбы
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт

	Player(String F, float X, float Y, float W, float H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		dx = 0; dy = 0; speed = 0; course = 0; playerScore = 0; health = 100;
		life = true;
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;
		sprite.setTextureRect(IntRect(w, h, w, h)); 

	}

	void update(float time)
	{
		switch (course)
		{
		case 0: dx = 0.7*speed; dy = 0; break; // вправо
		case 1: dx = 0.7*-speed; dy = 0; break; // влево
		case 2: dx = 0; dy = speed; break; // вниз
		case 3: dx = 0; dy = -speed; break; // вверх
		case 4: dx = 0.55*speed; dy = -speed; break;//вверх-вправо
		case 5: dx = 0.55*-speed; dy = -speed; break;//вверх-влево
		case 6: dx = 0.55*speed; dy = speed ; break;//вниз-вправо
		case 7: dx = 0.55*-speed ; dy = speed ; break;//вниз-влево
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
		if (health <=0){life = false;}
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		for (int i = y / 16; i < (y + h) / 16; i++)
			for (int j = x / 16; j < (x + w) / 16; j++)
			{
				if (TileMap[i][j] == '/')//если игрок соответствует символу / границы, то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 16 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 16 + 16;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx > 0)
					{
						x = j * 16 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 16 + 16;//аналогично идем влево
					}
				}
			}
	}

	float getplayercoordinateX() {	//этим методом будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY() {	//этим методом будем забирать координату Y 	
		return y;
	}
};

class Entity {
public:
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove;
	Texture texture;
	Sprite sprite;
	String name;//для разных врагов тип изменится от имени
	Entity(Image& image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
};

class Weapon {
public:
	float x, y, w, h;
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	Weapon(String F, float X, float Y, float W, float H) {
		File = F;
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y; w = W; h = H;
		sprite.setTextureRect(IntRect(x, y, w, h));
		
	}	
};

int main()
{
	RenderWindow window(VideoMode(640, 480), "ISW");

	Font font;//шрифт
	font.loadFromFile("images/CyrilicOld.ttf");
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. 

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом	

	Player p("knight_m.png", 300, 175, 16, 30);
	Weapon sp("knight_m.png", 154, 3, 7, 30);

	float CurrentFrame = 0;
	Clock clock;	

	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asMicroseconds();
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
					p.sprite.setTextureRect(IntRect(50 + 16, 0, -16, 30));   // направления для анимации героя
				if (p.dir == 1)
					p.sprite.setTextureRect(IntRect(50, 0, 16, 30)); 
			}
			
		}
		
		float coordinatePlayerX, coordinatePlayerY = 0;
		coordinatePlayerX = p.getplayercoordinateX();
		coordinatePlayerY = p.getplayercoordinateY();

		if (Keyboard::isKeyPressed(Keyboard::A))
		{ 
			p.course = 1; p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame))+16, 0, -16, 30));
			//p.sprite.move(-0.07 * time, 0);
			p.dir = 0;
			
		} 

		if (Keyboard::isKeyPressed(Keyboard::D)) 
		{
			p.course = 0; p.speed = 0.1;
			CurrentFrame += 0.005 * time; 
			if (CurrentFrame > 5) CurrentFrame -= 4; 
			p.sprite.setTextureRect(IntRect(50 +(16 * int(CurrentFrame)), 0, 16, 30)); 
			p.dir = 1;
			
		} 

		if (Keyboard::isKeyPressed(Keyboard::W)) 
		{
			if (Keyboard::isKeyPressed(Keyboard::D)) p.course = 4 ;
			else if (Keyboard::isKeyPressed(Keyboard::A)) p.course = 5 ;
			else p.course = 3; 
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			if (p.dir == 0) p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)) + 16, 0, -16, 30)); 
			else p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30));
			
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) 
		{
			if (Keyboard::isKeyPressed(Keyboard::D)) p.course = 6;
			else if (Keyboard::isKeyPressed(Keyboard::A)) p.course = 7;
			else p.course = 2; 
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 5) CurrentFrame -= 4;
			if (p.dir == 0) p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)) + 16, 0, -16, 30));
			else p.sprite.setTextureRect(IntRect(50 + (16 * int(CurrentFrame)), 0, 16, 30)); 
			
		}

		if (Keyboard::isKeyPressed(Keyboard::Numpad1))
		{

		}if (Keyboard::isKeyPressed(Keyboard::Numpad2))
		{

		}if (Keyboard::isKeyPressed(Keyboard::Numpad3))
		{

		}if (Keyboard::isKeyPressed(Keyboard::Numpad4))
		{

		}if (Keyboard::isKeyPressed(Keyboard::Numpad5))
		{

		}if (Keyboard::isKeyPressed(Keyboard::Numpad6))
		{

		}if (Keyboard::isKeyPressed(Keyboard::Numpad7))
		{

		}if (Keyboard::isKeyPressed(Keyboard::Numpad8))
		{

		}
		
		p.update(time);

		
		window.clear();
		//КАРТА
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(13, 60, 16, 16)); //пол
				if (TileMap[i][j] == '/')  s_map.setTextureRect(IntRect(115, 60, 16, 16)); // не пол
				if (TileMap[i][j] == 'o')  s_map.setTextureRect(IntRect(93, 140, 16, 16)); // яма
				

				s_map.setPosition(j * 16, i * 16);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате  и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран
			}
		
		std::ostringstream playerScoreString;    // объявили переменную
		playerScoreString << p.playerScore;		//занесли в нее число очков, то есть формируем строку
		text.setString("Счет:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(40, 430);
		window.draw(text);//рисую этот текст

		window.draw(p.sprite);
		window.display();
	}
	return 0;
}