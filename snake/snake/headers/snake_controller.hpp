#ifndef SNAKE_SHARED
#define SNAKE_SHARED
#include "snake_shared.hpp"
#endif

class SnakeUserController
{
private:
  sf::Clock clock;
  sf::Event event;
  sf::RenderWindow& window_;
  queue<Command> commands_queue;
  const int freq;
  bool not_so_fast();
public:
  SnakeUserController(sf::RenderWindow&, const int);
  void update();
  Command get_cmd();
};
