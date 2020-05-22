#ifndef SNAKE_SHARED
#define SNAKE_SHARED
#include "snake_shared.hpp"
#endif

class SnakeBotController
{
private:
  sf::Clock clock;
  sf::Event event;
  sf::RenderWindow& window_;
  const int freq;
  bool not_so_fast();
  Command cmd;
public:
  SnakeBotController(sf::RenderWindow&, const int);
  void update(vector<vector<State>>);
  Command get_cmd();
};
