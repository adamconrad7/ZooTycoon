#include "animal.hpp"
#include <iostream>
using namespace std;

/*********************************************************************
** Function:  Default and paramterized constructors for Animal class.
** Description: Constructs an Animal object with either default values or specific parameters passed.
** Parameters:  age, cost, number of babies, revenue generated, food cost multiplier, and name.
** Pre-Conditions: n/a
** Post-Conditions: Animal object will be instantiated.
*********************************************************************/
Animal::Animal(){
  this->age = 0;
  this->cost = 0;
  this->n_babies = 0;
  this->foodMultiplier = 0;
  this->revenue = 0;
}

Animal::Animal(int age, int cost, int n_babies, int foodMultiplier, int revenue, string name) : age(age), cost(cost), n_babies(n_babies), foodMultiplier(foodMultiplier), revenue(revenue), name(name){}

/*********************************************************************
** Function: printAnimal
** Description:  Prints all relevant information of an animal object.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Animal::printAnimal(){
  //int a = this->age;
  cout<<"This animal is "<< this->age <<" days old."<<endl;
  cout<<"This animal costs $"<< this->cost <<"."<<endl;
  cout<<"This animal has "<< this->n_babies <<" babies."<<endl;
  cout<<"This animal's food costs " <<this->foodMultiplier <<" times as much as base."<<endl;
  cout<<"This animal generates $"<< this->revenue <<" in revenue."<<endl;
}

/*********************************************************************
** Function: incAge
** Description: Increments age of an animal object by a single day.
** Parameters: n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
void Animal::incAge(){
  age++;
}

/*********************************************************************
** Function: getCost/Revenue/Mult/Name/Nbabies/Age
** Description: Returns specified field of an animal object.
** Parameters:  n/a
** Pre-Conditions: n/a
** Post-Conditions: n/a
*********************************************************************/
float Animal::getCost(){
  return cost;
}

float Animal::getRevenue(){
  return revenue;
}

int Animal::getMult(){
  return foodMultiplier;
}

string Animal::getName(){
  return name;
}

int Animal::getNbabies(){
  return n_babies;
}

int Animal::getAge(){
  return age;
}
