#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Player{
    char name[20];
    int id;
    int age;
    struct Player * next;
}Player;

typedef struct Queue{
    Player * head;
    Player * tail;
    int size;
}Queue;

void initQueue(Queue * queue){
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

//get player number from first player created to current player created(first player created gets number 1)
int getPlayerNumber(){
    static int playerNumber = 0;
    return ++playerNumber;
}

//Function to create player to avvoid repeated code
Player * createPlayer(){
    Player * player = malloc(sizeof(Player));
    player->next = NULL;
    player->id = getPlayerNumber();
    printf("Enter Name Of Player");
    fgets(player->name,sizeof(player->name), stdin);
    player->name[strcspn(player->name, "\n")] = '\0';
    printf("Enter player age");
    scanf("%d" , &player->age);
    getchar();
    return player;
}

//We take number by number starting from right to left and add them together
int sumNumbers(int initNumber){
    int sum = 0;
    while(initNumber != 0){
        sum = (sum + initNumber % 10);
        initNumber = initNumber / 10;
    }
    return sum;
}

//The if statement by default in gcc compiler returns true or false using this functionnality saves time
bool multipleOfFive(int number){
    return (number % 5 == 0);
}

bool emptyQueue(Queue * queue){
    return(queue->size == 0);
}


//Add element at the end of the Queue
void enQueue(Queue * queue){
    Player * player = createPlayer();
    if(queue->tail == NULL){
        queue->head = player;
        queue->tail = player;
        return;
    }
    else{
        queue->tail->next = player;
        queue->tail = queue->tail->next;
    }
    queue->size++;
}
Player * deQueue(Queue * queue){
    if(emptyQueue(queue)){
        return NULL;
    }
    Player * temp = queue->head;
    queue->head = queue->head->next;
    if(queue->head == NULL){
        queue->tail = NULL;
    }
    temp->next = NULL;
    queue->size--;
    return  temp;
}

Player * topPlayer(Queue * queue){
    if(emptyQueue) return NULL;
    return queue->head;
}

int main(){



    return 0;
}