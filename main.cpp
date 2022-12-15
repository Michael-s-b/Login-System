#include <iostream>
#include <string>
#include <iomanip>
#include <limits>    //for std::numeric_limits<std::streamsize>::max()
#include <windows.h> // for the refresh_console function

// simple function that clears out the console to be similar with a window.
void refreshConsole()
{
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR)' ',
            cellCount,
            homeCoords,
            &count))
        return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count))
        return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
// parse and print on the console a title line given a string and a int.
void displayTitle(int width, std::string title)
{
    width = width / 2;
    int differencial = title.length() / 2;
    std::cout << std::setw(width - differencial) << std::right << std::setfill('=') << "_";
    std::cout << title;
    std::cout << std::setw(width - differencial) << std::left << std::setfill('=') << "_";
    std::cout << std::endl;
}
// print the main menu of the application on the console
void displayMainMenu()
{
    displayTitle(60, "Welcome");
    std::cout << "L. Login\n"
              << "R. Register\n"
              << "Q. Exit" << std::endl;
}
// prompt the user for a single character.
char promptCharacter()
{
    char selection{};
    std::string tempString{};
    std::cout << "Enter a selection: ";
    // only one character can be selected at a time, will ignore the rest of the input.
    if (!(std::getline(std::cin, tempString)).fail() && !tempString.empty()) // if the extraction of the input of the user into the tempString NOT fails AND if the tempString is NOT empty.
    {
        return selection = tempString.at(0); // return the first character of the tempString
    }
    else
    {
        // else clear the input buffer stream and throw an exception.
        // std::cin.clear();
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // actualy theres no need to clear the input buffer.
        throw std::invalid_argument("Invalid input");
    }

    return selection;
}
// main function of the program
int main()
{
    char selection{}; // initialized to '\0' "null terminated"
    // the program starts
    refreshConsole();
    do
    {
        // reset selection to null
        selection = '\0';
        // show the user an menu with login and register options
        displayMainMenu();
        // prompt the user to choose beetwen the options available
        try
        {
            selection = std::toupper(promptCharacter());
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            selection = '\0'; // reset selection to null
        }
        if (selection != '\0') // check if selection is null
        {
            // if the user input is valid then call the corresponding function to the choice made
            switch (selection)
            {
            case 'L':
                std::cout << "Login selected" << std::endl;
                break;
            case 'R':
                std::cout << "Register selected" << std::endl;
                break;
            case 'Q':
                std::cout << "Exit selected" << std::endl;
                break;
            default:
                std::cout << '\"' << selection << '\"' << " is a invalid selection" << std::endl;
                break;
            }
        }
    } while (selection != 'Q');
    std::cout << "Program finished" << std::endl;

    // login and register functions end with success or failure message
};