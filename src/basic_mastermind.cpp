#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

#include <iostream>
#include <sstream>

int MasterMind(int number_of_colours);


int main()
{
    return MasterMind(6);
}


int MasterMind(int number_of_colours)
{
    std::vector<int> base(number_of_colours, 0);
    std::iota(base.begin(), base.end(), 1);

    std::cout << "Mulige 'farver':\n";
    for (auto c : base) std::cout << c << " ";
    std::cout << std::endl;


    std::vector<int> code;
    std::sample(base.begin(),
                base.end(),
                std::back_inserter(code),
                4,
                std::mt19937{std::random_device{}()});

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(base.begin(), base.end(), std::default_random_engine(seed));
    std::copy_n(base.begin(), 4, code.begin());

    for (auto c : code) std::cout << c << " ";
    std::cout << std::endl;

    std::cout << "Saa er vi igang - indtast dit bud og tryk enter..." << '\n';

    auto    extract = [](const std::string &s){
        std::istringstream  str(s);
        std::vector<int>    v;
        int x;
        while (str >> x)
        {
            v.push_back(x);
        }
        return v;
    };

    int counter{0};

    while (true)
    {
        std::string bud;
        std::getline(std::cin, bud);

        auto b = extract(bud);

        if (b.size() != 4)
        {
            std::cout << "Hov? du skal indtaste 4 tal med mellemrum - du tastede " << b.size() << "!\n";
            continue;
        }

        ++counter;

        int     match{0};
        int     off{0};

        for (int i=0; i<4; ++i)
        {
            if (code[i] == b[i])
                ++match;
            else if (std::find(code.begin(), code.end(), b[i]) != code.end())
                ++off;
        }

        std::cout << '['
                  << std::string(match, '+')
                  << std::string(off, '-')
                  << std::string(4 - match - off, '.')
                  << ']'
                  << std::endl;

        if (match == 4)
        {
            std::cout << "Saadan - Godt gået!!!" << std::endl;
            std::cout << "Antal gaet: " << counter << std::endl;
            break;
        }
    }

    return 0;
}

