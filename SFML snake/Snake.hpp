#pragma once
#include "Textbox.hpp"

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;
enum class Direction { None, Up, Down, Left, Right };

class Snake {
public:
	Snake(int l_blockSize, Textbox* l_log);
	
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();

	void Lose(); 
	void ToggleLost();
	const SnakeContainer& getSnake()
	{
		return m_snakeBody;
	}
	Direction GetPhysicalDirection();

	void Extend(); 
	void Reset(); 

	void Move(); 
	void Tick(); 
	void Cut(int l_segments); 
	void Render(sf::RenderWindow& l_window);
private:
	void CheckCollision(); 

	SnakeContainer m_snakeBody;
	int m_size{ 0 };
	Direction m_dir;
	int m_speed{ 15 };
	int m_lives{ 3 };
	unsigned int m_score{ 0 };
	bool m_lost{ false };
	sf::RectangleShape m_bodyRect; 
	Textbox* m_log{ nullptr };
};