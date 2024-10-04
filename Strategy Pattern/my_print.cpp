#include <iostream>

void print(){
  std::cout<<"\n";
}
template <class T>
void print(T arg)
{
  std::cout << arg << "\n";
}

template <class T, class... Ts>
void print(T arg, Ts... args)
{
  std::cout << arg << "\n";
  print(args...);
}