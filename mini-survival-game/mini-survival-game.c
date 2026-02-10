#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAX_HP 100
#define XP_PER_LEVEL 20
#define MAXHP_PER_LEVEL 10

typedef struct {
    int hp;
    int maxHp;
    char name[32];
    int days;
    int coins;
    int xp;
    int level;
} Player;

void initPlayer(Player* p, const char* name) {
    p->level = 1;
    p->maxHp = MAX_HP;
    p->hp = p->maxHp;

    p->days = 1;
    p->coins = 10;
    p->xp = 0;

    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
}

static void checkLevel(Player* p) {
    int newLevel = (p->xp / XP_PER_LEVEL) + 1;

    if (newLevel > p->level) {
        int gained = newLevel - p->level;

        p->level = newLevel;
        p->maxHp += gained * MAXHP_PER_LEVEL;
        p->hp = p->maxHp;

        printf("\n*** LEVEL UP! Now level %d | Max HP: %d ***\n",
            p->level, p->maxHp);
    }
}

static void printStatus(const Player* p) {
    printf("\n=== STATUS ===\n");
    printf("Name: %s\n", p->name);
    printf("Level: %d | XP: %d\n", p->level, p->xp);
    printf("HP: %d / %d\n", p->hp, p->maxHp);
    printf("Day: %d\n", p->days);
    printf("Coins: %d\n", p->coins);
}

static int tryRareEvent(Player* p) {
    int rare = rand() % 100;

    if (rare >= 5) {
        return 0; 
    }

    int type = rand() % 4;

    if (type == 0) {
        int coins = rand() % 50 + 20;
        p->coins += coins;
        printf("Lucky find! +%d coins!\n", coins);
    }
    else if (type == 1) {
        int xp = rand() % 15 + 5;
        p->xp += xp;
        printf("Big discovery! +%d XP\n", xp);
    }
    else if (type == 2) {
        int dmg = rand() % 30 + 15;
        p->hp -= dmg;
        if (p->hp < 0) p->hp = 0;
        printf("Ambush! Lost %d HP!\n", dmg);
    }
    else {
        int heal = rand() % 20 + 10;
        int oldHp = p->hp;
        p->hp += heal;
        if (p->hp > p->maxHp) p->hp = p->maxHp;
        printf("Medical supplies found! HP %d -> %d\n", oldHp, p->hp);
    }

    return 1;
}


static void doExplore(Player* p) {
    printf("\nYou explore the area...\n");

    if (tryRareEvent(p)) {
        p->days += 1;
        checkLevel(p);
        return;
    }

    int r = rand() % 100;
    if (r < 35) {
        int coins = rand() % 10 + 1;
        p->coins += coins;
        printf("You found %d coins\n", coins);
    }
    else if (r < 50) {
        int xp = rand() % 5 + 1;
        p->xp += xp;
        printf("You gained %d xp\n", xp);
    }
    else if (r < 85) {
        int dmg = (rand() % 10 + 5) + p->days / 5;

        p->hp -= dmg;
        if (p->hp < 0) p->hp = 0;

        printf("You were attacked! Lost %d HP!\n", dmg);
    }
    else {
        printf("\nNothing happened\n");
    }

    p->days += 1;
    checkLevel(p);
}

static void doRest(Player* p) {
    int cost = rand() % 20 + 1;
    int heal = rand() % 16 + 10;
    int xp = rand() % 3 + 1;

    if (p->hp >= p->maxHp) {
        printf("Health is already full. Resting did nothing.\n");
        return;
    }

    if (p->coins < cost) {
        printf("You don't have enough coins to rest. Need %d, you have %d.\n", cost, p->coins);
        return;
    }

    p->coins -= cost;

    int oldHp = p->hp;
    p->hp += heal;
    if (p->hp > p->maxHp) p->hp = p->maxHp;

    p->xp += xp;
    p->days += 1;

    printf("You rested: HP %d -> %d (+%d), XP +%d, Coins -%d\n",
        oldHp, p->hp, (p->hp - oldHp), xp, cost);

    checkLevel(p);

}

static void doMarket(Player* p) {
    int running = 1;
	char line[64];
    int choice;

    while (running) {
        printf("\n=== MARKET ===\n");
        printf("Coins: %d | HP: %d\n", p->coins, p->hp);
        printf("1) Buy Health Potion (+25 HP) - Cost: 25 coins\n");
        printf("2) Exit\n");
        printf("Choose: ");

        if (!fgets(line, sizeof(line), stdin)) {
            return;
        }

        if (sscanf(line, "%d", &choice) != 1) {
            choice = 0;
        }

        switch (choice) {
            case 1:
                if (p->coins < 25) {
                    printf("Not enought coins!\n");
                    break;
                }
                if (p->hp >= p->maxHp) {
                    printf("Health already full.\n");
                    break;
                }
                p->coins -= 25;

                int oldHp = p->hp;
                p->hp += 25;
                if (p->hp > p->maxHp)
                    p->hp = p->maxHp;

                printf("Potion used! HP %d -> %d\n", oldHp, p->hp);
                checkLevel(p);
                break;
            case 2:
                running = 0;
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
}

static int readMenuChoice(void) {
    char line[64];

    printf("\n=== MENU ===\n");
    printf("1) Explore\n");
    printf("2) Rest\n");
    printf("3) Market\n");
    printf("4) Status\n");
    printf("5) Exit\n");
    printf("Choose: ");

    if (!fgets(line, sizeof(line), stdin)) {
        return -1; 
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
    char name[32];

    printf("Enter your name: ");

    if (fgets(name, sizeof(name), stdin)) {
        name[strcspn(name, "\n")] = '\0';
    }
    else {
        strcpy(name, "Player");
    }

    initPlayer(&player, name);

    printf("Welcome to Survival CLI");
    printStatus(&player);

    int running = 1;

    while (running) {
        int choice = readMenuChoice();

        switch (choice) {
        case 1:
            doExplore(&player);
			printStatus(&player);
            break;
        case 2:
            doRest(&player);
			printStatus(&player);
            break;
        case 3:
            doMarket(&player);
            break;
        case 4:
            printStatus(&player);
            break;
        case 5:
            running = 0;
            break;
        default:
            printf("\nInvalid choice. Please type 1-5.\n");
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