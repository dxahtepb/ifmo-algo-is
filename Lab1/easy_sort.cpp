#include <fstream>
#include <vector>
 
using namespace std;
 
void bubble_sort(vector<int> & a) {
    int n = a.size();
    int temp;
 
    bool was_swap = false;
    do {
        was_swap = false;
        for (int i = 0; i < n-1; i++) {
            if (a[i] > a[i+1]) {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                was_swap = true;
            }
        }
    } while(was_swap);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin;
    fin.open("smallsort.in");
    unsigned int n;
    fin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    fin.close();
 
    bubble_sort(a);
 
    ofstream fout;
    fout.open("smallsort.out");
    for (int i = 0; i < n; i++) {
        fout << a[i] << " ";
    }
    fout.close();
 
    return 0;
}