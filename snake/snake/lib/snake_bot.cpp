#include "../headers/snake_bot.hpp"

bool SnakeBotController::not_so_fast()
{
  if (clock.getElapsedTime().asMilliseconds() >= 1000 / freq)
  {
    clock.restart();
    return false;
  }
  return true;
}

SnakeBotController::SnakeBotController(sf::RenderWindow& window, const int f) :
window_(window), freq(f), cmd(Command::pass)
{}

void SnakeBotController::update(vector<vector<State>> model)
{
  if (window_.pollEvent(event))
    if (event.type == sf::Event::Closed)
        cmd = Command::finish;
  if (not_so_fast())
    return;
  int snake_x = 0, snake_y = 0;
  int target_x = 0, target_y = 0;
  bool flag = true;
  for (int i = 0; i < model.size(); ++i)
    for (int j = 0; (j < model[0].size()) && (flag); ++j)
      if (model[i][j] == State::head)
      {
        snake_x = j;
        snake_y = i;
        flag = false;
        break;
      }
  flag = true;
  for (int i = 0; i < model.size(); ++i)
    for (int j = 0; (j < model[0].size()) && (flag); ++j)
      if (model[i][j] == State::fruit)
      {
        target_x = j;
        target_y = i;
        flag = false;
        break;
      }
  if (snake_x < target_x)
    cmd = Command::right;
  if (snake_x > target_x)
    cmd = Command::left;
  if (snake_y < target_y)
    cmd = Command::down;
  if (snake_y > target_y)
    cmd = Command::up;
}

Command SnakeBotController::get_cmd()
{
  return cmd;
}
