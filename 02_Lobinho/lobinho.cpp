#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height)
{
	auto dim = sprite.getLocalBounds();
	sprite.setScale((float)width / dim.width, (float)height / dim.height);
}

struct entity
{
	int x { 0 };
	int y { 0 };
	int step { 0 };
	sf::Sprite sprite;

	entity(int x, int y, int step, sf::Texture& texture) :
		x { x },
		y { y },
		step { step },
		sprite { texture }
	{
	}

	void draw(sf::RenderWindow& window)
	{
		this->sprite.setPosition(x * step, y * step);
		setSize(this->sprite, step, step);
		window.draw(this->sprite);
	}
};

struct fundo{
	int nc = {0};
	int nl = {0};
	int step {0};
	sf::Sprite sprite;
	sf::RectangleShape rect;
	fundo(int nc, int nl, int step, sf::Texture& texture){
		this-> nc = nc;
		this-> nl = nl;
		this-> step = step;
		this-> sprite.setTexture(texture);
		setSize(this->sprite, nc * step, nl * step);
		this-> sprite.setPosition(0, 0);
	}
	void draw (sf::RenderWindow& window){
		window.draw(this -> sprite);
	}
};

void control(sf::Keyboard::Key key, entity& entity, std::vector<sf::Keyboard::Key> move_keys){
	if(key == move_keys[0]){
		entity.x--;
	} else if (key == move_keys[1]){
		entity.y--;
	} else if (key == move_keys[2]){
		entity.x++;
	} else if (key == move_keys[3]){
		entity.x++;
	}
}
int main(){

	sf::Texture wolf_tex;
	if (! wolf_tex.loadFromFile("lobo.png")){
		std::cout << "Erro ao carregar textura" << std::endl;
		exit(1);
	};
	sf::Texture coelho_tex;
	if (! coelho_tex.loadFromFile("coelho.png")){
		std::cout << "Erro ao carregar textura" << std::endl;
		exit(1);
	};
	sf::Texture ceu_tex;
	if (! ceu_tex.loadFromFile("ceu.png")){
		std::cout << "Erro ao carregar textura" << std::endl;
		exit(1);
	};

	entity wolf(1, 1, 100, wolf_tex);
	entity coelho(3, 3, 100, coelho_tex);
	fundo ceu(7, 5, 100, ceu_tex);

	sf::RenderWindow window(sf::VideoMode(fundo.nc * STEP, fundo.n1 * STEP), "Jogo lobo");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}else if(event.type == sf::Event::KeyPressed){
				control(event.key.code, wolf,{sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
				control(event.key.code, coelho,{sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});

			}
		}


		window.clear();
		fundo.draw(window);
		wolf.draw(window);
		coelho.draw(window);
		window.display();
	}
	return 0;
}
