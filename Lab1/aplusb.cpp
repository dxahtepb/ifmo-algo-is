#include <fstream>
using namespace std;

int main() {
    ifstream in("aplusb.in");
    ofstream out("aplusb.out");
    int64_t a = 0, b = 0;
    in >> a >> b;
    out << static_cast<int64_t>(a + b);
}