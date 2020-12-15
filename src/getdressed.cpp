#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include "getdressed.h"
using namespace std;

//TODO the order to get dressed to go out is to call
//putonsocks() then  putonshoes() then putoncoat()
//you must fill code in below to enforce this order
//regardless of which thread starts first.
//You MUST use condition variables
//You MUST NOT use semaphores

//TODO please also make any non-threadsafe APIs threadsafe

//PLEASE DO NOT MAKE THESE ATOMICS
bool socks_are_on =false;
bool shoes_are_on =false;
bool coat_is_on =false;

void putonsocks(){
	cout<<"socks on"<<endl;
}

void putonshoes(){
	cout<<"shoes on"<<endl;
}

void putoncoat(){
	cout<<"coat on"<<endl;
}

//PLEASE DO NOT CHANGE THIS FUNCTION
void getdressed(){
	//put on some clothes
	std::thread t1(putoncoat);
	std::thread t2(putonshoes);
	std::thread t3(putonsocks);

	t1.join();
	t2.join();
	t3.join();
}


