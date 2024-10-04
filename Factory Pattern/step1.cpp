#include <iostream>
#include <memory>
#include <string>

using namespace std;

class enemy {
    // friend class enemyCreator;
    // friend class Goblin;
    // friend class Dragon;
    // friend class Troll;
    // friend class Orc;
    string name;
    string weapons;
    int HP;
    int harm;
    int speed;
    int attackFrequency;

public:
    enemy(string n = "Unknown Enemy", string w = "拳头", int hp = 100, int h = 10, int s = 5, int af = 1) 
        : name(n), weapons(w), HP(hp), harm(h), speed(s), attackFrequency(af) {}

public:
    bool attack() {
        cout << name + " did " + to_string(harm) + " points of damage with his " + weapons << endl;
        return true;
    }
    bool move() {
        cout << name << " is moving." << endl;
        return true;
    }
    bool sidestep() {
        cout << name << " sidestepped." << endl;
        return true;
    }
};

class Goblin : public enemy {
  public:
    Goblin() : enemy("Goblin", "手枪", 100, 10, 5, 2) {}
};
class Orc : public enemy {
  public:
    Orc() : enemy("Orc", "木棒") {}
};
class Dragon:public enemy{
 public:
    Dragon() : enemy("Dragon", "火焰吐息", 200, 50, 10, 1) {} // 初始化龙的属性
};
class Troll:public enemy{
  public:
  Troll():enemy("Troll","锤击"){}
};

class enemyCreator {
public:
    virtual std::unique_ptr<enemy> createEnemy() = 0;
};
class enemyCreatorOrc:public enemyCreator{
  std::unique_ptr<enemy> createEnemy(){
    return std::make_unique<Orc>();
  }
};
class enemyCreatorGoblin:public enemyCreator{
  std::unique_ptr<enemy> createEnemy(){
    return std::make_unique<Goblin>();
  }
};
class enemyCreatorDragon:public enemyCreator{
  std::unique_ptr<enemy> createEnemy(){ 
    return std::make_unique<Dragon>();
  }
};
class enemyCreatorTroll:public enemyCreator{
    std::unique_ptr<enemy> createEnemy(){
    return std::make_unique<Troll>();
  }
};


int main()
{
  enemyCreator* myCreator=new enemyCreatorDragon();
  unique_ptr<enemy> myEnemy_ptr=myCreator->createEnemy();
  myEnemy_ptr->attack();
  myEnemy_ptr->move();
  myEnemy_ptr->sidestep();
  return 0;
}
// 你可以通过注册机制或基于抽象类的多态机制，让每个敌人有自己独立的创建方式，而不是让工厂去硬编码每个敌人的创建细节。
// 对于这个我有点不太懂

