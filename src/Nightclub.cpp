#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include "Nightclub.h"
#include "Semaphore.h"
using namespace std;

//TODO use a semaphore to ensure only MAX_PEOPLE threads
//can be in function inside(int id) concurrently
//all other threads must wait until there
//are fewer than MAX_PEOPLE threads in inside(int id)
//You MUST NOT use condition variables
//You MUST use semaphores

//TODO please also make any non-threadsafe APIs threadsafe

const int NUMB_THREADS =20;
const int MAX_PEOPLE =2;
std::vector<thread> thds;

Semaphore s_cnt(MAX_PEOPLE);
Semaphore s_binary(0);
mutex club;
mutex log_m;

void log(string s){
	cout<<s<<endl;
}

void inside(int id) {
	s_cnt.wait();
	{
		lock_guard<mutex> lck(club);
		//bask in noisy ambiance
		{
			lock_guard<mutex> lck(log_m);
			log(string("Thread "+to_string(id)+" is inside"));
		}
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}
	s_cnt.signal();
}

void nc(int id){
	{
		lock_guard<mutex> lck(log_m);
		log(string("Thread "+to_string(id)+" waiting to get in"));
	}
	inside(id);
	{
		lock_guard<mutex> lck(log_m);
		log(string("Thread "+to_string(id)+" has left"));
	}
}

//PLEASE DO NOT CHANGE THIS FUNCTION
void Nightclub(){
	for (int j=0;j<NUMB_THREADS;j++){
			thds.push_back( thread(nc,j));
		}

	for (auto& thd:thds)
		thd.join();
}
