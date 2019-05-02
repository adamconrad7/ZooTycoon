#ifndef _zoo
#define _zoo
#include <string>
#include <vector>
#include "animal.hpp"
#include "monkey.hpp"
#include "otter.hpp"
#include "sloth.hpp"
using namespace std;
class Zoo{
    float bankAccount;
    float foodCost;
    int n_days;
    vector<Monkey*> mStore;
    vector<Otter*> oStore;
    vector<Sloth*> sStore;
    vector<Animal*> allAnimals;
    char foodType;
  public:
    Zoo();
    ~Zoo();
    void incDay();
    void changePrice();
    void printZoo();
    void buyAnimal();
    void collectBread();
    char get_input(string prompt, char c1, char c2, char c3);
    char get_input(string, char, char);
    void buyFood();
    float getBalance();
    void specialEvent();
    void sick();
    void babies();
    void boom();
    int countbabes(int);
    int countadults(int);

    vector<Animal*> getAnimals();
    vector<Monkey*> getMonkeys();
    vector<Otter*>  getOtters();
    vector<Sloth*>  getSloths();
};

#endif
