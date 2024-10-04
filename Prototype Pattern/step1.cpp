#include <iostream>
#include "my_print.cpp"
#include <string>
#include <vector>
using std::vector;
using std::string;
using namespace std;

class Character {
  protected:
  string name;
  int level;
  vector<string> skills;
  public:
  Character(
    string name,
    int level,
    vector<string> skills
  ){
    this->name=name;
    this->level=level;
    this->skills=skills;
  }
  virtual string getName(){
    return name;
  }
  virtual vector<string> getSkills(){
    return skills;
  }
  virtual int getLevel(){
    return level;
  }
  virtual Character* clone() {
    return new Character(name, level, skills);  
  }
};
class huanxue:public Character{
  public:
  huanxue(
  string name
  ,int level
  ,vector<string> skills
  ,string sex):Character(name, level, skills){
    this->sex=sex;
    this->name=name;
  }
  protected:
  string sex="male";
  string name="huanxue";
  public:
  huanxue* clone() {
    return new huanxue(name, level, skills,sex);  
  }
  string getSex(){
    return sex;
  }
};
int main(){
  Character * character=new Character("huanxue",12,{"sing","run","eat"});
  Character* cloneCharacter=character->clone();
  huanxue * myhuanxue=new huanxue("huanxue",12,{"sing","run","eat"},"male");
  huanxue* clonehuanxue=myhuanxue->clone();
  
  print(cloneCharacter->getLevel());
  print(cloneCharacter->getName());
  print(cloneCharacter->getSkills());

  print(clonehuanxue->getLevel());
  print(clonehuanxue->getName());
  print(clonehuanxue->getSkills());
  print(clonehuanxue->getSex());
}