#include "../headers/snake.hpp"

bool SnakeModel::not_so_fast()
{
  if (clock.getElapsedTime().asMilliseconds() >= 1000 / freq)
  {
    clock.restart();
    return false;
  }
  return true;
}

void SnakeModel::generate_fruits()
{
  while (fruits_value == 0)
    for(int i = 0; i < 3; ++i)
    {
      int x = 1 + rand() % (width - 2);
      int y = 1 + rand() % (height - 2);
      if (field[y][x] == State::empty)
      {
        field[y][x] = State::fruit;
        ++fruits_value;
      }
    }
}

bool SnakeModel::not_finished()
{
  return !finished;
}

SnakeModel::SnakeModel(const int w, const int h, const int f, const int difficulty) :
width(w), height(h), finished(false), freq(f), difficulty_(difficulty)
{
  srand (time(NULL));
  snake.push_back(SnakeNode{1 + rand() % (height - 2), 1 + rand() % (width - 2)});
  snake_direction = (Direction) (rand() % 4);
  field.resize(height);
  for(int i = 0; i < height; ++i)
  {
    field[i].resize(width);
    for (int j = 0; j < width; ++j)
      if ((i % (height - 1) == 0) || (j % (width - 1) == 0))
        field[i][j] = State::wall;
      else
        field[i][j] = State::empty;
  }
  field[snake.front().y][snake.front().x] = State::head;
  generate_fruits();
}

void SnakeModel::read_cmd(Command cmd)
{
  switch (cmd)
  {
    case Command::right:
      if (snake_direction != Direction::left)
        snake_direction = Direction::right;
    break;
    case Command::left:
      if (snake_direction != Direction::right)
        snake_direction = Direction::left;
    break;
    case Command::up:
    if (snake_direction != Direction::down)
      snake_direction = Direction::up;
    break;
    case Command::down:
    if (snake_direction != Direction::up)
      snake_direction = Direction::down;
    break;
    case Command::finish:
      finished = true;
    break;
  }
}

void SnakeModel::update()
{
  if (not_so_fast())
    return;
  if (!finished)
  {
    State next_state;
    auto end = snake.end();
    --end;
    SnakeNode new_node;
    switch (snake_direction)
    {
      case Direction::right:
        new_node.x = end->x + 1;
        new_node.y = end->y;
        next_state = field[new_node.y][new_node.x];
      break;
      case Direction::left:
        new_node.x = end->x - 1;
        new_node.y = end->y;
        next_state = field[new_node.y][new_node.x];
      break;
      case Direction::up:
      new_node.x = end->x;
      new_node.y = end->y - 1;
      next_state = field[new_node.y][new_node.x];
      break;
      case Direction::down:
        new_node.x = end->x;
        new_node.y = end->y + 1;
        next_state = field[new_node.y][new_node.x];
      break;
    }

    for(auto node : snake)
      field[node.y][node.x] = State::empty;

    if (next_state == State::empty)
    {
      for(auto it = snake.begin(); it != end; ++it)
      {
          auto it_next = it;
          ++it_next;
          it->x = it_next->x;
          it->y = it_next->y;
      }
      end->x = new_node.x;
      end->y = new_node.y;
    }

    if (next_state == State::fruit)
    {
      snake.push_back(new_node);
      --fruits_value;
      generate_fruits();
      freq += difficulty_;
    }

    if ((next_state == State::wall) || (next_state == State::snake))
      finished = true;
    else
    {
      for(auto node : snake)
        field[node.y][node.x] = State::snake;
      field[snake.back().y][snake.back().x] = State::head;
    }
  }
}

vector<vector<State>> SnakeModel::get_state()
{
  return field;
}
