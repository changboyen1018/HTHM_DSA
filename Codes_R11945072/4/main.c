#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    int attack_power;
    int player_id;
    struct Player *next;
    struct Player *pre;
} Player;

Player *create_player(int attack_power, int player_id, Player *next, Player *pre) {
    Player *temp = (Player *)malloc(sizeof(Player));

    temp->attack_power = attack_power;
    temp->player_id = player_id;
    temp->next = next;
    temp->pre = pre;

    return temp;
}

Player *eliminate_weaker_players(Player *head, int attack_power, int *surviving_players) {
    Player *current = head;
    while (current != NULL) {
        if (current->attack_power >= attack_power)
            break;
        printf(" %d", current->player_id);
        Player *temp = current->next;
        free(current);
        current = temp;
        (*surviving_players)--;
    }
    return current;
}

void enter_arena(Player **head, Player **tail, int attack_power, int player_id, Player *current) {
    *head = create_player(attack_power, player_id, current, NULL);
    if ((*head)->next != NULL)
        (*head)->next->pre = *head;
    if ((*head)->next == NULL)
        *tail = *head;
}

void handle_revolution(Player **tail, int *surviving_players, int arena_size) {
    if (*surviving_players > arena_size) {
        printf(" %d", (*tail)->player_id);
        Player *tail2 = (*tail)->pre;
        free(*tail);
        *tail = tail2;
        (*surviving_players)--;
        (*tail)->next = NULL;
    }
}

void process_rounds(int num_players, int arena_size) {
    Player *head = NULL;
    Player *tail = NULL;
    int surviving_players = 0;

    for (int i = 0; i < num_players; i++) {
        int power;
        printf("Round %d:", i + 1);
        scanf("%d", &power);
        surviving_players += 1;

        Player *current = eliminate_weaker_players(head, power, &surviving_players);

        enter_arena(&head, &tail, power, i + 1, current);

        handle_revolution(&tail, &surviving_players, arena_size);

        printf("\n");
    }

    printf("Final:");
    Player *current = head;
    while (current != NULL) {
        printf(" %d", current->player_id);
        current = current->next;
    }
}

int main() {
    int num_players, arena_size;

    scanf("%d %d", &num_players, &arena_size);
    process_rounds(num_players, arena_size);

    return 0;
}
