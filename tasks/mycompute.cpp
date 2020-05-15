#include <iostream>
#include <list>
#include <string>
#include <vector>

// Здесь я взял список, потому что удаление работает за константу
// Из аргументов искомый результат записываю отдельно в переменную, цифры в список
// Далее делаю новый список с первой цифрой
// Далее добавляю туда два узла: OP и DIGIT, где OP - одна из операций (дефайны ниже),
// а DIGIT - цифра из исходного ввода
// Это всё происходит рекурентно, пока с помощью сравнения итераторов я не поймаю конец списка цифр
// Как только список цифр кончился, функция count вычисляет результат по списку
// В этот момент собранный список выглядит, например, следующим образом
// {1, PLUS, 2, MUL, 3, MINUS, 4, MERGE, 0}
// Функция count делает три прохода по списку
// Первым проходом находит все MERGE, в каждый узел с MERGE записывает результат слияния соседних цифр
// Далее соседние узлы извлекаются из списка
// Далее аналогичные действия для MUL и DIV, затем для PLUS и MINUS
// В случае, когда один из вариантов перебора содержит деление на ноль или слияние с нулём вида 05,
// count возвращает TOXIC
// Перебор идёт по 5^(N-1) вариантам (N - кол-во цифр). Count работает линейно

#define  PLUS -1
#define MINUS -2
#define   MUL -3
#define   DIV -4
#define MERGE -5
#define TOXIC -99999

using handle = std::list<int>::iterator;
using list = std::list<int>;

int count(list data)
{
  for(auto it = data.begin(); it != data.end(); ++it)
    if (*it == MERGE)
    {
      auto it_left = --it;
      ++it;
      auto it_right = ++it;
      --it;
      if (*it_left == 0)
        return TOXIC;
      *it = (*it_left) * 10 + (*it_right);

      data.erase(it_left);
      data.erase(it_right);
    }

  for(auto it = data.begin(); it != data.end(); ++it)
    if ((*it == MUL) || (*it == DIV))
    {
        auto it_left = --it;
        ++it;
        auto it_right = ++it;
        --it;
        if ((*it == DIV) && (*it_right == 0))
          return TOXIC;
        if (*it == MUL)
          *it = (*it_left) * (*it_right);
        else
          *it = (*it_left) / (*it_right);

        data.erase(it_left);
        data.erase(it_right);
      }


  for(auto it = data.begin(); it != data.end(); ++it)
    if ((*it == PLUS) || (*it == MINUS))
    {
      auto it_left = --it;
      ++it;
      auto it_right = ++it;
      --it;

      if (*it == PLUS)
        *it = (*it_left) + (*it_right);
      else
        *it = (*it_left) - (*it_right);

      data.erase(it_left);
      data.erase(it_right);
    }
  return *(data.begin());
}

void print_data(list data)
{
  std::vector<std::string> pieces{"+", "-", "*", "/", ""};
  for (auto it: data)
    if (it < 0)
      std::cout << pieces[-it-1];
    else
      std::cout << it;
}

void search(handle pure_data_it, handle pure_data_end, list data, int res)
{
  if (pure_data_end != pure_data_it)
  {
    ++pure_data_it;

    std::vector<int> ops{MERGE, PLUS, MINUS, MUL, DIV};
    for(auto op: ops)
    {
      data.push_back(op);
      data.push_back(*pure_data_it);
      search(pure_data_it, pure_data_end, data, res);
      data.pop_back(); data.pop_back();
    }
  }
  else
  if (count(data) == res)
  {
    print_data(data);
    std::cout << "=" << res << std::endl;
  }
}

int main(int k, char* args[])
{
  list pure_data;
  int result = std::stoi(args[1]);
  for (int i = 2; i < k; ++i)
    pure_data.push_back(std::stoi(args[i]));

  list data{pure_data.front()};
  search(pure_data.begin(), --pure_data.end(), data, result);
  return 0;
}



int foo(std::vector<int>& a) {...}
int main()
{
  ...
  foo(a);
}

int foo(std::vector<int> a) {...}
int main()
{
  ...
  foo(a);
}
