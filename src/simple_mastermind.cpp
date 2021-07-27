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

int MasterMind(size_t number_of_colors, size_t code_size, bool use_letters);

/**
 * @brief Yes runs a infinite loop until user presses 'j' (yes) or 'n' (no) returns true if 'j' and false if 'n'.
 * @return      true if user presses 'j', false if 'n'.
 */
bool    Yes()
{
    std::cout << " [j/n]";

    while (true)
    {
        auto    answer = _getch();
        if (answer == 'n' || answer == 'N')
        {
            std::cout << std::endl;
            return false;
        }
        else if (answer == 'j' || answer == 'J' || answer == 'y' || answer == 'Y')
        {
            std::cout << std::endl;
            return true;
        }
    }
}

int main()
{

    std::cout << "Velkommen til MasterMind :-)" << '\n';

    // SETUP:
    size_t  number_of_colors{6};
    std::cout << "Hvor mange 'farver' vil du spille med? Indtast tal [4-8]: ";
    std::cin >> number_of_colors;

    size_t  code_size{4};
    std::cout << "Hvor lang en kode? Indtast tal [4-" << number_of_colors << "]: ";
    std::cin >> code_size;

    std::cout << "Vil du spille med bogstaver?";
    bool    use_letters{false};
    if (Yes())
    {
        use_letters = true;
    }

    std::cout << "Mulige farver: \n";
    std::string base(number_of_colors, ' ');
    if (use_letters)
    {
        std::iota(base.begin(), base.end(), 'a');
    }
    else
    {
        std::iota(base.begin(), base.end(), '1');
    }
    Buffer(base).Print();

    // INSTRUCTIONS:
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Indtast dit gaet. Kun eet af hvert tal er muligt!\n"
                 "Afslut dit gaet ved at trykke paa enter-tasten\n"
                 "Slet et tal ved at trykke paa melllemrumstasten.\n"
                 "Flyt cursoren med piletasterne.\n"
                 "Nulstil skrivefeltet med tryk paa r-tasten.\n"
                 "Afslut spillet ved at vinde - eller ved at trykke paa escape-tasten."
              << std::endl;
    std::cout << std::endl;
    std::cout << "God fornoejelse :-)"
              << std::endl;
    std::cout << std::endl;

    bool    done = false;
    while (!done)
    {
        try {
            MasterMind(number_of_colors, code_size, use_letters);
        } catch (std::exception &e)
        {
            std::cout << "ERROR: " << e.what() << std::endl;
            return -1;
        }

        //std::string answer;
        std::cout << "Vil du spille igen?";
        if (!Yes())
        {
            done = true;
            std::cout << "\nFarvel og tak :-)" << std::endl;
        }
    }

    return 0;
}

int MasterMind(size_t number_of_colors, size_t  code_size, bool use_letters)
{
    mastermind::Mastermind  master_mind(number_of_colors, code_size, use_letters);

    //std::cout << " ";
    //master_mind.PrintCode();

    Buffer  buffer(code_size);
    buffer.PrintAndMoveCursorToPosition();

    int     index{0};

    while (true)
    {
        auto c = _getch();

        if (c == 27)    // escape
        {
            std::cout << '\n' << "Afslutter..." << std::endl;
            break;
        }
        else if (c == 224) // special keys
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
            //buffer.Set(' ');
            buffer.MoveLeft();
        }
        else if (c == 13) // enter
        {
            ++index;
            auto    response = master_mind.Check(buffer.Get());

            buffer.Print();
            response.Print();

            if (response.IsDone())
            {
                if (index <= 2)
                {
                    std::cout << '\n' << "Hahahaha - rent held!!!\nIalt " << index << " traek" << std::endl;
                }
                else if (index <= 4)
                {
                    std::cout << '\n' << "Fantastisk!!! Godt gaaet!!!\nIalt " << index << " traek" << std::endl;
                }
                else if (index <= 8)
                {
                    std::cout << '\n' << "Godt gaaet!!!\nIalt " << index << " traek" << std::endl;
                }
                else
                {
                    std::cout << '\n' << "Godt gaaet - bedre held naeste gang!!!\nIalt " << index << " traek" << std::endl;
                }
                break;
            }

            buffer.Reset();
            std::cout << '\n';
        }
        else if (!use_letters && c > '0' && c <= ('0' + number_of_colors))
        {
            if (!buffer.Has(c))
            {
                buffer.Insert(c);
            }
        }
        else if (use_letters && c >= 'a' && c < ('a' + number_of_colors))
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
        else if (c == 'r')
        {
            buffer.Reset();
            buffer.Print();
        }
        else
        {
            //std::cout << c;
        }

        buffer.PrintAndMoveCursorToPosition();
    }

    return 0;
}
