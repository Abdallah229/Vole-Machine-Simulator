#include <iostream>
#include <vector>
#include "options.h"
#define GREEN "\e[32m"
#define RESET "\e[0m"
#define CYANBACK "\e[46m"
#define CYAN    "\033[36m"
#define YELLOW "\e[33m"
#define BOLD    "\033[1m"
using namespace std;
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>



int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void printMenu(const   vector<  string>& options, int selected) {
    // Move the cursor to the position where the options begin
    

      cout << "\033[3;0H"; // Move to the home position (top left corner)
    
    // Print all options and highlight the selected one
    for (int i = 0; i < options.size(); ++i) {
        if (i == selected) {
            // Highlight the selected option
              cout << "\033[1;32m> " << options[i] << "\033[0m" <<   endl;
        } else {
            // Print non-selected options
              cout << "  " << options[i] <<   endl;
        }
    }

    // Move the cursor back to the first option position
      cout << "\033[" << options.size() << "A"; // Move cursor up by the number of options
}






int navigateMenu(const   vector<  string>& options) {
    int selected = 0;

    while (true) {
        printMenu(options, selected);

        int key = _getch();

#ifdef _WIN32
        if (key == 224) { // Arrow keys are prefixed with 224 in Windows
            key = _getch();
            switch (key) {
                case 72: // Up arrow
                    if (selected > 0) selected--;
                    break;
                case 80: // Down arrow
                    if (selected < options.size() - 1) selected++;
                    break;
            }
        }
#else
        if (key == 27) { // Escape sequence for arrow keys
            _getch();    // Skip the '[' character
            key = _getch(); // Get arrow key direction
            switch (key) {
                case 'A':  // Up arrow
                    if (selected > 0) selected--;
                    break;
                case 'B':  // Down arrow
                    if (selected < options.size() - 1) selected++;
                    break;
            }
        }
#endif
        if (key == '\n' || key == '\r') { // Enter key
            return selected; // Return the index of the selected option
        }
    }
}
