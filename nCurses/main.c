#include <ncurses.h>

int main() {
    initscr();             // Initialize ncurses mode
    noecho();              // Don't show typed characters
    cbreak();              // Disable line buffering
    keypad(stdscr, TRUE);  // Enable arrow keys
    nodelay(stdscr, TRUE); // Non-blocking input

    printw("Press 'q' to quit.\n");
    refresh();
    
    int ch;
    while ((ch = getch()) != 'q') {
        if (ch != ERR) {  // Check if a key was pressed
            printw("You pressed: %c\n", ch);
            refresh();
        }
    }

    endwin(); // Restore normal terminal behavior
    return 0;
}
