#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <vector>

struct Pencil
{
	sf::Font font;
	sf::Text text;
	sf::RenderWindow& window;

	Pencil(sf::RenderWindow& window) :
		window { window }
	{
		if (font.loadFromFile("arial.tff") != 1)
		{
			std::cout << "Fail to load font" << std::endl;
			window.close();
		}
		else
		{
			std::cout << "Font loaded" << std::endl;
		}
	}
	void write(std::string str, int x, int y, int size, sf::Color color)
	{
		text.setString(str);
		text.setCharacterSize(size);
		text.setPosition(x, y);
		text.setFillColor(color);
		window.draw(text);
	}
};

struct Bubble
{
	int x;
	int y;
	int speed;
	char letter;
	bool alive { true };
	static const int radius { 10 };

	Bubble(int x, int y, int speed, char letter)
	{
		this->x = x;
		this->y = y;
		this->speed = speed;
		this->letter = letter;
	}
	void Update(int y, int speed)
	{
		this->y += this->speed;
	}
	void draw(sf::RenderWindow& window)
	{
		static Pencil pencil(window);
		sf::CircleShape Bubble(Bubble::radius);
		Bubble.setPosition(x, y);
		Bubble.setFillColor(sf::Color::Red);
		window.draw(Bubble);
		pencil.write(std::string(1, letter), x + 0.2 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::Blue);
	}
};
struct Board
{
	sf::RenderWindow& window;
	std::vector<Bubble> bubbles;
	const int new_bubble_timeout { 30 };
	int new_bubble_time { 0 };
	int hits { 0 };
	int misses { 0 };
	Pencil Pencil;

	Board(sf::RenderWindow& window) :
		window(window),
		Pencil { window }
	{
		bubbles.push_back(Bubble(100, 100, 'A', 1));
		bubbles.push_back(Bubble(200, 100, 'B', 2));
		bubbles.push_back(Bubble(300, 100, 'C', 3));
	}

	void Update()
	{
		if (this->check_new_bubble())
		{
			this->add_new_bubble();
		}

		for (auto& Bubble : bubbles)
		{
			Bubble.draw(window);
		}
		this->mark_bubbles();
		this->remove_dead_bubbles();
	}

	void remove_dead_bubbles()
	{
		std::vector<Bubble> alives;
		for (Bubble& bubble : bubbles)
		{
			if (bubble.alive)
			{
				alives.push_back(bubble);
			}
		}
		this->bubbles = alives;
	}

	void mark_bubbles()
	{
		for (Bubble& bubble : bubbles)
		{
			if (bubble.y + 2 * Bubble::radius > (int)this->window.getSize().y)
			{
				if (bubble.alive)
				{
					bubble.alive = false;
					this->misses++;
				}
			}
		}
	}

	void hit_bubble(char letter)
	{
		for (Bubble& bubble : bubbles)
		{
			if (bubble.letter == letter)
			{
				bubble.alive = false;
				this->hits++;
				break;
			}
		}
	}

	void add_new_bubble()
	{
		int x = rand() % ((int)this->window.getSize().x - 2 * Bubble::radius);
		int y = -2 * Bubble::radius;
		int speed = rand() % 5 + 1;
		char letter = rand() % 26 + 'A';
		bubbles.push_back(Bubble(x, y, letter, speed));
	}

	bool check_new_bubble()
	{
		new_bubble_time--;
		if (new_bubble_time <= 0)
		{
			new_bubble_time = this->new_bubble_timeout;
			return true;
		}
		return false;
	}

	void draw()
	{
		Pencil.write("Hits: " + std::to_string(this->hits) + "Misses" + std::to_string(this->misses), 10, 10, 20, sf::Color::White);
		Pencil.write("Size: " + std::to_string(this->bubbles.size()), 10, 30, 20, sf::Color::White);
		for (Bubble& bubble : bubbles)
		{
			bubble.draw(window);
		}
	}
};

struct Game
{
	sf::RenderWindow window;
	std::function<void()> on_update;
	

	Board board;

	Game() :
		window(sf::VideoMode(800, 600), "Bubble Game"),
		board(window)
	{
		this->on_update = [&]() { //?????????, não entendi
			this->draw();
		};
		window.setFramerateLimit(60);
	}

	void process_events()
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::TextEntered)
			{
				char code = static_cast<char>(event.text.unicode);
				code = toupper(code);
				board.hit_bubble(code);
			}
		}
	}

	void draw() //gameplay, onde tudo está sendo chamado
	{
		board.Update();
		window.clear();
		board.draw();
		window.display();
		if (board.misses > 5){
			this-> on_update = [&](){
				this->game_over();
			};
		}
	}

	void game_over()
	{
		static Pencil Pencil(window);
		window.clear(sf::Color::Cyan);
		Pencil.write("Game Over", 300, 300, 50, sf::Color::Red);
		window.display();
	}

	void main_loop()
	{
		while (window.isOpen())
		{
			process_events();
			on_update(); //:???????
		}
	}
};

int main()
{

	Game game;
	game.main_loop();

	return 0;
}