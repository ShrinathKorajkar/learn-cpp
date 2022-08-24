#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;

vector<int> adj[N];
int m, n;
int vis[N];
int lvl[N];

void bfs(int u)
{

    queue<int> q;
    lvl[u] = 0, vis[u] = 1;
    q.push(u);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i : adj[u])
        {
            if (not vis[i])
            {
                lvl[i] = 1 + lvl[u];
                vis[i] = 1;
                q.push(i);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> m >> n;
    int count = 0;
    for (int i = 1; i <= m * n; i++)
    {
        int a;
        cin >> a;
        if ((i - 1) % n == 0)
            count++;

        for (int j = i + 1; j <= i + a and j <= count * n; ++j)
            adj[i].push_back(j);
    }
    for (int i = 1; i <= m * n; ++i)
    {
        int a;
        cin >> a;
        for (int j = i; j + n <= n * m and a; j += n, a--)
            adj[i].push_back(j + n);
    }
    bfs(1);
    cout << lvl[n * m] << endl;
    return 0;
}