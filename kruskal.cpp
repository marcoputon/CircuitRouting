#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct UF {
    vector<int> rank;
    vector<int> root;

    UF(int n): rank(n, 0), root(n) {
        for(int i = 0; i < n; ++i) root[i] = i;
    }

    int Find(int x) {
        if (root[x] != x) {
            root[x] = Find(root[x]);
        }
        return root[x];
    }

    void Union(int x, int y) {
        if (rank[root[x]] > rank[root[y]]) {
            root[root[y]] = root[x];
        }
        else if (rank[root[x]] < rank[root[y]]) {
            root[root[x]] = root[y];
        }
        else {
            root[root[y]] = root[x];
            rank[x]++;
        }
    }
};

struct Edge {
    int u, v, w;

    Edge(int u_, int v_, int w_):u(u_), v(v_), w(w_) {}

    friend bool operator<(const Edge & a, const Edge & b) {
        return a.w < b.w;
    }
};


struct MST {
    vector<Edge> edges;
    vector<Edge> result;

    int n;
    int sum;

    MST(int n_): n(n_), sum(0) {}

    void compute(bool dir) {
        UF uf(n);
        if (dir) sort(edges.rbegin(), edges.rend());
        else     sort(edges.begin(),  edges.end());

        result.clear();
        sum = 0;

        for(const Edge & e : edges) {
            //cout << "sum: " << sum << '\n';
            //cout << "UF: " << e.u << ' ' << e.v << '\n';
            if(uf.Find(e.u) != uf.Find(e.v)) {
                result.push_back(e);
                uf.Union(e.u, e.v);
                sum += e.w;
            }
        }
    }
};

int main() {
    int n;
    cin >> n;

    MST mst(n);

    for(int i = 0; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        //cout << "adding edges\n";
        mst.edges.emplace_back(u-1, v-1, w);
    }

    mst.compute(true);
    cout << mst.sum << '\n';

    mst.compute(false);
    cout << mst.sum << '\n';
}
