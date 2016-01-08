#include <bits/stdc++.h>

#define INF 1000000000
#define MAXN 1000   /// number of nodes

using namespace std;

typedef pair < int, int > ii;
typedef vector < ii > vii;

/**
    N         : number of vertices
    M         : number of edges
    adj[i][j] : adjacency list - cost from vertex i to adj[i][j].first is adj[i][j].second
    pq        : priority queue for candidate vertices - sorted by dist
    dist[i]   : distance from starting edge

    Vertex ids are 0-based
    i.e. we have vertices 0, 1, 2, ..., N-1
**/

int N, M;
int start; /// starting vertex
int dist[MAXN];
vector < vii > adj;
priority_queue < ii, vector < ii > , greater < ii > > pq;

void Read() {
    int u, v, w;  /// temp edge

    cin >> N >> M;
    cin >> start;

    adj.assign(N, vii());  /// initialize adjacency list
    for (int i=0; i<M; i++) {
        cin >> u >> v >> w;    /// directed edge u -> v cost w
        adj[u].push_back(ii(v, w));
    }
}

void Dijkstra() {
    for (int i=0; i<N; i++)
        dist[i] = INF;      /// infinite cost is 1B to avoid overflow
    dist[start] = 0;     /// distance from start to start is 0
    pq.push(ii(0, start));  /// push start in priority queue

    while (!pq.empty()) {   /// while there are more vertices to consider
        /// remove topmost vertex
        ii next = pq.top();
        int currVert = next.second;
        int currDist = next.first;
        pq.pop();

        if (dist[currVert] != currDist) continue;  /// we have already processed this vertex

        /// update all neighbors of currVert
        for (int i=0; i<adj[currVert].size(); i++) {
            int candVert = adj[currVert][i].first;
            int candDist = adj[currVert][i].second;
            if (currDist + candDist < dist[candVert]) {   /// we have found a better path for candVert
                dist[candVert] = currDist + candDist;
                pq.push(ii(dist[candVert], candVert));
            }
        }
    }
}

int main()
{
    Read();    /// Read input and initialize adjacency list
    Dijkstra();  /// Execute Dijkstra's algorithm

    /// Now distance from start is in dist[i]
    for (int i=0; i<N; i++) {
        cout << "Distance from: " << start << " to: " << i << " is: " << dist[i] << endl;
    }

    return 0;
}
