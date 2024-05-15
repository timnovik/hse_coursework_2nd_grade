#include <vector>
#include <iostream>

#define int long long

using namespace std;

struct edge {
    int from, to, c, g;

    edge(int _from, int _to, int _c, int _g): from(_from), to(_to), c(_c), g(_g) {}
};

vector<edge> e;
vector<vector<int>> costs;
vector<int> d;
vector<int> prev_d;
vector<vector<int>> p;

const int inf = 1e9;

void solve() {
    int n, s, k;
    cin >> n >> s >> k;
    costs.assign(k, vector<int>(n));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> costs[i][j];
        }
    }
    e.clear();
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int c;
            cin >> c;
            int g_ij = 0, g_ji = 0;
            for (int w = 1; w < k; ++w) {
                if (costs[w][j] - costs[w][i] - c > costs[g_ij][j] - costs[g_ij][i] - c) {
                    g_ij = w;
                }
                if (costs[w][i] - costs[w][j] - c > costs[g_ji][i] - costs[g_ji][j] - c) {
                    g_ji = w;
                }
            }
            e.emplace_back(i, j, costs[g_ij][j] - costs[g_ij][i] - c, g_ij);
            e.emplace_back(j, i, costs[g_ji][i] - costs[g_ji][j] - c, g_ji);
        }
    }
    prev_d.assign(n, -n * inf);
    prev_d[0] = 0;
    d = prev_d;
    p.assign(1, vector<int>(n, -1));
    for (int len = 1; len < s; ++len) {
        p.push_back(p.back());
        for (int i = 0; i < e.size(); ++i) {
            if (prev_d[e[i].from] != -n * inf && prev_d[e[i].from] + e[i].c > d[e[i].to]) {
                d[e[i].to] = prev_d[e[i].from] + e[i].c;
                p[len][e[i].to] = i;
            }
        }
        prev_d = d;
    }

    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (d[i] > d[ans]) {
            ans = i;
        }
    }
    if (ans == 0) {
        cout << -1 << endl;
        return;
    }

    int cur = ans;
    vector<int> path{ans};
    vector<int> goods;
    int val = 0;
    int cnt = s - 1;
    while (cur != 0 || val != d[ans]) {
        edge ed = e[p[cnt][cur]];
        --cnt;
        cur = ed.from;
        path.push_back(cur);
        goods.push_back(ed.g);
        val += ed.c;
    }
    cout << path.size() << ' ' << d[ans] << endl;
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i] + 1 << ' ';
    }
    cout << endl;
    for (int i = goods.size() - 1; i >= 0; --i) {
        cout << goods[i] + 1 << ' ';
    }
    cout << endl;
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
