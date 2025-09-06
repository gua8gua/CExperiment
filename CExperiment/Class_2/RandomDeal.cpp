#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CARDS 54
#define PLAYER_COUNT 3
#define HAND_SIZE 17
#define BOTTOM_SIZE 3

// 花色、牌面
const char* suits[] = { "黑桃", "红桃", "草花", "方块" };
const char* faces[] = {
    "2","3","4","5","6","7","8","9","10",
    "J","Q","K","A"
};

typedef struct {
    char suit[20];
    char face[10];
} Card;

// 构造一副牌
void buildDeck(Card deck[]) {
    int idx = 0;
    for (int s = 0; s < 4; s++) {
        for (int f = 0; f < 13; f++) {
            strcpy(deck[idx].suit, suits[s]);
            strcpy(deck[idx].face, faces[f]);
            idx++;
        }
    }
    strcpy(deck[idx].suit, "Red");  strcpy(deck[idx].face, "Joker"); idx++;
    strcpy(deck[idx].suit, "Black"); strcpy(deck[idx].face, "Joker"); idx++;
}

// 洗牌
void shuffle(Card deck[]) {
    for (int i = 0; i < TOTAL_CARDS; i++) {
        int r = rand() % TOTAL_CARDS;
        Card tmp = deck[i];
        deck[i] = deck[r];
        deck[r] = tmp;
    }
}

// 打印一张牌
void printCard(Card c) {
    if (strcmp(c.suit, "Red") == 0) {
        printf("大王 ");
    }
    else if (strcmp(c.suit, "Black") == 0) {
        printf("小王 ");
    }
    else {
        printf("%s_%s ", c.suit, c.face);
    }
}

// 发牌
void dealAndPrint(Card deck[]) {
    Card players[PLAYER_COUNT][HAND_SIZE];
    Card bottom[BOTTOM_SIZE];

    int idx = 0;
    for (int i = 0; i < PLAYER_COUNT * HAND_SIZE; i++) {
        players[i % PLAYER_COUNT][i / PLAYER_COUNT] = deck[idx++];
    }
    for (int i = 0; i < BOTTOM_SIZE; i++) {
        bottom[i] = deck[idx++];
    }

    // 打印
    for (int p = 0; p < PLAYER_COUNT; p++) {
        printf("玩家%d: ", p + 1);
        for (int j = 0; j < HAND_SIZE; j++) {
            printCard(players[p][j]);
        }
        printf("\n");
    }

    printf("底牌: ");
    for (int i = 0; i < BOTTOM_SIZE; i++) {
        printCard(bottom[i]);
    }
    printf("\n\n");
}

//int main() {
//    srand((unsigned)time(NULL));
//    Card deck[TOTAL_CARDS];
//
//    for (int t = 1; t <= 5; t++) {
//        buildDeck(deck);
//        shuffle(deck);
//        printf("===== 第 %d 次发牌 =====\n", t);
//        dealAndPrint(deck);
//    }
//
//    return 0;
//}
