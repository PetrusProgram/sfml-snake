#include "World.hpp"
#include <random>
#include <iostream>
World::World(sf::Vector2u l_windSize, Snake& snake) : m_snake(snake) {
	m_blockSize = 16;

	m_windowSize = l_windSize;
	RespawnApple();
	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setRadius(m_blockSize / 2.f);

	for (std::size_t i = 0; i < m_bounds.size(); ++i) {
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)) {
			m_bounds[i].setSize(sf::Vector2f(static_cast<float>(m_windowSize.x), static_cast<float>(m_blockSize)));
		}
		else {
			m_bounds[i].setSize(sf::Vector2f(static_cast<float>(m_blockSize), static_cast<float>(m_windowSize.y)));
		}
		if (i < 2) {
			m_bounds[i].setPosition(0.f, 0.f);
		}
		else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}

int World::GetBlockSize() { return m_blockSize; }

void World::RespawnApple() {
	static const int maxX = (m_windowSize.x / m_blockSize) - 2;
	static const int maxY = (m_windowSize.y / m_blockSize) - 2;
	static std::random_device r;
	static std::mt19937 RandomEngine(r());
	static std::uniform_int_distribution<int> distributionX(1, maxX);
	static std::uniform_int_distribution<int> distributionY(1, maxY);
	bool pass = true;
	int counter = 0;
	const auto& snake = m_snake.getSnake();
	//get a random spawn position
	do
	{
		m_item = sf::Vector2i(distributionX(RandomEngine), distributionY(RandomEngine));
		//check that the spawn position is not same as snake cord.
		for (const auto& x : snake)
			if (x.position == m_item)
			{
				counter++;
				pass = false;
				if (counter > 10)
				{
					break;
				}
			}
		if (counter > 10)
			break;
	} while (!pass);

		if (!pass)
		{
			for (const auto& x : snake)
				if (x.position == m_item)
				{
					do
					{
						m_item.x = ++m_item.x % maxX;
						m_item.y = ++m_item.y % maxY;
					} while (m_item.x<3 || m_item.y <3);
					
				}
		}
		

	
	m_appleShape.setPosition(
		m_item.x * m_blockSize,
		m_item.y * m_blockSize);
}

void World::Update(Snake& l_player) {
	if (l_player.GetPosition() == m_item) {
		l_player.Extend();
		l_player.IncreaseScore();
		RespawnApple();
	}

	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;

	if (l_player.GetPosition().x <= 0 ||
		l_player.GetPosition().y <= 0 ||
		l_player.GetPosition().x >= gridSize_x - 1 ||
		l_player.GetPosition().y >= gridSize_y - 1)
	{
		l_player.Lose();
	}
}

void World::Render(sf::RenderWindow& l_window) {
	for (std::size_t i = 0; i < m_bounds.size(); i++) {
		l_window.draw(m_bounds[i]);
	}
	l_window.draw(m_appleShape);
}