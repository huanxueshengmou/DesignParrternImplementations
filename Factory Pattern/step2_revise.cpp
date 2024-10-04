#include <iostream>
#include <memory>
#include <string>
#include <vector>
//抽象工厂模式的重点是创建**“产品族”**，也就是一组相关的对象。
//通过创建不同的工厂子类，你能够生成不同的产品组，而无需依赖 if-else 判断具体生成哪个产品。
using namespace std;

// 敌人基类
class enemy
{
  string name;
  int HP;

public:
  enemy(string n, int hp) : name(n), HP(hp) {}
  virtual void attack() = 0;
  virtual ~enemy() = default;
};

// 武器基类
class weapon
{
public:
  virtual void use() = 0;
  virtual ~weapon() = default;
};

// 具体敌人类
class Goblin : public enemy
{
public:
  Goblin() : enemy("Goblin", 100) {}
  void attack() override
  {
    cout << "Goblin attacks with claws!" << endl;
  }
};

class Dragon : public enemy
{
public:
  Dragon() : enemy("Dragon", 500) {}
  void attack() override
  {
    cout << "Dragon breathes fire!" << endl;
  }
};

// 具体武器类
class Sword : public weapon
{
public:
  void use() override
  {
    cout << "Sword slashes!" << endl;
  }
};

class FireBreath : public weapon
{
public:
  void use() override
  {
    cout << "Fire breath scorches!" << endl;
  }
};

// 抽象工厂接口
class EnemyFactory
{
public:
  virtual unique_ptr<enemy> createEnemy() = 0;
  virtual unique_ptr<weapon> createWeapon() = 0;
  virtual ~EnemyFactory() = default;
};

// 普通敌人工厂
class OrdinaryFactory : public EnemyFactory
{
public:
  unique_ptr<enemy> createEnemy() override
  {
    return make_unique<Goblin>();
  }
  unique_ptr<weapon> createWeapon() override
  {
    return make_unique<Sword>();
  }
};

// BOSS敌人工厂
class BossFactory : public EnemyFactory
{
public:
  unique_ptr<enemy> createEnemy() override
  {
    return make_unique<Dragon>();
  }
  unique_ptr<weapon> createWeapon() override
  {
    return make_unique<FireBreath>();
  }
};

// 客户端代码
int main()
{
  // 使用普通敌人工厂
  unique_ptr<EnemyFactory> factory = make_unique<OrdinaryFactory>();
  unique_ptr<enemy> myEnemy = factory->createEnemy();
  unique_ptr<weapon> myWeapon = factory->createWeapon();

  myEnemy->attack();
  myWeapon->use();

  // 使用BOSS敌人工厂
  factory = make_unique<BossFactory>();
  myEnemy = factory->createEnemy();
  myWeapon = factory->createWeapon();

  myEnemy->attack();
  myWeapon->use();

  return 0;
}
