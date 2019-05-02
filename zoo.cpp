#include "zoo.hpp"
#include <time.h> // for time
#include <stdlib.h> // for rand
#include <math.h> //for fmod
#include <iostream>
#include <random>
using namespace std;

/*********************************************************************
** Function: Zoo constructor
** Description: Initializes general fields of Zoo class.
** Parameters:  n/a
** Pre-Conditions: n/a
** Post-Conditions:  n/a
*********************************************************************/
Zoo::Zoo(){
  bankAccount = 100000;
  foodCost = 50;
  n_days = 0;
  foodType = 'r';
}

/*********************************************************************
** Function: Zoo destructor
** Description: Frees dynamically allocated memory for animal arrays.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
Zoo::~Zoo(){
  for (int i = 0; i<allAnimals.size(); i++){
    delete allAnimals[i];
  }
}

/*********************************************************************
** Function: incDay
** Description: Increments day count, and ages each animal a single day.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Every animals is one day older.
*********************************************************************/
void Zoo::incDay(){
  n_days++;
  if(mStore.size() > 0){
    for(int i=0; i<mStore.size(); i++){
      mStore.at(i)->incAge();
    }
  }
  if(oStore.size() > 0){
    for(int i=0; i<oStore.size(); i++){
      oStore.at(i)->incAge();
    }
  }
  if(sStore.size() > 0){
    for(int i=0; i<sStore.size(); i++){
      sStore.at(i)->incAge();
    }
  }
}

/*********************************************************************
** Function: changePrice
** Description: Changes cost of food to a random value 75-125% of the previous day's cost.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Cost of food will be updated.
*********************************************************************/
void Zoo::changePrice(){
  srand(time(NULL));
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_real_distribution<> distr(.75, 1.25); // define the range
  foodCost = foodCost * distr(eng);
}

/*********************************************************************
** Function: printZoo
** Description: Prints all relevant information about zoo.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Zoo::printZoo(){
  int mAdults = countadults(1);
  int mBabes = countbabes(1);
  int oAdults = countadults(2);
  int oBabes= countbabes(2);
  int sAdults = countadults(3);
  int sBabes = countbabes(3);

  cout<<"\n"<<endl;
  cout<<"############# Day "<< n_days <<" ################"<<endl;
  cout<<"Available balance: $"<<bankAccount<<endl;
  cout<<"Food price: $"<< foodCost<<endl;

  cout<<"You have "<< mStore.size()<<" monkeys:"<<endl;
  cout<<"\t"<<" "<<mAdults<<" adults and "<<mBabes<<" babies"<<endl;

  cout<<"You have "<< oStore.size()<<" sea otters:"<<endl;
  cout<<"\t"<<" "<<oAdults<<" adults and "<<oBabes<<" babies"<<endl;

  cout<<"You have "<< sStore.size()<<" sloths:"<<endl;
  cout<<"\t"<<" "<<sAdults<<" adults and "<<sBabes<<" babies"<<endl;


}

/*********************************************************************
** Function: buyAnimal
** Description: Asks user if they want to buy an animal, and if yes which type and how many. It then stores said animal(s) into vectors.
** Parameters: n/a
** Pre-Conditions: Vector of pointers to animals must be instantiated.
** Post-Conditions: Dynamically allocated animal will be added to a vector of it's class's
pointer as well as to a vector of pointers to the parent Animal class.
*********************************************************************/
void Zoo::buyAnimal(){
  string str = "Would you like to buy a (m)onkey, (o)tter, or (s)loth?";
  char picc = this->get_input(str, 'm', 'o', 's');
  string again = "Would you like to buy another one? (y/n)";
  char repeat = get_input(again, 'y', 'n');
  int l = 1;
  if(repeat == 'y'){
    l = 2;
  }
  for(int i =0; i<l; i++){
    switch (picc){
      case 'm':
        {
          Monkey* m = new Monkey;
          mStore.push_back(m);
          allAnimals.push_back(m);
          bankAccount -= m->getCost();
          break;
        }
      case 'o':
        {
          Otter* o = new Otter;
          oStore.push_back(o);
          allAnimals.push_back(o);
          bankAccount -= o->getCost();
          break;
        }
      case 's':
        {
          Sloth* s = new Sloth;
          sStore.push_back(s);
          allAnimals.push_back(s);
          bankAccount -= s->getCost();
          break;
        }
    }
  }
}

/*********************************************************************
** Function:  buyFood
** Description: Prompts user for whic type of food they want to buy, and subtracts the cost of that food times the multiplier for each animal owned from available balance.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions:  n/a
*********************************************************************/
void Zoo::buyFood(){
  int m = 0,s = 0,o = 0;
  if(mStore.size() > 0){
     m = mStore.size() * mStore.front()->getMult() * foodCost;
  }
  if(oStore.size() > 0){
    o = oStore.size() * oStore.front()->getMult() * foodCost;
  }
  if(sStore.size() > 0){
    s = sStore.size() * sStore.front()->getMult() * foodCost;
  }
  int n = m + o + s;
  cout<<" You can buy more expensive food to decrease the chance of your animals getting sick, or buy cheaper food and increase their risk."<<endl;
  string str = "Do you want (p)remium, (r)egular, or (c)heap food?";
  char choice = get_input(str, 'p', 'r', 'c');
  float mult;
  switch(choice){
    case 'p':
      {
        mult = 2;
        break;
      }
    case 'r':
      {
        mult = 1;
        break;
      }
    case 'c':
      {
        mult = .5;
        break;
      }
  }
  foodType = choice;
  bankAccount -= n * mult;
}

/*********************************************************************
** Function: getBalance
** Description: Returns available balance.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
float Zoo::getBalance(){
  return bankAccount;
}

/*********************************************************************
** Function: specialEvent
** Description: Randomly chooses one of four events and takes into account current food type for sickness probability.
** Parameters:  n/a
** Pre-Conditions: n/a
** Post-Conditions:  n/a
*********************************************************************/
void Zoo::specialEvent(){
  int l;
  int h;
  switch (foodType){
    case 'p':
      {
        l=2;
        h=8;
        break;
      }
    case 'r':
      {
        l=1;
        h=4;
        break;
      }
    case 'c':
      {
        l=1;
        h=5;
        break;
      }
  }
  srand(time(NULL));
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(l, h);
  int n = distr(eng);
  if(allAnimals.size()>0){
      switch(n){
        case 1:
        case 5:
          {
            cout<<"One of your animals got sick!"<<endl;
            sick();
            break;
          }
        case 2:
        case 6:
          {
            babies();
            break;
          }
        case 3:
        case 7:
          {
            cout<<"A boom in attendance generates you extra cash!"<<endl;
            boom();
            break;
          }
        case 4:
        case 8:
          {
            cout<<"It was a slow day at the Zoo."<<endl;
            break;
          }
      }
    }else{
      cout<<"Your zoo is empty."<<endl;
    }
}

/*********************************************************************
** Function:  sick
** Description: Randomly chooses an animal and subtracts specified cost from available balance, or kills animal if funds are insufficient.
** Parameters:  n/a
** Pre-Conditions: n/a
** Post-Conditions: Sick animal is removed from vectors if user doesn't have enough money to heal it.
*********************************************************************/
void Zoo::sick(){
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, allAnimals.size()-1); // define the range from 0 to the index of the last animal
    int index = distr(rd);
    int price = allAnimals[index]->getCost() / 2;
    if(allAnimals[index]->getAge() < 30 ){
      price = price * 2;
    }
    if(price < bankAccount){
      cout<<"You paid $"<< price <<" to heal your "<< allAnimals[index]->getName() <<"."<<endl;
      bankAccount -= price;
    }else{
      cout<<"You do not have enough money to heal your "<< allAnimals[index]->getName() <<"."<<" It has died."<<endl;
      vector<Animal*>::iterator itr = allAnimals.begin() + index;
      allAnimals.erase(itr);
      int id = allAnimals[index]->getNbabies();
      switch(id){//NEED TO fix segfault with no animals
        case 1:
          {
            for(int i = 0; i<mStore.size(); i++){
              vector<Monkey*>::iterator itr = mStore.begin() + i;
              if(mStore[i] == allAnimals[index]){
                  mStore.erase(itr);
              }
            }
          }
        case 2:
          {
            for(int i = 0; i<oStore.size(); i++){
              vector<Otter*>::iterator itr = oStore.begin() + i;
              if(oStore[i] == allAnimals[index]){
                  oStore.erase(itr);
              }
            }
          }
        case 3:
          {
          for(int i = 0; i<sStore.size(); i++){
            vector<Sloth*>::iterator itr = sStore.begin() + i;
            if(sStore[i] == allAnimals[index]){
                sStore.erase(itr);
            }
          }
        }
      }
    }

  // * One randomly chosen animal gets sick.
  // In order to care for the sick animal, the owner must pay an amount equal to half the initial cost of an animal of the same species as the sick animal
  // (e.g. a sick monkey costs half of $15,000, i.e. $7,500).  If the owner has enough money to cover this cost, it is subtracted from their bank account.
  //  If they do not have enough money, then the sick animal dies and is removed from the zoo.

}

/*********************************************************************
** Function: babies
** Description: Randomly selects an adult animal and creates a new amount of of that animal based on how many babies that animal has.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Zoo::babies(){
  srand(time(NULL));
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, allAnimals.size()-1); // define the range from 0 to the index of the last animal
  int index = distr(rd);
  int n = allAnimals[index]->getNbabies();
  cout<<"One of your "<< allAnimals[index]->getName()<<"s gave birth to "<< n <<" baby(s)!"<<endl;
  for(int i = 0; i<n; i++){
    switch(n){
      case 1:
        {
            Monkey* m = new Monkey(0);
            mStore.push_back(m);
            allAnimals.push_back(m);
            bankAccount -= m->getCost();
          break;
        }
      case 2:
        {
          Otter* o = new Otter(0);
          oStore.push_back(o);
          allAnimals.push_back(o);
          bankAccount -= o->getCost();
          break;
        break;
        }
      case 3:
        {
          Sloth* s = new Sloth(0);
          sStore.push_back(s);
          allAnimals.push_back(s);
          bankAccount -= s->getCost();
          break;
        break;
        }
    }
  }
}

/*********************************************************************
** Function: boom
** Description: Adds a random amount of money between $250-$500 to balance for each monkey owned.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: Balance is increased if monkeys are owned.
*********************************************************************/
void Zoo::boom(){
  for(int i=0; i<allAnimals.size(); i++){
    if(allAnimals[i]->getNbabies() == 1){
      srand(time(NULL));
      std::random_device rd;
      std::mt19937 eng(rd());
      std::uniform_int_distribution<> distr(250, 500);
      bankAccount += distr(eng);
    }
  }
}


/*********************************************************************
** Function:  collectBread
** Description:  Counts revenue generated by each animal and adds it to available balance.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions:  n/a
*********************************************************************/
void Zoo::collectBread(){
    int cash = 0;
  for(int i=0; i<allAnimals.size(); i++){
    if(allAnimals[i]->getAge() < 30){
      cash += allAnimals[i]->getRevenue() * 2;
    }else{
      cash += allAnimals[i]->getRevenue();
    }
  }

  bankAccount += cash;
}

/*********************************************************************
** Function: countadults/babes
** Description:  Counts every animal of specified age.
** Parameters:  n/a
** Pre-Conditions: n/a
** Post-Conditions:  n/a
*********************************************************************/
int Zoo::countadults(int id){
  int adult = 0;
  switch (id){
    case 1:
      {
        for(int i=0; i<mStore.size(); i++){
          if(mStore[i]->getAge() > 1095){
            adult++;
          }
        }
        break;
      }
    case 2:
      {
        for(int i=0; i<oStore.size(); i++){
          if(oStore[i]->getAge() > 1095){
            adult++;
          }
        }
        break;
      }
    case 3:
      {
        for(int i=0; i<sStore.size(); i++){
          if(sStore[i]->getAge() > 1095){
            adult++;
          }
        }
        break;
      }
  }
  return adult;
}

int Zoo::countbabes(int id){
    int adult = 0;
    switch (id){
      case 1:
        {
          for(int i=0; i<mStore.size(); i++){
            if(mStore[i]->getAge()  < 30){
              adult++;
            }
          }
          break;
        }
      case 2:
        {
          for(int i=0; i<oStore.size(); i++){
            if(oStore[i]->getAge()  < 30){
              adult++;
            }
          }
          break;
        }
      case 3:
        {
          for(int i=0; i<sStore.size(); i++){
            if(sStore[i]->getAge() < 30){
              adult++;
            }
          }
          break;
        }
    }
    return adult;
}


/*********************************************************************
** Function: getAnimals/Otters/Monkeys/Sloths
** Description: Returns vector of specified type (Animals/Otters/Monkeys/Sloths).
** Parameters:  none
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
vector<Animal*> Zoo::getAnimals(){
  return allAnimals;
}

vector<Otter*> Zoo::getOtters(){
  return oStore;
}

vector<Sloth*> Zoo::getSloths(){
  return sStore;
}

vector<Monkey*> Zoo::getMonkeys(){
  return mStore;
}

/*********************************************************************
** Function: get_input
** Description: Prompts user with a string and validates response. Overloaded function for using either two or three responses.
** Parameters: String that is the prompt to user, as well as two or three acceptable responses to said prompt.
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
char Zoo::get_input(string prompt, char c1, char c2, char c3){
  bool flag = false;
  char in;
  do{
    cout<<prompt<<endl;
    cin>> in;
    if(in != c1 && in != c2 && in != c3){
      cout<<"Please enter a valid choice."<<endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}

char Zoo::get_input(string prompt, char c1, char c2){
  bool flag = false;
  char in;
  do{
    cout<<prompt<<endl;
    cin>> in;
    if(in != c1 && in != c2){
      cout<<"Please enter a valid choice."<<endl;
      flag = true;
    }else{
      flag = false;
    }
  }while(flag);
  return in;
}
