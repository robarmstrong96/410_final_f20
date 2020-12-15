/*
 * Semaphore.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: keith
 */
#include <iostream>
#include "Semaphore.h"
using namespace std;

Semaphore::Semaphore(int cnt) :
		count(cnt) {
}
Semaphore::~Semaphore() {
}

void Semaphore::wait() {
	unique_lock<mutex> mlk(m);

	//if you equal 0 you wait
	while(count <= 0)
			cv.wait(mlk);
	--count;
}
void Semaphore::signal() {
	{
		unique_lock<mutex> mlk(m);
		++count;
	}
	//if a bunch of threads are blocked
	//there is no point in calling notify_all
	//since the first to wake in wait()
	//will decrement the count and then
	//any other threads that wake will
	//see count==0 and will go back to sleep
    cv.notify_one();	
}

