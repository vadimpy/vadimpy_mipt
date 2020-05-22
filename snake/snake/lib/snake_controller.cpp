#include "../headers/snake.hpp"

bool SnakeUserController::not_so_fast()
{
  if (clock.getElapsedTime().asMilliseconds() >= 1000 / freq)
  {
    clock.restart();
    return false;
  }
  return true;
}
SnakeUserController::SnakeUserController(sf::RenderWindow& window, const int f) :
window_(window),
freq(f)
{}
void SnakeUserController::update()
{
  if (not_so_fast())
    return;
  if (window_.pollEvent(event))
    if (event.type == sf::Event::Closed)
        commands_queue.push(Command::finish);

  switch (event.key.code)
  {
    case sf::Keyboard::Key::Up:
      commands_queue.push(Command::up);
    break;
    case sf::Keyboard::Key::Down:
      commands_queue.push(Command::down);
    break;
    case sf::Keyboard::Key::Left:
      commands_queue.push(Command::left);
    break;
    case sf::Keyboard::Key::Right:
      commands_queue.push(Command::right);
    break;
  }
}
Command SnakeUserController::get_cmd()
{
  if (commands_queue.empty())
    return Command::pass;
  Command cmd = commands_queue.front();
  commands_queue.pop();
  return cmd;
}
