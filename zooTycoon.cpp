/*********************************************************************
** Program Filename:   zooTycoon.cpp
** Author: Adam Conrad
** Date: 2/18/19
** Description: A game where users operate a zoo. They can buy animals of three different species.
** Input: Type and amount of animals to buy, type of food to use.
** Output: Current day, available balance, price of food, amount of animals, net income for a single day, and special event information.
*********************************************************************/
#include <iostream>
#include "animal.hpp"
#include "monkey.hpp"
#include "otter.hpp"
#include "sloth.hpp"
#include "zoo.hpp"
using namespace std;

int main(){
  Zoo z;
  while(z.getBalance() > 0){
    int init = z.getBalance();
    z.incDay();//increment day
    z.changePrice();//update price of food
    z.printZoo();
    string str = "Would you like to buy an animal? (y/n)";
    char c = z.get_input(str, 'y', 'n');
    if ( c == 'y'){
      z.buyAnimal();//buy animals
    }
    z.buyFood();  //pay for food
    z.specialEvent();            //special event
    z.collectBread();  //collect bread
    int final = z.getBalance();
    int net = final - init;
    cout<<"Today's earnings: $"<<net<<endl;
  }
  cout<<"Your zoo went bankrupt. Game over."<<endl;
return 0;
}
