#include <iostream>
#include <fstream>

#define INFINITY 99999;

using namespace std;

ifstream test("floor.data");
ofstream output("final.path");


int main()
{
    int m , n ;
    test >> m >> n;
    char floors[m][n];
    char floor;
    int battery;
    test >> battery;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            test >> floor;
            floors[i][j] = floor;
        }
    }
    
    return 0;
}