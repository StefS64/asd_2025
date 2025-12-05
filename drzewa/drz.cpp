#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> t;
    Fenwick(int n) : n(n), t(n+1, 0) {}
    void add(int i, int v) {
        for(; i <= n; i += i & -i) t[i] += v;
    }
    int sum(int i) {
        int s = 0;
        for(; i > 0; i -= i & -i) s += t[i];
        return s;
    }
};

struct Query {
    long long x;
    int y, id, sign;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<long long,long long>> pts(n);
    vector<long long> ys; ys.reserve(n + 2*m);

    for(int i=0;i<n;i++){
        cin >> pts[i].first >> pts[i].second;
        ys.push_back(pts[i].second);
    }

    vector<array<long long,4>> qs(m);
    for(int i=0;i<m;i++){
        cin >> qs[i][0] >> qs[i][1] >> qs[i][2] >> qs[i][3];
        ys.push_back(qs[i][2]);
        ys.push_back(qs[i][3]);
        ys.push_back(qs[i][2]-1);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto getY = [&](long long y){
        auto it = std::lower_bound(ys.begin(), ys.end(), y);
        if (it == ys.end()) return (int)ys.size(); 
        return (int)(it - ys.begin()) + 1;
    };

    sort(pts.begin(), pts.end());

    vector<Query> pref;
    pref.reserve(4*m);

    for(int i=0;i<m;i++){
        auto [xl, xr, yb, yt] = qs[i];

        long long xs[2] = {xr, xl-1};
        long long ys1[2] = {yt, yb-1};
        int signs[2][2] = {{+1, -1}, {-1, +1}};

        for(int xi = 0; xi < 2; xi++)
            for(int yi = 0; yi < 2; yi++) {
                long long X = xs[xi];
                long long Y = ys1[yi];
                if (Y < 0) Y = -1;

                pref.push_back({
                    X,
                    (Y < 0 ? 0 : getY(Y)),
                    i,
                    signs[xi][yi]
                });
            }
    }

    sort(pref.begin(), pref.end(),
         [](auto &a, auto &b){ return a.x < b.x; });

    Fenwick fw(ys.size());
    vector<long long> ans(m, 0);

    int ptr = 0; 

    for(auto &q : pref) {
        while(ptr < n && pts[ptr].first <= q.x) {
            int Yc = getY(pts[ptr].second);
            fw.add(Yc, 1);
            ptr++;
        }
        if (q.y > 0)
            ans[q.id] += q.sign * fw.sum(q.y);
        else
            ans[q.id] += 0; 
    }

    for(long long v : ans)
        cout << v << "\n";
}
