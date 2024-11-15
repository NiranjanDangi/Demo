#include <iostream>
#include <vector>
using namespace std;

#define MAX_FRAMES 10

int FIFO(const vector<int>& pages, int frames) {
    int pageFaults = 0;
    vector<int> frame(frames, -1);
    int index = 0;

    for (int page : pages) {
        bool found = false;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = true;
                break;
            }
        }

        // Page fault occurs if page is not found
        if (!found) {
            frame[index] = page;
            index = (index + 1) % frames; // Circular increment for FIFO
            pageFaults++;
        }
    }
    return pageFaults;
}

int LRU(const vector<int>& pages, int frames) {
    int pageFaults = 0;
    vector<int> frame(frames, -1);
    vector<int> lastUsed(frames, -1);

    for (int i = 0; i < pages.size(); i++) {
        bool found = false;

        // Check if page is already in frame and update last used time
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = true;
                lastUsed[j] = i;
                break;
            }
        }

        // Page fault occurs if page is not found
        if (!found) {
            int lruIndex = 0;

            // Find the least recently used page to replace
            for (int j = 1; j < frames; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }

            frame[lruIndex] = pages[i];
            lastUsed[lruIndex] = i;
            pageFaults++;
        }
    }
    return pageFaults;
}

int Optimal(const vector<int>& pages, int frames) {
    int pageFaults = 0;
    vector<int> frame(frames, -1);

    for (int i = 0; i < pages.size(); i++) {
        if (find(frame.begin(), frame.end(), pages[i]) == frame.end()) {
            int farthest = i + 1, optimalIndex = 0;
            for (int j = 0; j < frames; j++) {
                auto it = find(pages.begin() + i + 1, pages.end(), frame[j]);
                int dist = (it != pages.end()) ? distance(pages.begin(), it) : pages.size();
                if (dist > farthest) { farthest = dist; optimalIndex = j; }
            }
            frame[optimalIndex] = pages[i];
            pageFaults++;
        }
    }
    return pageFaults;
}


int main() {
    // Hardcoded page reference string (converted from characters to integers)
    vector<int> pages = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}; // Example: A=0, B=1, C=2, etc.
    int frames = 3; // Number of frames

    cout << "Page faults for FIFO: " << FIFO(pages, frames) << endl;
    cout << "Page faults for LRU: " << LRU(pages, frames) << endl;
    cout << "Page faults for Optimal: " << Optimal(pages, frames) << endl;

    return 0;
}
