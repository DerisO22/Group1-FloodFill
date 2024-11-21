#include <iostream>
#include <vector>
// Src: https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
#include <chrono>
#include <thread>
using namespace std;

// Src: https://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
// It was not optimized at all, so I added some stuff
void floodFillUtil(int x, int y, int targetColor, int replacementColor, vector<vector<int>>& image, vector<vector<bool>>& visited) {
    int rows = image.size(), cols = image[0].size();
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return;
    }
    if (image[x][y] != targetColor) {
        return;
    }
    if (image[x][y] == replacementColor) {
        return;
    }
    // Check if already visited
    if (visited[x][y]) {
        return;
    }

    visited[x][y] = true;
    image[x][y] = replacementColor;

    // Print the updated matrix after each change
    cout << "Step: " << endl;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[0].size(); j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    // step-by-step
    this_thread::sleep_for(std::chrono::milliseconds(1500));

    // Recursive call floodFill
    floodFillUtil(x - 1, y, targetColor, replacementColor, image, visited);
    floodFillUtil(x + 1, y, targetColor, replacementColor, image, visited);
    floodFillUtil(x, y - 1, targetColor, replacementColor, image, visited);
    floodFillUtil(x, y + 1, targetColor, replacementColor, image, visited);
}

void floodFill(int x, int y, int replacementColor, vector<vector<int>>& image) {
    int targetColor = image[x][y];
    if (targetColor != replacementColor) {
        // I've added visited vector to optimize the dfs
        vector<vector<bool>> visited(image.size(), vector<bool>(image[0].size(), false));
        floodFillUtil(x, y, targetColor, replacementColor, image, visited);
    }
}
int main() {
    vector<vector<int>> image =
    { {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
      {1, 1, 1, 0, 0, 0, 0, 0, 1, 1},
      {1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
      {1, 1, 1, 0, 0, 1, 0, 1, 1, 1},
      {1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
      {1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0} };

    cout << "Original Image :" << endl;
    //print original matrix;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[0].size(); j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int replacementColor, x, y;
    cout << "Enter a x-coordinate: ";
    cin >> x;
    cout << "Enter a y-coordinate: ";
    cin >> y;
    cout << "Enter a replacement color: ";
    cin >> replacementColor;

    floodFill(y - 1, x - 1, replacementColor, image);

    cout << "\nColored Image:" << endl;
    //print coloured matrix;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[0].size(); j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}