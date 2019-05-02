#ifndef _animal
#define _animal
#include <iostream>
using namespace std;

class Animal{
    int age;
    float cost;
    int n_babies;
    int foodMultiplier;
    float revenue;
    string name;
  public:
    Animal();
    Animal(int age, int cost, int n_babies, int foodMultiplier, int revenue, string name);
    void printAnimal();
    float getCost();
    float getRevenue();
    int getMult();
    void incAge();
    string getName();
    int getNbabies();
    int getAge();
    
};

#endif
