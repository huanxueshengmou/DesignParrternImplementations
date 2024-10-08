#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "my_print.cpp"
#include <algorithm>
using std::string;
using std::vector;
using std::shared_ptr;

class Observer {
public:
    virtual void update(const string& weatherData) = 0;
    virtual ~Observer() {}
};

class Subject {
public:
    virtual void registerObserver(shared_ptr<Observer> newObserver) = 0;
    virtual void removeObserver(shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() {}
};

class WeatherSubject : public Subject {
private:
    vector<shared_ptr<Observer>> observers;
    string weatherData;

public:
    void registerObserver(shared_ptr<Observer> newObserver) override {
        observers.push_back(newObserver);
    }

    void removeObserver(shared_ptr<Observer> observer) override {
        observers.erase(remove_if(observers.begin(), observers.end(),
            [&observer](const shared_ptr<Observer>& o) { return o == observer; }),
            observers.end());
    }



    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(weatherData);
        }
    }

    void setWeatherData(const string& data) {
        weatherData = data;
        notifyObservers();
    }
};

class WeatherObserver : public Observer {
private:
    string weatherData;

public:
    void update(const string& weatherData) override {
        this->weatherData = weatherData;
        printCurrWeather();
    }

    void printCurrWeather() const {
        print("Current Weather: " + weatherData);
    }
};

void testObserverPattern() {
    auto weatherSubject = std::make_shared<WeatherSubject>();
    auto weatherObserver1 = std::make_shared<WeatherObserver>();
    auto weatherObserver2 = std::make_shared<WeatherObserver>();

    // Register the observers
    weatherSubject->registerObserver(weatherObserver1);
    weatherSubject->registerObserver(weatherObserver2);

    // Simulate setting weather data
    weatherSubject->setWeatherData("Temperature: 24°C, Humidity: 60%");
    weatherSubject->setWeatherData("Temperature: 25°C, Humidity: 10%");

    // Remove the first observer
    weatherSubject->removeObserver(weatherObserver1);

    // Update weather data again
    weatherSubject->setWeatherData("Temperature: 26°C, Humidity: 20%");
}

int main() {
    testObserverPattern();
    return 0;
}

/*
Expected Output:
Current Weather: Temperature: 24°C, Humidity: 60%
Current Weather: Temperature: 24°C, Humidity: 60%
Current Weather: Temperature: 25°C, Humidity: 10%
Current Weather: Temperature: 25°C, Humidity: 10%
Current Weather: Temperature: 26°C, Humidity: 20%
*/
