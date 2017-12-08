#include <fstream>
using namespace std;

int main() {
    ifstream in("aplusbb.in");
    ofstream out("aplusbb.out");
    int64_t a = 0, b = 0;
    in >> a >> b;
    out << static_cast<int64_t>(a + b * b);
}