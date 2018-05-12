#include <iostream>
#include <fstream>
#include <vector>


void prefix_function(std::string const & text, std::vector<int> & prefix)
{
    prefix.push_back(0);

    for (size_t i = 1; i < text.size(); ++i)
    {
        int border = prefix[i - 1];

        while (border > 0 && text[i] != text[border])
        {
            border = prefix[border - 1];
        }

        prefix.push_back(border + static_cast<int>(text[border] == text[i]));
    }
}


int main()
{
    std::ifstream inp_file("prefix.in");
    std::ofstream out_file("prefix.out");

    std::string text;
    inp_file >> text;

    std::vector<int> prefix;
    prefix_function(text, prefix);

    for (auto x : prefix)
    {
        out_file << x << ' ';
    }

    return 0;
}