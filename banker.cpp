#include <iostream>
using namespace std;

int main() {
    int n = 5; // Number of processes
    int m = 3; // Number of resources
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int avail[3] = {3, 3, 2}; // Available resources

    int f[n] = {0}, ans[n], need[n][m];

    // Calculating the Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Display Allocation Matrix
    cout << "Allocated Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << alloc[i][j] << " ";
        cout << endl;
    }

    // Display Max Matrix
    cout << "\nMax Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << max[i][j] << " ";
        cout << endl;
    }

    // Display Need Matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << endl;
    }

    cout << "\nAvailable resources: ";
    for (int i = 0; i < m; i++)
        cout << avail[i] << " ";
    cout << endl;

    // Banker's Algorithm
    int ind = 0;
    bool safe = true;
    for (int k = 0; k < n; k++) {
        bool allocated = false;
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    ans[ind++] = i;
                    cout << "\nResources allocated to P" << i;
                    for (int y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                    allocated = true;
                }
            }
        }

        if (!allocated) {
            safe = false;
            cout << "\nThe system is not in a safe state.\n";
            break;
        }
    }

    if (safe) {
        cout << "\nThe system is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < n - 1; i++)
            cout << "P" << ans[i] << " -> ";
        cout << "P" << ans[n - 1] << endl;
    }

    return 0;
}
