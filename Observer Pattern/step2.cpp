#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "my_print.cpp"
using std::stack;
using std::string;
using std::vector;
class Observer
{
public:
    virtual void update(const string &WeatherJson) = 0;
};
class Subject
{
public:
    virtual void registerObserver(Observer *newObserver) = 0;
    virtual void removeObserver() = 0;
    virtual void notifyObservers() = 0;
};

class WeatherSubject : public Subject
{
protected:
    Observer *myObserver = nullptr;
    string WeatherJson;

public:
    void registerObserver(Observer *newObserver)
    {
        this->myObserver = newObserver;
    }
    void removeObserver()
    {
        this->myObserver = nullptr;
    }
    void notifyObservers()
    {
        if (myObserver)
        {
            myObserver->update(WeatherJson);
            WeatherJson = "";
        }
    }

public:
    template <class T>
    void FromHardwareWeatherData(T arg)
    {
        WeatherJson += arg;
        notifyObservers();
    }

public:
    template <class T, class... Ts>
    void FromHardwareWeatherData(T arg, Ts... args)
    {
        WeatherJson += arg;
        FromHardwareWeatherData(args...);
    }
};
class Memento
{
public:
    virtual ~Memento() {}

public:
    virtual string getState() const = 0;
    virtual void setState(const string &state) = 0;
};

class LogMemento : public Memento
{
private:
    string state;
public:
    LogMemento(const string &state) : state(state) {}
    string getState() const override
    {
        return state;
    }
    void setState(const string &state) override
    {
        this->state = state;
    }
};
class Caretaker
{
protected:
    stack<Memento *> logMemento;

public:
    stack<Memento *> &getlogMemento()
    {
        return logMemento;
    }

    stack<Memento *> &addlogMemento(Memento *memento)
    {
        logMemento.push(memento);
        return logMemento;
    }

    stack<Memento *> &POPlogMemento()
    {
        if (logMemento.empty())
            return logMemento;
        logMemento.pop();
        return logMemento;
    }
    void destroylogMemento()
    {
        while (!getlogMemento().empty())
        {
            delete getlogMemento().top();
            POPlogMemento();
        }
    }
};
class WeatherObserver : public Observer
{
protected:
    string WeatherJson;
    Caretaker caretaker;
public:
    void update(const string &WeatherJson)
    {
        this->WeatherJson = WeatherJson;
        alert();
        Memento *logMemento = new LogMemento(WeatherJson);
        caretaker.addlogMemento(logMemento);
    }
    void getLog()
    {
        int count=0;
        if (caretaker.getlogMemento().empty())
            return;

        while (!caretaker.getlogMemento().empty())
        {
            // 打印并删除 Memento 对象
            Memento *memento = caretaker.getlogMemento().top();
            printNonPln(count,":");
            count++;
            print(memento->getState());
            caretaker.POPlogMemento();
            delete memento; // 释放动态分配的内存
        }
    }

    void printCurrWeather()
    {
        print(WeatherJson);
    }
    void alert()
    {
        print("Beep!Beep!Beep!");
    }
};

void testObserverPattern()
{
    WeatherSubject weatherSubject;
    WeatherObserver weatherObserver;

    // Register the observer
    weatherSubject.registerObserver(&weatherObserver);

    // Simulate incoming hardware data
    weatherSubject.FromHardwareWeatherData("Temperature: 24°C", "Humidity: 60%", "Pressure: 1012 hPa");

    // No need to call notifyObservers() here, it's handled inside FromHardwareWeatherData()

    // Print the current weather data
    weatherObserver.printCurrWeather();

    weatherSubject.FromHardwareWeatherData("Temperature: 25°C", "Humidity: 10%");
    weatherObserver.printCurrWeather(); // This should print anything

    // Remove the observer
    weatherSubject.removeObserver();

    // Since observer is removed, no new updates should occur
    weatherSubject.FromHardwareWeatherData("Temperature: 25°C", "Humidity: 20%");
    weatherObserver.printCurrWeather(); // This should print old anything
    print("print log");
    weatherObserver.getLog();
}

int main()
{
    testObserverPattern();
    return 0;
}

/*
Beep!Beep!Beep!
Temperature: 24°CHumidity: 60%Pressure: 1012 hPa
Beep!Beep!Beep!
Temperature: 25°CHumidity: 10%
Temperature: 25°CHumidity: 10%
print log
0:Temperature: 25°CHumidity: 10%
1:Temperature: 24°CHumidity: 60%Pressure: 1012 hPa
*/