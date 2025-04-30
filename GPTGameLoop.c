#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("\033[2J\033[H"); // ANSI escape code to clear screen and move cursor to home

    printf("#######################\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress any key (Ctrl+C to exit):\n");

    char key;
    while (1) {
        // Read a single character from the terminal
        if (read(STDIN_FILENO, &key, 1) == -1) {
            perror("reading failed");
            exit(EXIT_FAILURE);
        }
        // Clear the terminal and print the pressed key
        printf("\033[2J\033[H"); // Clear screen and move cursor to home
        printf("\aYou pressed: '%c' (ASCII: %d)\n", key, key);
        printf("a");
    }

    return 0;
}
