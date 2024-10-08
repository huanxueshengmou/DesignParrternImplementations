#include <iostream>
#include "my_print.cpp"
#include <string>

class Iterator
{
public:
  virtual bool hasNext() = 0;
  virtual void *next() = 0;
};
class Aggregate
{
private:
  class AggregateIterator : public Iterator
  {
  protected:
    Aggregate *nextAggregate;

  public:
    AggregateIterator(Aggregate *nextAggregate) : nextAggregate(nextAggregate) {}

  public:
    bool hasNext()
    {
      return nextAggregate == nullptr ? false : true;
    }
    void *next()
    {
      if (hasNext())
      {
        void *result = static_cast<void *>(nextAggregate);
        nextAggregate = nextAggregate->nextAggregate;
        return result;
      }
      return nullptr;
    }
  };

public:
  Aggregate() : aggregateIterator(nullptr), nextAggregate(nullptr) {}

protected:
  Iterator *aggregateIterator;
  Aggregate *nextAggregate;

public:
  Iterator *createIterator()
  {
    aggregateIterator = new AggregateIterator(this);
    return aggregateIterator;
  }
  Iterator *getIterator()
  {
    return aggregateIterator;
  }
  void setNextAggregate(Aggregate *nextAggregate)
  {
    this->nextAggregate = nextAggregate;
  }
  Aggregate* getNextAggregate(){
    return nextAggregate;
  }
};

template <class T>
class List : public Aggregate
{
protected:
  T data;
  int size;

public:
  List() : Aggregate() {}

public:
  void setNextList(Aggregate *nextAggregate)
  {
    this->nextAggregate = nextAggregate;
    size++;
  }
  void pop()
  {
    if (nextAggregate == nullptr)
    {
      throw std::runtime_error("No next element to pop.");
    }

    Iterator *it = getIterator();
    Aggregate *prev = nullptr;
    Aggregate *current = this;
    while (current->getNextAggregate() != nullptr)
    {
      prev = current;
      current = current->getNextAggregate();
    }
    if (prev != nullptr)
    {
      prev->setNextAggregate(nullptr);
    }
    else
    {
      nextAggregate = nullptr;
    }
    size--;
    delete current;
  }
  int getSize()
  {
    return size;
  }
  T getdata(){
    return data;
  }
  void setDate(T data){
    this->data=data;
  }
};
int main()
{
  List<int> a1, a2;
  a1.setNextList(&a2);
  a1.setDate(2);
  a2.setDate(5);
  Iterator *it = a1.createIterator();
  while (it->hasNext())
  {
    List<int> *agg = static_cast<List<int>*>(it->next());
    print("Next Aggregate: ", agg->getdata());
  }

  delete it;
  return 0;
}

/*
  Next Aggregate: 
  2
  Next Aggregate: 
  5
*/