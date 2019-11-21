#include <iostream>
#include <fstream>

#define INFINITY 99999
#define MAX 1000

using namespace std;

ifstream test("floor.data");
ofstream output("final.path");

char floors[MAX][MAX];
int dist[MAX][MAX];
int parent[MAX][MAX];

// Queue implement
class Queue
{
private:
    int capacity;
    int front;
    int rear;
    int *queue;

public:
    Queue(int n)
    {
        capacity = n;
        front = -1;
        rear = -1;
        queue = new int[capacity];
    }
    void push(int x);
    void pop();
    bool isEmpty();
    bool isFull();
    int getFront();
};

void Queue::push(int x)
{
    if (isFull())
    {
        cout << "Queue is full.\n";
    }
    queue[++rear] = x;
}
void Queue::pop()
{

    if (isEmpty())
    {
        cout << "Queue is empty.\n";
        return;
    }
    front++;
}
bool Queue::isFull()
{

    return (rear + 1 == capacity);
}
bool Queue::isEmpty()
{

    return (front == rear);
}
int Queue::getFront()
{
    return queue[front + 1];
}

void BFS(int start_x, int start_y, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = INFINITY;
            parent[i][j] = -1;
        }
    }
    Queue *queue = new Queue(m * n);

    dist[start_x][start_y] = 0;
    parent[start_x][start_y] = -1;

    int s = start_x * 1000 + start_y;
    queue->push(s);

    while (!queue->isEmpty())
    {
        int top = queue->getFront();
        int rol = top / 1000;
        int col = top % 1000;

        queue->pop();

        if (floors[rol - 1][col] == '0' && parent[rol - 1][col] == -1)
        {
            dist[rol - 1][col] = dist[rol][col] + 1;
            parent[rol - 1][col] = top;
            int left = (rol - 1) * 1000 + col;
            queue->push(left);
        }
        if (floors[rol + 1][col] == '0' && parent[rol + 1][col] == -1)
        {
            dist[rol + 1][col] = dist[rol][col] + 1;
            parent[rol + 1][col] = top;
            int right = (rol + 1) * 1000 + col;
            queue->push(right);
        }
        if (floors[rol][col - 1] == '0' && parent[rol][col - 1] == -1)
        {
            dist[rol][col - 1] = dist[rol][col] + 1;
            parent[rol][col - 1] = top;
            int down = rol * 1000 + (col - 1);
            queue->push(down);
        }
        if (floors[rol][col + 1] == '0' && parent[rol][col + 1] == -1)
        {
            dist[rol][col + 1] = dist[rol][col] + 1;
            parent[rol][col + 1] = top;
            int up = rol * 1000 + (col + 1);
            queue->push(up);
        }
    }
}
void path(long battery, int m, int n, int start_x, int start_y)
{

    int max = 0;
    int temp = battery;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] > max && dist[i][j] != INFINITY)
            {
                max = dist[i][j];
            }
        }
    }
    int count = 0;
    for (int k = 1; k <= max; k++)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][j] == k)
                {
                    count += k * 2;
                }
            }
        }
    }

    output << count << '\n';
    for (int k = 1; k <= max; k++)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                battery = temp;
                if (dist[i][j] == k)
                {
                    output << start_x << " " << start_y << " ";
                    output << '\n';
                    int tempArr[max * 2];
                    int inverseArr[max * 2];
                    int index = 0;
                    int tmp_x = i;
                    int tmp_y = j;
                    while (parent[tmp_x][tmp_y] != -1)
                    {
                        inverseArr[index] = tmp_y;
                        inverseArr[index + 1] = tmp_x;
                        tempArr[index] = tmp_x;
                        tempArr[index + 1] = tmp_y;

                        int tmp = parent[tmp_x][tmp_y];

                        tmp_x = tmp / 1000;
                        tmp_y = tmp % 1000;
                        index += 2;
                    }

                    for (int l = index - 1; l >= 2; l--)
                    {
                        output << inverseArr[l] << " ";
                        if (l % 2 == 0)
                        {
                            output << '\n';
                            battery--;
                        }
                    }
                    for (int l = 0; l < index; l++)
                    {
                        output << tempArr[l] << " ";
                        if (l % 2 == 1)
                        {
                            output << '\n';
                            battery--;
                        }
                    }

                    output << start_x << " " << start_y << " ";
                    output << '\n';
                    battery--;
                }
            }
        }
    }
}

int main()
{
    int m, n;
    test >> m >> n;
    char floor;
    long battery;
    test >> battery;
    int start_x;
    int start_y;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            test >> floor;
            floors[i][j] = floor;
            if (floor == 'R')
            {
                start_x = i;
                start_y = j;
            }
        }
    }
    BFS(start_x, start_y, m, n);
    path(battery, m, n, start_x, start_y);

    return 0;
}