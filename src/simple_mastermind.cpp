#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

#include <iostream>
#include <sstream>

#include <conio.h>

#include "buffer.h"
#include "master_mind.h"

int MasterMind2(size_t number_of_colors, size_t code_size);


int main()
{
    std::cout << "Velkommen til MasterMind :-)" << '\n';
    
    size_t  number_of_colors{6};
    std::cout << "Hvor mange 'farver' vil du spille med? Indtast tal [4-8]: ";
    std::cin >> number_of_colors;

    size_t  code_size{4};
    std::cout << "Hvor lang en kode? Indtast tal [4-8]: ";
    std::cin >> code_size;

    bool    done = false;
    while (!done)
    {
        MasterMind2(number_of_colors, code_size);

        //std::string answer;
        std::cout << "Vil du spille igen? [j/n]" << std::endl;
        while (true)
        {
            auto    answer = _getch();
            //std::cin >> answer;
            if (answer == 'n' || answer == 'N')
            {
                done = true;
                std::cout << "\nFarvel og tak :-)" << std::endl;
                break;
            }
            else if (answer == 'j' || answer == 'J')
            {
                break;
            }
        }
    }

    return 0;
}

//int MasterMind(int number_of_colours)
//{
//    std::vector<int> base(number_of_colours, 0);
//    std::iota(base.begin(), base.end(), 1);
//
//    std::cout << "Mulige 'farver':\n";
//    for (auto c : base) std::cout << c << " ";
//    std::cout << std::endl;
//
//
//    std::vector<int> code;
//    std::sample(base.begin(),
//                base.end(),
//                std::back_inserter(code),
//                4,
//                std::mt19937{std::random_device{}()});
//
//    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::shuffle(base.begin(), base.end(), std::default_random_engine(seed));
//    std::copy_n(base.begin(), 4, code.begin());
//
//    for (auto c : code) std::cout << c << " ";
//    std::cout << std::endl;
//
//    std::cout << "Saa er vi igang - indtast dit bud og tryk enter..." << '\n';
//
//    auto    extract = [](const std::string &s){
//        std::istringstream  str(s);
//        std::vector<int>    v;
//        int x;
//        while (str >> x)
//        {
//            v.push_back(x);
//        }
//        return v;
//    };
//
//    int counter{0};
//
//    while (true)
//    {
//        std::string bud;
//        std::getline(std::cin, bud);
//
//        auto b = extract(bud);
//
//        if (b.size() != 4)
//        {
//            std::cout << "Hov? du skal indtaste 4 tal med mellemrum - du tastede " << b.size() << "!\n";
//            continue;
//        }
//
//        ++counter;
//
//        int     match{0};
//        int     off{0};
//
//        for (int i=0; i<4; ++i)
//        {
//            if (code[i] == b[i])
//                ++match;
//            else if (std::find(code.begin(), code.end(), b[i]) != code.end())
//                ++off;
//        }
//
//        std::cout << '['
//                << std::string(match, '+')
//                << std::string(off, '-')
//                << std::string(4 - match - off, '.')
//                << ']'
//                << std::endl;
//
//        if (match == 4)
//        {
//            std::cout << "Saadan - Godt gået!!!" << std::endl;
//            std::cout << "Antal gaet: " << counter << std::endl;
//            break;
//        }
//    }
//
//    return 0;
//}

int MasterMind2(size_t number_of_colors, size_t  code_size)
{
    mastermind::Mastermind  master_mind(number_of_colors, code_size);

    //std::cout << " ";
    //master_mind.PrintCode();

    Buffer  buffer(code_size);
    
    int     index{0};
    
    while (true)
    {
        auto c = _getch();
        
        if (c == 27)    // escape
        {
            std::cout << '\n' << "Afslutter..." << std::endl;
            break;
        }
        
        if (c == 224) // special keys
        {
            auto c = _getch();
            
            switch (c) 
            {
                case 75:
                    buffer.MoveLeft();
                break;
                case 77:
                    buffer.MoveRight();
                break;
            }
            
            //continue;
        }
        else if (c == 8)  // back_space
        {
            buffer.Set(' ');
            buffer.MoveLeft();
        }
        else if (c == 13) // enter
        {
            ++index;
            auto    response = master_mind.Check(buffer.Get());
            
            buffer.Print();
            response.Print();
            
            if (response.Done())
            {
                std::cout << '\n' << "Fantastisk!!! Godt gaaet!!!\nIalt " << index << " traek" << std::endl;
                break;
            }
            
            buffer.Reset();
            std::cout << '\n';
        }
        else if (c > '0' && c <= ('0' + number_of_colors)) // && position < 4)
        {
            if (!buffer.Has(c))
            {
                buffer.Insert(c);
            }
        }
        else if (c == ' ')
        {
            buffer.Insert(c);
        }
        else
        {
            std::cout << c;
        }
        
        buffer.PrintAndMoveCursorToPosition();
    }
    
    return 0;
}
