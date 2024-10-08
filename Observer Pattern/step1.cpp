#include <iostream>
#include <vector>
#include <string>
#include "my_print.cpp"
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
      WeatherJson="";
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

class WeatherObserver : public Observer
{
protected:
  string WeatherJson;

public:
  void update(const string &WeatherJson)
  {
    this->WeatherJson = WeatherJson;
  }
  void printCurrWeather()
  {
    print(WeatherJson);
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

  weatherSubject.FromHardwareWeatherData("Temperature: 25°C","Humidity: 10%");
  weatherObserver.printCurrWeather(); // This should print anything

  // Remove the observer
  weatherSubject.removeObserver();

  // Since observer is removed, no new updates should occur
  weatherSubject.FromHardwareWeatherData("Temperature: 25°C","Humidity: 20%");
  weatherObserver.printCurrWeather(); // This should print old anything
}

int main()
{
  testObserverPattern();
  return 0;
}

/*
Temperature: 24°CHumidity: 60%Pressure: 1012 hPa
Temperature: 25°CHumidity: 10%
Temperature: 25°CHumidity: 10%
*/ 