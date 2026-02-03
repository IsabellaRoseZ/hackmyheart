#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Overflowing Love (Easy)
 * Goal: Overflow the buffer to change "isLoved" to the magic value,
 * then the program prints the flag.
 *
 * Intended solve: send > 32 bytes + overwrite int to 0x1337
 */

static void print_flag(void) {
    // Keep flag in the binary for easy CTF-style retrieval after triggering condition.
    // If you prefer a file-based flag for hosting, see the "Server Variant" section below.
    puts("💖 The program blushes...");
    puts("FLAG{overflowing_with_love}");
}

int main(void) {
    // Make IO predictable for netcat/remote usage
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin,  NULL, _IONBF, 0);

    struct {
        char note[32];
        int isLoved;
    } box;

    box.isLoved = 0;

    puts("=== Overflowing Love 💘 ===");
    puts("Write your Valentine note:");
    puts("(Tip: this program REALLY loves long messages...)");
    printf("> ");

    // Vulnerable input on purpose (easy buffer overflow)
    gets(box.note); // NOLINT (intentional vulnerability)

    if (box.isLoved == 0x1337) {
        puts("\n💌 Your note was... overwhelmingly convincing.");
        print_flag();
    } else {
        puts("\n💔 Aww... that's sweet, but not convincing enough.");
        printf("Debug (for dev): isLoved = 0x%x\n", box.isLoved);
    }

    return 0;
}
