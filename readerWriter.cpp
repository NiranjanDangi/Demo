#include<iostream>
#include<thread>
#include<semaphore.h>
#include<mutex>

using namespace std;

sem_t resourceSem;
mutex readerMut;
int readerCount = 0;
int sharedResource = 0;

void reader(int id)
{
	while(true)
	{
		{
			lock_guard<mutex> lock(readerMut);
			readerCount++;
			if(readerCount == 1)
			{
				sem_wait(&resourceSem);
			}
		}
		
		cout << "reader : " << id << " resource : " << sharedResource << endl;
		
		{
			lock_guard<mutex> lock(readerMut);
			readerCount--;
			if(readerCount == 0)
			{
				sem_post(&resourceSem);
			}
		}
	}
}

void writer(int id)
{
	while(true)
	{
		sem_wait(&resourceSem);
		
		sharedResource++;
		
		cout << "writer : " << id << " resource : " << sharedResource << endl;
		
		sem_post(&resourceSem);
	}
}

int main()
{
	sem_init(&resourceSem, 0, 1);
	
	thread readers[3], writers[2];
	for(int i = 0; i < 3; i++)
	{
		readers[i] = thread(reader, i + 1);
	}
	
	for(int i = 0; i < 2; i++)
	{
		writers[i] = thread(writer, i + 1);
	}
	
	
	for(auto &read : readers) read.join();
	for(auto &write : writers) write.join();
	
	sem_destroy(&resourceSem);
}