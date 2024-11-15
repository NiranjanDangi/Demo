#include <iostream>
#include <vector>
#include <thread>

using namespace std;

#define MAX 4

int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];  // Used for both addition and subtraction results
int D[MAX][MAX];  // Used for multiplication results

struct threadData {
    int row, col;
};

void add(threadData data) {
    C[data.row][data.col] = A[data.row][data.col] + B[data.row][data.col];
}

void sub(threadData data) {
    C[data.row][data.col] = A[data.row][data.col] - B[data.row][data.col];
}

void mul(threadData data) {
    int sum = 0;
    for (int i = 0; i < MAX; i++) {
        sum += A[data.row][i] * B[i][data.col];
    }
    D[data.row][data.col] = sum;
}

void initMat() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = i + j + 1;
            B[i][j] = i * j + 1;
        }
    }
}

template <typename FUNC>
void operation(FUNC op) {
    vector<thread> threads;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            // Pass threadData by value to avoid data races
            threads.emplace_back(op, threadData{i, j});
        }
    }
    for (auto &it : threads) it.join();
}

void printmat(int mat[MAX][MAX], const string &label) {
    cout << label << " operation:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}s

int main() {
    initMat();
    
    operation(add);
    printmat(C, "Addition");

    operation(sub);
    printmat(C, "Subtraction");

    operation(mul);
    printmat(D, "Multiplication");

    return 0;
}
