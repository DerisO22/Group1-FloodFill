#include <iostream>
#include <vector>
// Src: https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
#include <chrono>
#include <thread>
#include <queue>
#include <stack>
using namespace std;

// Adapted from https://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
// It was not optimized at all, so I added some stuff

// Using an iterative approach for dfs and bfs similar to assignment 8

/**
 * Fills an image starting at coordinates (x,y) with a replacementColor if the point matches targetColor
 */
void floodFill(const int x, const int y, const int targetColor, const int replacementColor, vector<vector<int>> &image, vector<vector<bool>> &visited) {
    int rows = image.size(), cols = image[0].size();

    // Base cases
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return;
    }
    if (image[x][y] != targetColor) {
        return;
    }
    if (image[x][y] == replacementColor) {
        return;
    }
    if (visited[x][y]) {
        return;
    }

    // Recursive steps
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

    // Recursively call floodFill for adjacent cells
    floodFill(x - 1, y, targetColor, replacementColor, image, visited);
    floodFill(x + 1, y, targetColor, replacementColor, image, visited);
    floodFill(x, y - 1, targetColor, replacementColor, image, visited);
    floodFill(x, y + 1, targetColor, replacementColor, image, visited);
}

void bfsFloodFill(const int x, const int y, const int targetColor, const int replacementColor, vector<vector<int> > &image, vector<vector<bool> > &visited) {
    int rows = image.size();
    int cols = image[0].size();

    queue<pair<int, int>> frontier;
    frontier.push({x, y});

    // Run BFS
    while (!frontier.empty()) {
        auto [row, col] = frontier.front();
        frontier.pop();

        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            continue;
        }
        if (image[row][col] != targetColor) {
            continue;
        }
        if (image[row][col] == replacementColor) {
            continue;
        }
        // Check if already visited
        if (visited[row][col]) {
            continue;
        }

        visited[row][col] = true;
        image[row][col] = replacementColor;

        // Print the updated matrix after each change
        cout << "Step: " << endl;
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[0].size(); j++) {
                cout << image[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        // step-by-step output
        this_thread::sleep_for(std::chrono::milliseconds(1500));

        // Add adjacent cells to the queue and check for already visited
        if (row - 1 >= 0 && !visited[row - 1][col] && image[row - 1][col] == targetColor) {
            frontier.push({row - 1, col});
        }
        if (row + 1 < rows && !visited[row + 1][col] && image[row + 1][col] == targetColor) {
            frontier.push({row + 1, col});
        }
        if (col - 1 >= 0 && !visited[row][col - 1] && image[row][col - 1] == targetColor) {
            frontier.push({row, col - 1});
        }
        if (col + 1 < cols && !visited[row][col + 1] && image[row][col + 1] == targetColor) {
            frontier.push({row, col + 1});
        }
    }
}

int main() {
    vector<vector<int>> image =
    {
        {0, 2, 2, 2, 2, 2, 2, 0, 0, 0},
        {0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
        {0, 2, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 2, 0, 0, 0, 0, 0, 0, 2, 2},
        {0, 2, 0, 0, 8, 3, 5, 0, 2, 2},
        {0, 2, 0, 0, 6, 3, 5, 0, 2, 2},
        {0, 2, 0, 0, 1, 5, 0, 0, 2, 2},
        {0, 2, 0, 0, 5, 0, 0, 0, 2, 2},
        {0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {0, 2, 2, 2, 2, 2, 2, 0, 0, 0}
    };
    // {
    //     {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
    //     {1, 1, 1, 0, 0, 0, 0, 0, 1, 1},
    //     {1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
    //     {1, 1, 1, 0, 0, 1, 0, 1, 1, 1},
    //     {1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
    //     {1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
    //     {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 0, 0}
    // };
    vector visited(image.size(), vector(image[0].size(), false));

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

    int choice;
    cout << "Choose Your Approach:" << endl;
    cout << "1. DFS" << endl;
    cout << "2. BFS" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    // Check User Input
    if (choice == 1) {
        floodFill(x - 1, y - 1, image[x - 1][y - 1], replacementColor, image, visited);
    } else if (choice == 2) {
        bfsFloodFill(x - 1, y - 1, image[x - 1][y - 1], replacementColor, image, visited);
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

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