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

condition_variable cv;
mutex m;
mutex print;

void putonsocks(){
	{
		lock_guard<mutex> lck(print);
		cout<<"socks on"<<endl;
		socks_are_on=true;
	}
	cv.notify_all();
}

void putonshoes() {
	unique_lock<mutex> lck(m);
	while(!socks_are_on)
		cv.wait(lck);
	{
		lock_guard<mutex> lck(print);
		cout<<"shoes on"<<endl;
		shoes_are_on=true;
	}
	cv.notify_all();
}

void putoncoat(){
	unique_lock<mutex> lck(m);
	while(!shoes_are_on)
		cv.wait(lck);
	{
		lock_guard<mutex> lck(print);
		cout<<"coat on"<<endl;
		coat_is_on=true;		
	}
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
