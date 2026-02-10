#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    int hp;
    char name[32];
    int days;
    int coins;
    int xp;
} Player;

void initPlayer(Player* p, const char* name) {
    p->hp = 100;
    p->days = 1;
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
    p->coins = 10;
    p->xp = 0;
}

static void printStatus(const Player* p) {
    printf("\n=== STATUS ===\n");
    printf("Name: %s\n", p->name);
    printf("HP: %d\n", p->hp);
    printf("Day: %d\n", p->days);
    printf("Coins: %d\n", p->coins);
    printf("XP: %d\n", p->xp);
}

static void doExplore(Player* p) {
    int r = rand() % 100;
    if (r < 50) {
        int coins = rand() % 10 + 1;
        p->coins += coins;
        printf("You found %d coins\n", coins);
    }
    else if (r < 70) {
        int xp = rand() % 5 + 1;
        p->xp += xp;
        printf("You gained %d xp\n", xp);
    }
    else if (r < 90) {
        int dmg = rand() % 15 + 1;
        p->hp -= dmg;
        printf("You were attacked! Lost %d HP!\n", dmg);
    }
    else {
        printf("Nothing happened");
    }
    printf("\nYou rest...\n");

    p->days += 1;
}

static void doRest(Player* p) {
    printf("\nYou rest...\n");
    p->days += 1;
}

static int readMenuChoice(void) {
    char line[64];

    printf("\n=== MENU ===\n");
    printf("1) Explore\n");
    printf("2) Rest\n");
    printf("3) Status\n");
    printf("4) Exit\n");
    printf("Choose: ");

    if (!fgets(line, sizeof(line), stdin)) {
        return -1; // Input error
    }

    int choice = 0;

    if (sscanf(line, "%d", &choice) != 1) {
        return 0;
    }

    return choice;
}


int main()
{
    srand((unsigned)time(NULL));

    Player player;
    initPlayer(&player, "Edwart");

    printf("Welcome to Survival CLI");
    printStatus(&player);

    int running = 1;

    while (running) {
        int choice = readMenuChoice();

        switch (choice) {
        case 1:
            doExplore(&player);
            break;
        case 2:
            doRest(&player);
            break;
        case 3:
            printStatus(&player);
            break;
        case 4:
            running = 0;
            break;
        case -1:
            printf("\nInput closed. Exiting...\n");
            running = 0;
            break;
        default:
            printf("\nInvalid choice. Please type 1-4.\n");
            break;
        }

        if (player.hp <= 0) {
            printf("\nGame Over! %s did not survive.\n", player.name);
            running = 0;
        }
    }

    printf("\nBye!\n");

    return 0;
}