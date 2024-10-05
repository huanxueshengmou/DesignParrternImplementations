#include <iostream>
#include <vector>
using std::vector;
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
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