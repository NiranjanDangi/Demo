#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void createZombieProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid > 0) {  // Parent process
        cout << "Parent process: Zombie process created. PID = " << pid << endl;
        sleep(10);
    } else {  // Child process
        cout << "Child process exiting to become zombie." << endl;
        exit(0);
    }
}

void createOrphanProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid > 0) {  // Parent process
        cout << "Parent process exiting to create orphan process." << endl;
        exit(0);
    } else {  // Child process
        sleep(5);
        cout << "Child process (orphan) continuing after parent termination. PID = " << getpid() << endl;
    }
}

void sumEvenOdd(const int arr[], int size) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid > 0) {  // Parent process
        int evenSum = 0;
        for (int i = 0; i < size; i++) if (arr[i] % 2 == 0) evenSum += arr[i];
        cout << "Parent process: Sum of even numbers = " << evenSum << endl;
        wait(nullptr);
    } else {  // Child process
        int oddSum = 0;
        for (int i = 0; i < size; i++) if (arr[i] % 2 != 0) oddSum += arr[i];
        cout << "Child process: Sum of odd numbers = " << oddSum << endl;
        exit(0);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Calculating sum of even and odd numbers:" << endl;
    sumEvenOdd(arr, size);

    cout << "\nCreating a zombie process:" << endl;
    createZombieProcess();
    sleep(5);

    cout << "\nCreating an orphan process:" << endl;
    createOrphanProcess();

    return 0;
}