#include <iostream>
#include <string>
#include "my_print.cpp"
using namespace std;

class DVDPlayer {
public:
    void turnOn() {
        cout << "DVD Player is now ON." << endl;
    }
    
    void play() {
        cout << "DVD Player is playing." << endl;
    }
};

class Projector {
public:
    void turnOn() {
        cout << "Projector is now ON." << endl;
    }
    
    void setInput() {
        cout << "Projector input set to DVD." << endl;
    }
    
    void show() {
        cout << "Projector is showing the video." << endl;
    }
};

class SoundSystem {
public:
    void turnOn() {
        cout << "Sound System is now ON." << endl;
    }
    
    void setVolume(int level) {
        cout << "Sound System volume set to " << level << "." << endl;
    }
    
    void play() {
        cout << "Sound System is playing audio." << endl;
    }
};
class HomeTheaterFacade{
    protected:
    DVDPlayer* dvdPlayer;
    Projector* projector;
    SoundSystem* soundSystem;
    bool isturnon=false;
    public:
    HomeTheaterFacade& setProjector(Projector* projector){
        this->projector=projector;
        return *this;
    }
    HomeTheaterFacade& setSoundSystem(SoundSystem* soundSystem){
        this->soundSystem=soundSystem;
        return *this;
    }
    HomeTheaterFacade& setDvdPlayer(DVDPlayer* dvdPlayer){
        this->dvdPlayer=dvdPlayer;
        return *this;
    }
    HomeTheaterFacade& setVolume(int num){
        this->soundSystem->setVolume(5);
        return *this;
    }
    HomeTheaterFacade& setInput(){
        this->projector->setInput();
        return *this;
    }
    void watchMovie(){
        if(!isturnon){
            if(dvdPlayer)
            dvdPlayer->turnOn();
            if(projector)
            projector->turnOn();
            if(soundSystem)
            soundSystem->turnOn();
        }
        if(dvdPlayer)
        dvdPlayer->play();
        if(projector)
        projector->show();
        if(soundSystem)
        soundSystem->play();
    }
};
int main() {
    DVDPlayer* dvdPlayer=new DVDPlayer();
    Projector* projector=new Projector();
    SoundSystem* soundSystem=new SoundSystem();
    
    
    HomeTheaterFacade* homeTheaterFacade=new HomeTheaterFacade();
    homeTheaterFacade->setDvdPlayer(dvdPlayer).setProjector(projector)
    .setSoundSystem(soundSystem).setInput();
    homeTheaterFacade->watchMovie();
    homeTheaterFacade->setVolume(5);

    return 0;
}
