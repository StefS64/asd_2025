#include <iostream>

using namespace std;
constexpr int MOD = 1e9;


struct tree_elem {
    int state[10];
    // default constructor: initialize all entries to zero
    tree_elem(int a) {
        for (int i = 0; i < 10; ++i) state[i] = 0;
        state[0] = a;
    }

    tree_elem() {
        for (int i = 0; i < 10; ++i) state[i] = 0;
    }

    // element-wise addition
    tree_elem operator+ (const tree_elem& other) const {
        tree_elem result;
        for (int i = 0; i < 10; ++i) {
            result.state[i] = (this->state[i] + other.state[i]) % MOD;
        }
        return result;
    }

    tree_elem& operator+= (const tree_elem& other) {
        // delegate to operator+
        *this = *this + other;
        return *this;
    }

    void shift() {
        for (int i = 9; i > 0; i--) {
            state[i] = state[i-1];
        }
        state[0] = 1;
    }

    // stream output for debugging/printing
    friend ostream &operator<<(ostream &os, const tree_elem &p)
    {
        os << "{";
        for (int i = 0; i < 10; ++i) {
            os << p.state[i];
            if (i + 1 < 10) os << ", ";
        }
        os << "}";
        return os;
    }
};
constexpr int MAX_VAL = 32678;//32678
constexpr int TREE_SIZE = 2*(MAX_VAL); 

int T[MAX_VAL + 2];

tree_elem Tree[TREE_SIZE];


void init_tree() {
    for(int i = 1; i < TREE_SIZE; i++) {
        Tree[i] = tree_elem(0);
    }
}

void print_tree() {
    for (int i = 0; i < TREE_SIZE; i++){
        cout << i << " : " << Tree[i] << endl;
    }
}


void enplace(int index, tree_elem value) {
    index = MAX_VAL + index - 1;
    // cout << "enplacing" << index << value <<endl;
    Tree[index] = value;
    index /= 2;
    while (index > 0) {
        Tree[index] = Tree[2*index + 1] + Tree[2*index];
        index /= 2;
    }
}


tree_elem sum(int l, int r)
{
    l = MAX_VAL + l - 1;
    r = MAX_VAL + r - 1;
    tree_elem _sum = tree_elem(0);

    while (l <= r) {  
        // cout << l <<":l r:"<< r <<endl;
        // cout <<"sum " << _sum << endl;
        if(l % 2 == 1) {
            // cout <<"hello" <<endl;
            _sum += Tree[l];
            l++;
        }
        if(r % 2 == 0) {
            // cout <<"hello" << Tree[r] << endl;
            _sum += Tree[r];
            r--;
        }

        r /=2;
        l /=2;
    }

    // cout <<"sum " << _sum << endl;
    return _sum;
}



int main() {
    int k, n;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> T[i];
    }

    int end_sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        tree_elem subset = sum(1,T[i] - 1);
        subset.shift();
        // cout << subset << endl;
        enplace(T[i], subset);
        end_sum = (end_sum + (Tree[T[i] + MAX_VAL - 1].state[k-1])) % MOD;

        // print_tree();
    }

    cout << end_sum << endl;
    return 0;
}
