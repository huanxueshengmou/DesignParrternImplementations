
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class enemy
{
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
  bool attack()
  {
    cout << name + " did " + to_string(harm) + " points of damage with his " + weapons << endl;
    return true;
  }
  bool move()
  {
    cout << name << " is moving." << endl;
    return true;
  }
  bool sidestep()
  {
    cout << name << " sidestepped." << endl;
    return true;
  }
};

class Goblin : public enemy
{
public:
  Goblin() : enemy("Goblin", "手枪", 100, 10, 5, 2) {}
};
class Orc : public enemy
{
public:
  Orc() : enemy("Orc", "木棒") {}
};
class Dragon : public enemy
{
public:
  Dragon() : enemy("Dragon", "火焰吐息", 200, 50, 10, 1) {} // 初始化龙的属性
};
class Troll : public enemy
{
public:
  Troll() : enemy("Troll", "锤击") {}
};

class EnemyFactory
{
public:
  virtual std::vector<std::unique_ptr<enemy>> &createEnemy() = 0;
};
class FactoryBoss : public EnemyFactory
{
  std::vector<std::unique_ptr<enemy>> enemy_list;

public:
  std::vector<std::unique_ptr<enemy>> &createEnemy()
  {
    std::unique_ptr<enemy> enemy_3 = std::make_unique<Dragon>();
    enemy_list.push_back(move(enemy_3));
    return enemy_list;
  }
};
class FactoryOrdinary : public EnemyFactory
{
  std::vector<std::unique_ptr<enemy>> enemy_list;
  std::vector<std::unique_ptr<enemy>> &createEnemy()
  {
    std::unique_ptr<enemy> enemy_1 = std::make_unique<Orc>();
    std::unique_ptr<enemy> enemy_2 = std::make_unique<Goblin>();
    std::unique_ptr<enemy> enemy_3 = std::make_unique<Troll>();
    enemy_list.push_back(move(enemy_1));
    enemy_list.push_back(move(enemy_2));
    enemy_list.push_back(move(enemy_3));
    return enemy_list;
  }
};
int main()
{
  EnemyFactory *enemy_factor_boss = new FactoryBoss();
  EnemyFactory *enemy_factor_ordinary = new FactoryOrdinary();
  for (auto &factor_ptr : enemy_factor_boss->createEnemy())
  {
    std::cout << factor_ptr->attack();
  }
  for (auto &factor_ptr : enemy_factor_ordinary->createEnemy())
  {
    std::cout << factor_ptr->attack();
  }
}
//关于抽象工厂如何生产产品我还是有点，迷糊，事实上我想利用ifelse语句来实现指定的
//类的一个创建，但是呢这样不就是和简单工厂模式一样没有区别了吗，所以我实在想不出来如何
//不通过ifelse来具体实现一个指定的类。所以我直接输出了一个系列的类。我感觉我对于抽象工厂的把握还是不够多
//使用我还是想看看如果是你会如何实现这个功能。
