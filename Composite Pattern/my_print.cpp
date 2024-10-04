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



void printNonPln(){
  std::cout<<"";
}
template <class T>
void printNonPln(T arg)
{
  std::cout << arg ;
}

template <class T, class... Ts>
void printNonPln(T arg, Ts... args)
{
  std::cout << arg ;
  printNonPln(args...);
}