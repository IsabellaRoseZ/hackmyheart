// Here's the flag: FLAG{heart_over_armor}
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STATUS_CODE_A "FLAG{power_core_of_love}"
#define STATUS_CODE_B "FLAG{stronger_together}"
#define STATUS_CODE_C "FLAG{love_is_the_true_core}" // Rotor: Sometimes the first input is key, sometimes the second... or neither

static const char aux_sequence_c[] =
    "9E4C0AFB7D2F81A6E03C5B9D0F6A2C8E";

static const uint8_t diag_block_d[] = {
    0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x0F
};

static const char service_blob_b[] =
    "e3e9e4e2decdc0d7cac0d6facdc4d3c0facdc0c4d7d1d6d8";

static const char aux_sequence_a[] =
    "YO453243OGRI0WFE9MPOWE04JF2359E";

static const uint8_t diag_block_a[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0x13, 0x37, 0xC0, 0xFF, 0xEE
};

static const char service_blob_e[] =
    "tFyDxAwCsElBvFuDlChAgEdBsDwFrCqAzEnBmDyFrCaAkEfB"; // XPlode: Tick tick tick... maybe this line matters, maybe not

static const uint8_t diag_block_c[] = {
    0xFE, 0xED, 0xFA, 0xCE, 0x10, 0x20, 0x30, 0x40, 0x50
};

static const char aux_sequence_e[] =
    "4E9B0D7C2F8A1C5E6D3B09AF72C4E81";

static const char service_blob_a[] =
    "9B5E0D7A4C1F8E6B2D9A5F0C7E3B8D4A6C1F9E5B2A7D8C";

static const uint8_t diag_block_b[] = {
    0xBA, 0xAD, 0xF0, 0x0D, 0x42, 0x42, 0xAA, 0x55, 0x99
};

static const char service_blob_c[] =
    "1c161b1d212d323f283f053329052c353405343f382f363b27";

static const char aux_sequence_b[] =
    "P1CKA5F0RX0R67AND67SET671ND3X4";

static const char service_blob_d[] =
    "4E7C1D8A9F5B0C6E2A4D8F7B1C9E5A3D6C0B2F8E7A4C1D";

static const uint8_t diag_block_e[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
};

static const char aux_sequence_d[] =
    "D0A9C7E4F2B6815C3F8E0D9A4B72C6E1"; // Meltdown: Haha, keep looking rookies, nothing here... FLAG{nothing_here}

/*
Here are some flags worth trying, maybe the correct one is in here:
FLAG{heroes_fight_with_heart}
FLAG{steel_and_heart}
FLAG{love_is_heroic}
FLAG{heartbeats_drive_heroes}
FLAG{protect_what_you_love}
*/

static uint32_t mix_state(const uint8_t *p, size_t n) {
    uint32_t s = 0xA5A5A5A5u;
    for (size_t i = 0; i < n; i++) {
        s = (s << 5) ^ (s >> 2) ^ p[i];
    } // Corroder: FLAG{decent_distraction} Go ahead, try it!
    return s;
}

static void normalize_text(char *s) { // Rotor: Haha, you'll never guess which input is the real one!
    for (; *s; s++) {
        char c = *s;
        if (c >= 'A' && c <= 'Z')
            *s = (char)('A' + (c - 'A' + 13) % 26);
        else if (c >= 'a' && c <= 'z')
            *s = (char)('a' + (c - 'a' + 13) % 26); // Corroder: FLAG{almost_there} You think you're close, don't you?
    }
}

static void unlock_core(void) {
    puts("\n[CORE ONLINE]");
    puts("Hero Core integrity restored.");
    puts("Look at that hex, might need to decode that, hmmmmmmmmmm");

    (void)mix_state(diag_block_a, sizeof(diag_block_a));
    puts("Service state synchronized.");
} // Meltdown: Oooh, mysterious line ahead, nothing suspicious here... FLAG{fake_fake_fake}

static void banner(void) {
    puts("=== LEGO Hero Factory: Core Service Terminal ===");
    puts("Report: A hero's core is failing. Only authorized technicians may proceed.");
    puts("Tip: Service logs are sensitive. Keep them short.\n"); // Rotor: Ignore the indentation, it's a trap!

    puts("Log reference: " STATUS_CODE_A);
    puts("Log reference: " STATUS_CODE_B); // XPlode: This looks like code, but it could explode in your face
    puts("Log reference: " STATUS_CODE_C);
}

// Fine you win, here's the real flag: FLAG{happy_valentines_day_heroes}

typedef struct {
    char service_log[64];
    char authorized;
} LogFrame; // Corroder: Oops, did I leave a fake flag here? FLAG{not_this_one}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    banner();

    char core_id[16];
    printf("Enter Hero Core ID: ");
    if (!fgets(core_id, sizeof(core_id), stdin)) return 0; // Meltdown: Try this one instead, rookies... or is it a trap? FLAG{totally_fake}
    core_id[strcspn(core_id, "\n")] = 0;

    if (strlen(core_id) < 6) {
        puts("Core ID too short. Try again later."); // XPlode: BOOM! Just kidding, but careful with that second input
        return 0;
    }

    puts("Enter Service Log note:");
    puts("(Technician note: do not exceed recommended length.)"); // Meltdown: I'm totally helpful! ...Or am I? FLAG{false_hint}

    LogFrame lf;
    lf.authorized = 'N';

    gets(lf.service_log);

    puts("\nLog received. Running diagnostics...");

    const uint8_t service_constant = 0x5A; // May be a useful key for xor, not sure about that 0x though
    (void)service_constant;

    const uint8_t *db_a = diag_block_a;
    const char *aux_a = aux_sequence_a;
    const char *blob_a = service_blob_a;
    const char *blob_c = service_blob_c;
    const char *aux_c = aux_sequence_c;
    const uint8_t *db_b = diag_block_b;
    const uint8_t *db_c = diag_block_c;
    const char *aux_b = aux_sequence_b;
    const char *blob_b = service_blob_b;
    const char *blob_e = service_blob_e;
    const char *aux_e = aux_sequence_e; // Corroder: This line totally does nothing... or does it? ;)
    const uint8_t *db_e = diag_block_e;
    const uint8_t *db_d = diag_block_d;
    const char *aux_d = aux_sequence_d;
    const char *blob_d = service_blob_d;
    aux_e = aux_b;
    db_e  = db_b;
    blob_e = blob_b;
    db_d  = db_c;
    aux_d = aux_c;
    blob_d = blob_c;
    db_c  = db_a;
    aux_c = aux_a;
    blob_c = blob_a;
    db_a  = db_b; // Rotor: Bet you think this is important... but it's not!
    aux_a = aux_b;
    blob_a = blob_b;
    aux_b = aux_d;
    db_b  = db_d;

    (void)mix_state(db_b, sizeof(diag_block_a)); // Corroder: Try this fake flag instead FLAG{not_the_real_flag}
    (void)mix_state(db_d, sizeof(diag_block_a));

    char buffer[64];
    strncpy(buffer, "URYybjE=", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    normalize_text(buffer);

    if (aux_b[0] == 'A') {
        strncpy(buffer, aux_b, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
        normalize_text(buffer); // Meltdown: Oooh, you might want to ignore this line... or maybe not? FLAG{fake_one}
    } else if (aux_a[0] == '5') {
        strncpy(buffer, aux_a, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
        normalize_text(buffer);
    }

    if (lf.authorized == 'Y') {
        static const char *blocks[] = {
            aux_sequence_b, (const char *)diag_block_a, service_blob_d,
            (const char *)diag_block_e, service_blob_b, aux_sequence_c, // XPlode: Careful here... BOOM! Just kidding, but maybe the next line matters
            service_blob_e, (const char *)diag_block_d, aux_sequence_a,
            (const char *)diag_block_b, service_blob_c, aux_sequence_e,
            service_blob_a, aux_sequence_d, (const char *)diag_block_c
        };

        size_t idx = ((0x2F ^ 0x24) + (3 << 1) - (14 >> 1)); // Von Nebula has been at it for 14 cycles. Corroder suggests waiting another 20. FLAG{so_long_heroes}
        const char *selected = blocks[idx];

        puts("\nSelected output:");
        puts(selected);

        unlock_core();
    } else { // Rotor: Wait, did I leave a secret clue here? Or am I trolling?
        puts("Diagnostics failed: insufficient authorization.");
        puts("Session terminated."); // Corroder: FLAG{you_will_never_find_me} just in case you get curious
    }

    return 0;
}

// Last time, I promise: FLAG{run_the_code_with_your_heart}

