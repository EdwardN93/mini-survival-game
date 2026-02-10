#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


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

int main()
{
    printf("Hello World!\n");
    Player player;
    initPlayer(&player, "Edwart");

    printf("Player name: %s\nHp: %d\nDay:%d\nCoins: %d\nExperience: %d", 
        player.name, 
        player.hp, 
        player.days, 
        player.coins, 
        player.xp);

    return 0;
}