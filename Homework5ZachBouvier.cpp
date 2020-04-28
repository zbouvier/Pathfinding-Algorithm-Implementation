// Homework5ZachBouvier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class MapVertex
{
    public:
        bool known;
        int parent = 0;
        vector<int> neighbors;
        int pathCost = 1;
        int id;
        friend ostream& operator<<(ostream& os, const MapVertex& mv);
        MapVertex(int nodeID, int parentNode, vector<int> neighborNodes)
        {

            id = nodeID;
            known = false;
            parent = parentNode;
            neighbors = neighborNodes;
        }

};
ostream& operator<<(ostream& os, const MapVertex& mv) {
    os << "----------------" << endl << "Node:" << mv.id << endl << "Cost:" << mv.pathCost << endl << "Parent:" << mv.parent << endl << "Known:" << mv.known << endl << "Neighbors:" << mv.neighbors.size() << endl << "----------------";
    return os;
}
vector<MapVertex> readFile()
{
    ifstream file("maze.txt");
    string str;
    vector<MapVertex> vectorOfMap;
    while (getline(file, str)) {
        std::istringstream is(str);
        int n;
        
        vector<int> ids;
        bool firstNumber = true;
        while (is >> n) {

            
            int parent = 0;
            vector<int> neighbors;
            if (n != -1)
            {
                if (firstNumber)
                {
                    firstNumber = false;
                    MapVertex temp = MapVertex(n, 0, neighbors);
                    while (is >> n)
                    {
                        if (n == -1)
                        {
                            break;
                        }
                        else
                        {
                            temp.neighbors.push_back(n);
                        }
                    }
                    vectorOfMap.push_back(temp);

                }

            }
            else
            {
                firstNumber = true;
            }
        }
        
        //return vectorOfMap;
    }
    return vectorOfMap;
}
vector<int> findPath(vector<MapVertex> fullMap)
{
    vector<int> temp;
    int size = fullMap.size();
    int currentLocation = size;
    while (fullMap[currentLocation-1].parent >= 0)
    {
        if (fullMap[currentLocation - 1].parent > 0)
        {
            temp.push_back(fullMap[currentLocation - 1].id);
            currentLocation = fullMap[currentLocation - 1].parent;
        }
        else
        {
            temp.push_back(fullMap[currentLocation - 1].id);
            break;
        }

    }
    return temp;
}

int findPathCost(vector<MapVertex> fullMap)
{
    return fullMap[fullMap.size()-1].pathCost;
}
int main()
{
    queue<MapVertex> q;
    
    vector<MapVertex> test = readFile();
    q.push(test[0]);
    while (!q.empty())
    {
        MapVertex v = q.front();
        //cout << q.front();
        q.pop();
        for (int i = 0; i < (int) v.neighbors.size(); i++)
        {
            if (!(test[v.neighbors[i]-1].known) && v.neighbors.size() > 0)
            {
                test[v.neighbors[i]-1].pathCost = v.pathCost + 1;
                test[v.neighbors[i]-1].parent = v.id;
                test[v.neighbors[i]-1].known = true;
                q.push(test[v.neighbors[i]-1]);
            }
        }
    }
    vector<int> pathFound = findPath(test);
    for (int i = pathFound.size(); i > 0; i--)
    {
        cout << pathFound[i-1] << "->";
    }
    cout << "Cost:" << findPathCost(test);
}

/*
    q.push(v_start)
        while (!q.isEmpty()) {
            v = q.dequeue();
            for each w adjacent to v{
                if (w is unknown) {
                    w.cost = v.cost + 1
                    w.known = true
                    w.parent = v
                    q.enqueue(w);
                }
            }
        }
*/