#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

double optimal_B(int n, double A)
{
    double hi = A;
    double low = 0;
    double B = 0;
    double EPS = 0.00000001;

    while (hi - low > EPS)
    {
        double middle = (hi + low) / 2;

        double prev_lamp = A;
        double curr_lamp = middle;
        double possible_B = 0;
        int at_ground = 0;

        for (int i = 2; i < n; ++i)
        {
            double next_lamp = 2 * curr_lamp + 2 - prev_lamp;
            if (next_lamp == 0)
            {
                ++at_ground;
            }
            if (next_lamp < 0)
            {
                at_ground = 2000;
                break;
            }
            prev_lamp = curr_lamp;
            curr_lamp = next_lamp;
            possible_B = next_lamp;
        }

        if (at_ground <= 1)
        {
            hi = middle;
            B = possible_B;
        }
        else
        {
            low = middle;
        }
    }

    return B;
}


int main()
{
    ifstream input("garland.in");
    ofstream output("garland.out");

    int n = 0;
    double A = 0;

    input >> n >> A;

    output << setprecision(2) << fixed << optimal_B(n, A);

    return 0;
}