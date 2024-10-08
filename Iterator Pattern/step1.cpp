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
};
int main()
{
  Aggregate a1, a2;
  a1.setNextAggregate(&a2);

  Iterator *it = a1.createIterator();
  while (it->hasNext())
  {
    Aggregate *agg = static_cast<Aggregate *>(it->next());
    print("Next Aggregate: ",agg);
  }

  delete it;
  return 0;
}

/*
Next Aggregate: 
0x61fe00
Next Aggregate: 
0x61fdf0
*/  