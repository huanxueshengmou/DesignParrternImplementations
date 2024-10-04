#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <functional>

using namespace std;

class enemy {
    string name;
    string weapons;
    int HP;
    int harm;
    int speed;
    int attackFrequency;

public:
    enemy(string n = "Unknown Enemy", string w = "拳头", int hp = 100, int h = 10, int s = 5, int af = 1) 
        : name(n), weapons(w), HP(hp), harm(h), speed(s), attackFrequency(af) {}

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
    Dragon() : enemy("Dragon", "火焰吐息", 200, 50, 10, 1) {}
};
class Troll:public enemy{
public:
    Troll():enemy("Troll","锤击"){}
};

// enemyFactory 使用注册机制来动态创建敌人
class enemyFactory {
public:
    using creatorFunc = function<unique_ptr<enemy>()>;

    void registerEnemy(string type, creatorFunc creator) {
        creators[type] = creator;
    }

    unique_ptr<enemy> createEnemy(const string& type) {
        if (creators.find(type) != creators.end()) {
            return creators[type]();
        }
        return nullptr;
    }

private:
    map<string, creatorFunc> creators;  // 用来存储敌人的创建函数
};

int main()
{
    enemyFactory factory;
    
    // 注册不同类型的敌人
    factory.registerEnemy("Goblin", []() { return make_unique<Goblin>(); });
    factory.registerEnemy("Orc", []() { return make_unique<Orc>(); });
    factory.registerEnemy("Dragon", []() { return make_unique<Dragon>(); });
    factory.registerEnemy("Troll", []() { return make_unique<Troll>(); });
    
    // 动态创建敌人
    unique_ptr<enemy> myEnemy = factory.createEnemy("Dragon");
    if (myEnemy) {
        myEnemy->attack();
        myEnemy->move();
        myEnemy->sidestep();
    }

    return 0;
}
