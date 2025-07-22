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
 * @return      true if user presses 'j' (or 'y'), false if 'n'.
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

/**
 * @brief main is the main entry of the application. It Asks the user for startup info and presents some instructions before running into the game loop.
 * @return 0
 */
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
    auto use_letters = Yes();

    // Setting up the palette:
    std::string base(number_of_colors, ' ');
    if (use_letters)
    {
        std::iota(base.begin(), base.end(), 'a');
    }
    else
    {
        std::iota(base.begin(), base.end(), '1');
    }
    std::cout << "Mulige farver: \n";
    Buffer(base).Print();

    // INSTRUCTIONS:
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Indtast dit gaet. Kun eet af hvert tal er muligt!\n"
                 "Afslut dit gaet ved at trykke paa enter-tasten\n"
                 "Slet et tal ved at trykke paa melllemrumstasten.\n"
                 "Flyt cursoren med piletasterne.\n"
                 "Nulstil skrivefeltet med tryk paa r-tasten.\n"
                 "Efter hvert gaet faar du et svar:\n"
                 "  + betyder, at farven er rigtig, men den staar forkert\n"
                 "  # betyder, at farven er rigtig og staar rigtigt\n"
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

/**
 * @brief MasterMind is the event (key input) handler. It initializes the game and runs until game completion or forced exits.
 * @param number_of_colors  number of available colors.
 * @param code_size         size of the code
 * @param use_letters       if true, letters are used (from 'a'). If false, numbers are used (from '1').
 * @return                  0
 */
int MasterMind(size_t number_of_colors, size_t  code_size, bool use_letters)
{
    mastermind::Mastermind  master_mind(number_of_colors, code_size, use_letters);

    //std::cout << " ";
    //master_mind.PrintCode();

    Buffer  buffer(code_size);
    buffer.PrintAndMoveCursorToPosition();

    int     row_counter{0};

    // KEY EVENT LOOP:
    while (true)                // Runs infinitly - until break somewhere...
    {
        auto c = _getch();      // Getting the input character off the input buffer.

        if (c == 27)            // ESCAPE - end the game
        {
            std::cout << '\n' << "Afslutter..." << std::endl;
            break;              // Breaking out of the loop.
        }
        else if (c == 224)      // special keys...
        {
            auto c = _getch();  // Getting the extra input character off the input buffer.

            switch (c)
            {
            case 75:
                buffer.MoveLeft();
                break;
            case 77:
                buffer.MoveRight();
                break;
            }
        }
        else if (c == 8)        // BACK_SPACE - acting as left arrow.
        {
            //buffer.Set(' ');
            buffer.MoveLeft();
        }
        else if (c == 13)       // ENTER. Check the guess against the code.
        {
            ++row_counter;
            auto    response = master_mind.Check(buffer.Get());

            buffer.Print();
            response.Print();

            if (response.IsDone())  // If code is guessed...
            {
                if (row_counter <= 2)
                {
                    std::cout << '\n' << "Hahahaha - rent held!!!\nIalt " << row_counter << " traek" << std::endl;
                }
                else if (row_counter <= 4)
                {
                    std::cout << '\n' << "Fantastisk!!! Godt gaaet!!!\nIalt " << row_counter << " traek" << std::endl;
                }
                else if (row_counter <= 8)
                {
                    std::cout << '\n' << "Godt gaaet!!!\nIalt " << row_counter << " traek" << std::endl;
                }
                else
                {
                    std::cout << '\n' << "Godt gaaet - bedre held naeste gang!!!\nIalt " << row_counter << " traek" << std::endl;
                }
                break;          // code is guessed - break the loop.
            }

            buffer.Reset();     // Reset buffer to prepare for new guess...
            std::cout << '\n';  // ... at e new row.
        }
        else if ((!use_letters && c > '0' && c <= ('0' + number_of_colors))     // numeric characters > '0'
                 || (use_letters && c >= 'a' && c < ('a' + number_of_colors)))  // or... letters >= 'a'
        {
            if (!buffer.Has(c))
            {
                buffer.Insert(c);
            }
        }
        else if (c == ' ')      // SPACE - to clear a position
        {
            buffer.Insert(c);
        }
        else if (c == 'r')      // KEY 'r' to reset buffer
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
