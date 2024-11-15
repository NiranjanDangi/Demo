#include<iostream>
#include<unistd.h>
#include<thread>
#include<semaphore.h>
#include<mutex>
#include<cstdlib>

using namespace std;

const int BUFFERSIZE = 5;
int buffer[BUFFERSIZE];

int count, in, out = 0;

mutex bufMut;
sem_t notEmpty;
sem_t notFull;

int producer(int id)
{
	while(true)
	{
		int item = rand() % 100;
		sem_wait(&notFull);
		{
		 	lock_guard<mutex> lock(bufMut);
		 	buffer[in] = item;
		 	in = (in - 1) % BUFFERSIZE;
		 	count++;
		 	cout << "producer : " << id << "resource : " << item << endl;
		 
		 
		}
		sem_post(&notEmpty);
	}
}
int consumer(int id)
{
	while(true)
	{
		sem_wait(&notEmpty);
		
		int item;
		{
			lock_guard<mutex> lock(bufMut);
			item = buffer[out];
			out = (out - 1) % BUFFERSIZE;
			count--;
			cout << "consumer : " << id << " resource : " << item << endl;
		}
		
		sem_post(&notFull);
	}
}
int main()
{
	sem_init(&notEmpty, 0, BUFFERSIZE);
	sem_init(&notFull, 0, 0);
	
	thread producers[2] = {thread(producer, 1), thread(producer, 2)};
	thread consumers[2] = {thread(consumer, 1), thread(consumer, 2)};
	
	for(auto &prod : producers) prod.join();
	for(auto &con : consumers) con.join();
	
	sem_destroy(&notEmpty);
	sem_destroy(&notFull);
}







