#include <iostream>
#include <set>
#include <string>

// В STL итераторы set и map хранятся в виде красно-чёрного дерева, вставка O(logN)
// Таким образом сложность O(NlogN)
// Можно взять вектор и добавлять вставками, сложность будет O(N^2)
// Можно взять вектор и добавлять в конец, потом вызвать sort и unique (O(NlogN + N^2))
// Я взял set, потому что писать меньше и по сложности оптимально

int main()
{
  std::set<std::string> m;
  std::string input;
  while (!(std::cin.eof()))
  {
    std::getline(std::cin, input);
    m.insert(input);
  }
  for(auto it: m)
    std::cout << it << std::endl;
  return 0;
}
