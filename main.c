#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Player{
    char name[20];
    int id;
    int age;
    int points;
    int gamesWon;
    int gamesLost;
    int winStreak;
    int lossStreak;
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

//get player number from first player created to current player created(first player created gets number 1 second player created gets number 2 etc)
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
    player->points = 0;
    player->gamesLost = 0;
    player->gamesWon = 0;
    player->winStreak = 0;
    player->lossStreak = 0;
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

int getGameNumber(){
    static int gameNumber = 0;
    return ++gameNumber;
}

typedef struct Game{
    int gameNumber;
    Player * player1;
    Player * player2;
    int pts1;
    int pts2;
}Game;


void displayGame(Game * game){ //displays the game inputed in the function
    printf("Game number %d\b" , game->gameNumber);
    printf("Player number : %d %s age : %d Number of points : %d" , game->player1->id , game->player1->name, game->player1->age , game->pts1);
    printf("Player number : %d %s age : %d Number of points : %d" , game->player2->id , game->player2->name, game->player2->age , game->pts2);

}


void playGame(Player * player1 , Player * player2 , Game *game , Player * winner ,Player * loser){
    int randNum;
    int rounds = 0;

    while(abs(player1->points - player2->points) < 3 || rounds != 12){
        randNum = rand() % 10000;
        printf("Number generated %d \n" , randNum);
        printf("It is the turn of %s\n" , player1->name);
        if(multipleOfFive(sumNumbers(randNum))){
            player1->points++;
            printf("%s gets 1 point\n" , player1->name);
            printf("Total points of %s is %d\n" ,player1->name , player1->points);
        }
        else{
            printf("%s gets 0 point\n" , player1->name);
        }
        randNum = rand() % 10000;
        printf("Number generated %d \n" , randNum);
        printf("It is the turn of %s\n" , player2->name);
        if(multipleOfFive(sumNumbers(randNum))){
            player2->points++;
            printf("%s gets 1 point\n" , player2->name);
            printf("Total points of %s is %d\n" ,player2->name , player2->points);
        }
        else{
            printf("%s gets 0 point\n", player2->name);
        }
        rounds = rounds + 2;
        /*
        printf("Enter 1 to continue\n");
        printf("Enter 0 to abort game\n");
        scanf("%d" , &stop);//the point of this scan is to allow the user to see the developpement of the game
           
        if(stop == 0){
            player1->points = 0;//reset points to 0
            player2->points = 0;
            return NULL; //abort game
        }
        */
    }    
    //record the game inside the game that has been passed to this function
    game->player1 = player1;
    game->player2 = player2;
    game->pts1 = player1->points;
    game->pts2 = player2->points;
    if(player1->points > player2->points){
        printf("%s won this game\n" , player1->name);
        player1->gamesWon++;
        player2->gamesLost++;
        player1->points = 0; //reset points to zero     
        player2->points = 0;
        player1->winStreak++;//add one to the win streak of the winner
        player2->winStreak = 0; //set winstreak of loser to 0
        player1->lossStreak = 0; //reset winstreak of 
        player2->lossStreak++;//add one to loser of 
        winner = player1;
        loser = player2;
        return;
    }
    else if(player1->points == player2->points){
        player1->points = 0;
        player2->points = 0;
        winner = NULL;//this makes it so there is no winner no loser
        loser = NULL;
        return;
    }
    else {
        printf("%s won this game\n" , player2->name);
        player2->gamesWon++;
        player1->gamesLost++;
        player1->points = 0; //reset points to zero     
        player2->points = 0;
        player2->winStreak++;
        player1->winStreak = 0; //set winstreak of loser to zero
        player2->lossStreak = 0;
        player1->lossStreak++; // add 1 to the loss streak of loser
        winner = player2;
        winner = player1;
        return;
    }
}


int main(){
    bool quit = false;
    int numPlayers = 0;

    printf("Game initialization!\n");
    printf("Input the number of players!\n");
    scanf("%d" , &numPlayers);

    

    while(!quit){
        ;
    }


    return 0;
}