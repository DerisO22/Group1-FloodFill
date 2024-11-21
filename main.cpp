// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
using namespace std;

void floodFillUtil(int x, int y, int targetColor, int replacementColor, vector<vector<int>>& image) {
    int rows = image.size(), cols = image[0].size();
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return;
    }
    if (image[x][y] != targetColor) {
        return;
    }
    image[x][y] = replacementColor;
    floodFillUtil(x-1, y, targetColor, replacementColor, image);
    floodFillUtil(x+1, y, targetColor, replacementColor, image);
    floodFillUtil(x, y-1, targetColor, replacementColor, image);
    floodFillUtil(x, y+1, targetColor, replacementColor, image);
}

void floodFill(int x, int y, int replacementColor, vector<vector<int>>& image) {
    int targetColor = image[x][y];
    if (targetColor != replacementColor) {
        floodFillUtil(x, y, targetColor, replacementColor, image);
    }
}
int main(){
    vector<vector<int>> image=
    { {0,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,1,1,1},
      {1,1,1,0,0,0,0,0,1,1},
      {1,1,1,0,1,0,0,1,1,1},
      {1,1,1,0,0,1,0,1,1,1},
      {1,1,1,0,0,0,0,1,1,1},
      {1,1,0,0,0,1,1,1,1,1},
      {1,1,1,1,0,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,0,0} };

    cout<<"Original Image :"<<endl;
    //print original matrix;
    for(int i=0; i < image.size(); i++){
        for(int j=0; j < image[0].size(); j++){
            cout<<image[i][j]<<" ";
        }
        cout<<endl;
    }
    cout << endl;

    int replacementColor, x, y;

    cout << "Enter a x-coordinate: ";
    cin >> x;

    cout << "Enter a y-coordinate: ";
    cin >> y;

    cout << "Enter a replacement color: ";
    cin >> replacementColor;

    floodFill(y-1, x-1, replacementColor, image);

    cout << "\nColored Image:" << endl;
    //print coloured matrix;
    for(int i=0; i < image.size(); i++){
        for(int j=0; j < image[0].size(); j++){
            cout<<image[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}