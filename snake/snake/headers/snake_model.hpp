#ifndef SNAKE_SHARED
#define SNAKE_SHARED
#include "snake_shared.hpp"
#endif

class SnakeModel
{
private:
  sf::Clock clock;
  const int width;
  const int height;
  int freq;
  const int difficulty_;
  bool finished;
  int fruits_value;
  struct SnakeNode
  {
    int y;
    int x;
  };
  enum class Direction {left, right, up, down};
  Direction snake_direction;
  list<SnakeNode> snake;
  vector<vector<State>> field;

  bool not_so_fast();
  void generate_fruits();

public:
  bool not_finished();
  SnakeModel(const int, const int, const int, const int);

  void read_cmd(Command);
  void update();
  vector<vector<State>> get_state();
};
