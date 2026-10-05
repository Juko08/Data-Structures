#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

int main() {
    // Graph:
    //       A
    //      / \
    //     B   C
    //    / \   \
    //   D   E   F

    vector<vector<int>> graph = {
        {1, 2},       // A
        {3, 4},       // B
        {5},          // C
        {},           // D
        {},           // E
        {}            // F
    };

    vector<char> names = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<bool> visited(6, false);
    queue<int> q;

    q.push(0);
    visited[0] = true;

    cout << "BFS visit order: ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << names[current];
        if (!q.empty()) cout << " -> ";

        for (int next : graph[current]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    cout << endl;
    return 0;
}
