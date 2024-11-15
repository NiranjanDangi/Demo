#include<iostream>
#include<fstream>
#include<unistd.h>
#include<cstring>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/fcntl.h>
#include<sys/stat.h>

using namespace std;

void proc();
void comm();
void info();
void file();


int main()
{
	int op;
	while(true)
	{
		cout << "1.proc\n2.comm\n3.info\n4.file\n5.exit\n" << endl;
		cout << "Enter operation " << endl;
		cin >> op;
		
		switch(op)
		{
		case 1:
			proc();
			break;
		case 2:
			comm();
			break;
		case 3:
			info();
			break;
		case 4:
			file();
			break;
		case 5:
			exit(0);
			break;
		}
	}
	return 0;
}


void proc()
{
	pid_t pid = fork();
	
	if(pid == 0)
	{
		cout << "child proc : " << pid << endl;
	}
	else if(pid > 0)
	{
		cout << "parent proc : " << pid << endl;
		wait(nullptr);
	}
	else
	{
		perror("fork");
	}
}

void comm()
{
	int fd[2];
	const char write_msg[] = "hellow";
	char read_msg[100];
	
	pid_t pid = fork();
	
	if(pid == 0)
	{
		close(fd[0]);
		write(fd[1], write_msg, strlen(write_msg) + 1);
		close(fd[1]);
	}
	else if(pid > 0)
	{
		close(fd[1]);
		read(fd[0], read_msg, sizeof(read_msg));
		close(fd[0]);
	}
	else
	{
		perror("fd");
	}
	
}

void info()
{
	pid_t pid = getpid();
	cout << "pid : " << pid << endl;
	pid_t ppid = getppid();
	cout << "ppid : " << ppid << endl;
	uid_t uid = getuid();
	cout << "uid : " << uid << endl;
	gid_t gid = getgid();
	cout << "gid : " << gid << endl;
	
	
}
void file()
{
	int fd;
	int buffer[100];
	
	fd = open("ex.txt", O_RDWR | O_CREAT , S_IRUSR | S_IWUSR);
	
	if(fd == -1)
	{
		perror("fd");
	}
	
	if(write(fd, "hello/n", 6) == -1)
	{
		perror("write");
	}
	
	lseek(fd, 0, SEEK_SET);
	
	if(read(fd, buffer, 100) == -1)
	{
		perror("read");
	}
	
	if(close(fd) == -1)
	{
		perror("close");
	}
	
	if(link("ex.txt", "ex2.txt") == -1)
	{
		perror("link");
	}
	
	if(unlink("ex2.txt") == -1)
	{
		perror("unlink");
	}
	
	struct stat filestat;
	
	if(stat("ex.txt", &filestat) < 0)
	{
		perror("stat");
	}
}



