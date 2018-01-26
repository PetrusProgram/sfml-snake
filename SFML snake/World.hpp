#pragma once
#include "Snake.hpp"
#include <array>
class World {
public:
	World(sf::Vector2u l_windSize, Snake& snake);

	int GetBlockSize();

	void RespawnApple();

	void Update(Snake& l_player);
	void Render(sf::RenderWindow& l_window);
private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	int m_blockSize;
	 Snake& m_snake;
	sf::CircleShape m_appleShape;
	std::array<sf::RectangleShape, 4> m_bounds;
};