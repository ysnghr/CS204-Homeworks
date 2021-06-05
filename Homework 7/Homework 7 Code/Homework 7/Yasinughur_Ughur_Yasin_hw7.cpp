/*-------------------------------------------------------

Faculty of Engineering and Natural Sciences
CS204 Advanced Programming
Spring 2021
Homework 7 – Simulation of Factory Production Lines using Threads
Input: total of seven inputs are entered via keyboard

Author: Yasin Ughur

Date: 5/26/2021

---------------------------------------------------------*/

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <random>
#include <time.h>
#include "Yasinughur_Ughur_Yasin_hw7_HW7DynIntQueue.h"

using namespace std;

/* BEGIN: CODE TAKEN FROM ASSIGNMENT PDF FILE */
int random_range(const int & min, const int & max) {
 static mt19937 generator(time(0));
 uniform_int_distribution<int> distribution(min, max);
 return distribution(generator);
}
/* END: CODE TAKEN FROM ASSIGNMENT PDF FILE */


HW7DynIntQueue packagingQUEUE;
HW7DynIntQueue fillingQUEUE;
mutex fillerMutex, packingMutex, coutMutex;

int total_number_items;
int counter_filler_box, counter_packager_box = 0;
int min_time_producer, max_time_producer;
int min_time_filler, max_time_filler;
int min_time_packager, max_time_packager;

// producer thread function
void producer()
{
	for (int i = 0; i < total_number_items; i++)
	{
		int afterFilling;
		// getting random number between min and max and
		// sleeping thread this much
		this_thread::sleep_for(chrono::seconds(random_range(min_time_producer, max_time_producer))); 

		fillerMutex.lock();
			fillingQUEUE.enqueue(i+1);
			afterFilling = fillingQUEUE.getCurrentSize();
		fillerMutex.unlock();

		coutMutex.lock();
			/* BEGIN: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			/* BEGIN: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */
			cout <<"Producer has enqueued a new box "<< i+1 <<" to filling queue (filling queue size is " << afterFilling << "): "<< put_time(ptm,"%X") <<endl;
		coutMutex.unlock();

	}
}

// filler thread function
void filler(int fillerID)
{
	int getValueItem;

	while(counter_filler_box < total_number_items)
	{	
		fillerMutex.lock();
		if (!fillingQUEUE.isEmpty()) 
		{  
				fillingQUEUE.dequeue(getValueItem);
				int afterDeleting = fillingQUEUE.getCurrentSize();
				counter_filler_box++;
			fillerMutex.unlock();

			coutMutex.lock();
				/* BEGIN: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				/* END: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */
				cout << "Filler " << fillerID << " started filling the box "<< getValueItem <<" (filling queue size is "<< afterDeleting <<"): " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
			
			// getting random number between min and max and
			// sleeping thread this much
			this_thread::sleep_for(chrono::seconds(random_range(min_time_filler, max_time_filler))); 

			coutMutex.lock();
				// getting time
				tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				localtime_s(ptm, &tt); 
				cout << "Filler "<< fillerID <<" finished filling the box " << getValueItem <<": " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();

			packingMutex.lock();
				// adding the value which is dequeued from filling queue
				packagingQUEUE.enqueue(getValueItem);
				int afterFilling = packagingQUEUE.getCurrentSize();
			packingMutex.unlock();

			coutMutex.lock();
				tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				localtime_s(ptm, &tt); 
				cout << "Filler " << fillerID << " put box " << getValueItem << " into packaging queue (packaging queue size is " << afterFilling << "):" << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

		}
		else
		{
			fillerMutex.unlock();
		}
	}
}

void packaging(int packagerID)
{
	int getValueItem;
	while(counter_packager_box  < total_number_items)
	{	
		packingMutex.lock();
		if (!packagingQUEUE.isEmpty()) 
		{  
				packagingQUEUE.dequeue(getValueItem);
				int afterDeleting = packagingQUEUE.getCurrentSize();
				counter_packager_box++;
			packingMutex.unlock();

			coutMutex.lock();
				/* BEGIN: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				/* END: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */
				cout << "Packager "<< packagerID <<" started packaging the box "<< getValueItem <<" (packaging queue size is "<< afterDeleting <<"): " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
			
			// getting random number between min and max and
			// sleeping thread this much
			this_thread::sleep_for(chrono::seconds(random_range(min_time_packager, max_time_packager))); 

			coutMutex.lock();
				tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				localtime_s(ptm, &tt); 
				cout << "Packager "<< packagerID <<" finished packaging the box " << getValueItem <<": " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
		}
		else
		{
			packingMutex.unlock();
		}
	}
}

// getting each step min and max values
void getInputs(string text, int& min, int& max)
{
	cout << "Please enter the min-max waiting time range of " << text << ":" << endl;
	cout << "Min: ";
	cin >> min;
	cout << "Max: ";
	cin >> max;
}

int main()
{
	cout << "Please enter the total number of items: ";
	cin >> total_number_items;

	getInputs("producer",min_time_producer, max_time_producer);
	getInputs("filler workers",min_time_filler, max_time_filler);
	getInputs("packager workers",min_time_packager, max_time_packager);
	
	/* BEGIN: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	/* END: CODE TAKEN FROM LAB 13 ProducerConsumer.cpp */

	cout <<"Simulation starts "<< put_time(ptm,"%X") <<endl;


	thread thr0(producer);
	thread thr1(filler, 1);
	thread thr2(filler, 2);
	thread thr3(packaging, 1);
	thread thr4(packaging, 2);
	
	// starting each thread
	thr0.join();
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();

	// getting time where simulation ends
	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	localtime_s(ptm, &tt); 
	cout <<"End of the simulation ends: "<< put_time(ptm,"%X") <<endl;
	return 0;
}