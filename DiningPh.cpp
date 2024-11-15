#include<iostream>
#include<thread>
#include<mutex>
#include<semaphore.h>
#include<unistd.h>
#include<vector>

using namespace std;

mutex mut;
const int PHIL = 5;
sem_t sem[PHIL];

void philosopher(int id)
{
	while(true)
	{
		{
			lock_guard<mutex> lock(mut);
			cout << "philosopher : " << id << " is eating " << endl;
		}
		
		sem_wait(&sem[id]);
		sem_wait(&sem[(id + 1) % PHIL]);
		
		{
			lock_guard<mutex> lock(mut);
			cout << "philosopher : " << id << " is thinking " << endl;
		}
		
		sem_post(&sem[id]);
		sem_post(&sem[(id + 1) % PHIL]);
	}
}
int main()
{
	for(int i = 0; i < PHIL; i++)
	{
		sem_init(&sem[i], 0, 1);
	}
	
	vector<thread> philos;
	for(int i = 0; i < PHIL; i++)
	{
		philos.push_back(thread(philosopher, i));
	}
	
	for(auto &ph : philos) ph.join();
	
	for(int i = 0; i < PHIL; i++)
	{
		sem_destroy(&sem[i]);
	}

}