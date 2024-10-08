#include <iostream>
#include <vector>
#include <memory>

// 前向声明
template <typename T>
class ConcreteIterator;

template <typename T>
class Aggregate {
public:
    virtual std::shared_ptr<ConcreteIterator<T>> createIterator() = 0;
    virtual void addItem(const T& item) = 0;
};

template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};
template <typename T>
class ConcreteAggregate : public Aggregate<T> {
private:
    std::vector<T> items;

public:
    std::shared_ptr<ConcreteIterator<T>> createIterator() override {
        return std::make_shared<ConcreteIterator<T>>(this);
    }

    void addItem(const T& item) override {
        items.push_back(item);
    }

    size_t getSize() const {
        return items.size();
    }

    T getItem(size_t index) const {
        return items.at(index);
    }
};
template <typename T>
class ConcreteIterator : public Iterator<T> {
private:
    const ConcreteAggregate<T> *aggregate;
    size_t currentIndex;

public:
    ConcreteIterator(const ConcreteAggregate<T> *aggregate) : aggregate(aggregate), currentIndex(0) {}

    bool hasNext() override {
        return currentIndex < aggregate->getSize();
    }

    T next() override {
        if (!hasNext()) {
            throw std::out_of_range("Iterator out of range");
        }
        return aggregate->getItem(currentIndex++);
    }
};
int main() {
    auto aggregate = std::make_shared<ConcreteAggregate<int>>();
    aggregate->addItem(1);
    aggregate->addItem(2);
    aggregate->addItem(3);

    auto it = aggregate->createIterator();
    while (it->hasNext()) {
        std::cout << it->next() << std::endl;
    }

    return 0;
}
/*output
    1
    2
    3
*/