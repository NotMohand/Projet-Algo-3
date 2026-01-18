#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct Player{
    char name[30];
    int id;
    int age;
    int gamesWon;
    int gamesLost;
    int winStreak;
    int cumulativepts;
    int newLosses; //for RULESET 2
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
    printf("Enter Name Of Player : ");
    fgets(player->name,sizeof(player->name), stdin);
    player->name[strcspn(player->name, "\n")] = '\0';
    printf("Enter player age : ");
    scanf("%d" , &player->age);
    getchar();
    player->gamesLost = 0;
    player->gamesWon = 0;
    player->winStreak = 0;
    player->cumulativepts = 0;
    player->newLosses = 0;
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
void createEnQueue(Queue * queue){
    Player * player = createPlayer();
    if(queue->tail == NULL){
        queue->head = player;
        queue->tail = player;
    }
    else{
        queue->tail->next = player;
        queue->tail = queue->tail->next;
    }
    queue->size++;
}

void enQueue(Queue * queue , Player * player){
    if(queue == NULL) return;
    if(queue->tail == NULL){
        queue->head = player;
        queue->tail = player;
    }
    else{
        queue->tail->next = player;
        queue->tail = queue->tail->next;
    }
    queue->size++;

}

Player * deQueue(Queue * queue){
    if(emptyQueue(queue)){
        printf("Nothing to Dequeue");
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

Player * topPlayer(Queue * queue){//topQueue
    if(emptyQueue(queue)) return NULL;
    return queue->head;
}

int getGameNumber(int add){
    static int gameNumber = 0;
    if(add == 0){
        return gameNumber;
    }
    else return gameNumber++;
}

typedef struct Game{
    int gameNumber;
    Player * player1;
    Player * player2;
    int pts1;
    int pts2;
}Game;


void displayGame(Game * game){ //displays the game inputed in the function
    printf("Game number %d\n" , game->gameNumber);
    printf("Player number : %d %s age : %d Number of points : %d\n" , game->player1->id , game->player1->name, game->player1->age , game->pts1);
    printf("Player number : %d %s age : %d Number of points : %d\n" , game->player2->id , game->player2->name, game->player2->age , game->pts2);
}


int playGameRule1(Player * player1 , Player * player2 , Game *game , int *score1  ,int *score2){//have to pass score 1 and 2 by REFERENCE
    int randNum;
    int rounds = 0;

    while(abs(*score1 - *score2) < 3 && rounds < 12){
        randNum = abs(rand() % 10000);
        printf("Number generated %d \n" , randNum);
        printf("It is the turn of %s\n" , player1->name);
        if(multipleOfFive(sumNumbers(randNum))){
            *score1 = *score1 + 1;
            printf("%s gets 1 point\n" , player1->name);
            printf("Total points of %s is %d\n" ,player1->name , *score1);
        }
        else{
            printf("%s gets 0 point\n" , player1->name);
        }
        randNum = abs(rand() % 10000);
        printf("Number generated %d \n" , randNum);
        printf("It is the turn of %s\n" , player2->name);
        if(multipleOfFive(sumNumbers(randNum))){
            *score2 = *score2 + 1;//increment AFTER dereferencing
            printf("%s gets 1 point\n" , player2->name);
            printf("Total points of %s is %d\n" ,player2->name , *score2);
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
    game->pts1 = *score1; 
    game->pts2 = *score2;
    if(*score1 > *score2){
        return 1;
    }
    else if (*score1 < *score2)
    {
        return 2;
    }
    else return 0;
}

int PGCD(int rand1 , int rand2){
    // Handle cases where one or both numbers are 0
    if (rand1 == 0 && rand2 == 0) return 0;
    if (rand1 == 0) return rand2;
    if (rand2 == 0) return rand1;
    
    int pgcd = (rand1 < rand2) ? rand1 : rand2;
    while(pgcd > 0){
        if(rand1 % pgcd == 0 && rand2 % pgcd == 0){
            return pgcd;
        }
        pgcd--;
    }
    return 1;
}

bool numExists(int chiffre, int nombre){
    if (nombre == 0) {
        return (chiffre == 0);
    }
    
    while (nombre > 0) {
        if (nombre % 10 == chiffre) {
            return true;
        }
        nombre /= 10;
    }
    return false;
}

int calculerScore(int rand1, int rand2 , int pgcd) {
    if (pgcd == 0) {
        // If PGCD is 0, check if either number contains 0
        if (numExists(0, rand1) || numExists(0, rand2)) {
            return 1;
        }
        return 0;
    }
    // Extract each number from pgcd
    int temp = pgcd;
    while (temp > 0) {
        int chiffre = temp % 10;
        if (numExists(chiffre, rand1) || numExists(chiffre, rand2)) {
            return 1;  // Score = 1 to add to the player
        }
        temp /= 10;
    }
    if (temp == 0) {//case no pgcd at all
        if (numExists(0, rand1) || numExists(0, rand2)) {
            return 1;
        }
    }
    return 0;//default no points gained
}

int playGameRule2(Player * player1 , Player * player2 , Game *game , int *score1 , int *score2){
    int rounds = 0;
    int rand1 = 0;
    int rand2 = 0;
    int pgcdp1 = 0;//pgcd of player 1
    int pgcdp2 = 0;//pgcd of player 2
    while(abs(*score1 - *score2) < 3){
        //player 1 pgcd
        rand1 = abs(rand() % 10000);
        rand2 = abs(rand() % 10000);
        printf("Turn of %s numbers generated : %d and %d\n" , player1->name , rand1 , rand2);
        pgcdp1 = PGCD(rand1 , rand2);
        printf("PGCD is %d\n" , pgcdp1);
        *score1 = *score1 + calculerScore(rand1,rand2,pgcdp1);
        //player 2 pgcd
        rand1 = abs(rand() % 10000);
        rand2 = abs(rand() % 10000);
        printf("Turn of %s numbers generated : %d and %d\n" , player2->name , rand1 , rand2);
        pgcdp2 = PGCD(rand1 , rand2);
        printf("PGCD is %d\n" , pgcdp2);
        *score2 = *score2 + calculerScore(rand1,rand2,pgcdp2); 
        rounds = rounds + 2;
        if(rounds == 16){
            game->player1 = player1;
            game->player2 = player2;
            game->pts1 = *score1;
            game->pts2 = *score2;
            return -1;
        }
    }
    game->player1 = player1;
    game->player2 = player2;
    game->pts1 = *score1;
    game->pts2 = *score2;
    if(*score1 > *score2){
        return 1;
    }
    else if (*score1 < *score2)
    {
        return 2;
    }
    else return 0;
}

Player* selectPlayer(Queue *F1, Queue *F, Queue *F3) {
    if (F1 != NULL && !emptyQueue(F1)) {
        if (F1->size >= 2) {
            return deQueue(F1);
        }
        else if (F1->size == 1) {
            //Handling if there is only one left in F1 
            if (F != NULL && !emptyQueue(F)) {
                return deQueue(F);
            }
            else {
                return deQueue(F1);
            }
        }
    }
    
    if (F != NULL && !emptyQueue(F)) {
        if (F->size >= 2) {
            return deQueue(F);
        }
        else if (F->size == 1) {
            //Handling if there is only one left in F 
            if (F3 != NULL && !emptyQueue(F3)) {
                return deQueue(F3);
            }
            else {
                return deQueue(F);
            }
        }
    }
    if (F3 != NULL && !emptyQueue(F3)) {
        return deQueue(F3);
    }
    return NULL; //No players available at all 
}

void displayFilesState(Queue *F, Queue *F1, Queue *F3, Queue *LG, Queue *LS) {
    printf("\nETAT DES FILES ET LISTES---------------\n");
    // for F
    printf("File F (Priority Normal - %d players):\n", F->size);
    if (emptyQueue(F)) {
        printf("  Empty\n");
    } else {
        Player *current = F->head;
        int count = 1;
        while (current != NULL) {
            printf("  %d. Player %d: %s (Age: %d, Wins: %d, Losses: %d)\n", 
                   count, current->id, current->name, current->age, 
                   current->gamesWon, current->gamesLost);
            current = current->next;
            count++;
        }
    }
    
    // for F1 just same thing
    printf("\nFile F1 (Priority 1 - %d players):\n", F1->size);
    if (emptyQueue(F1)) {
        printf("  Empty\n");
    } else {
        Player *current = F1->head;
        int count = 1;
        while (current != NULL) {
            printf("  %d. Player %d: %s (Age: %d, Wins: %d, Losses: %d)\n", 
                   count, current->id, current->name, current->age, 
                   current->gamesWon, current->gamesLost);
            current = current->next;
            count++;
        }
    }
    // same thing for F3
    printf("\nFile F3 (Priority 3 - %d players):\n", F3->size);
    if (emptyQueue(F3)) {
        printf("  Empty\n");
    } else {
        Player *current = F3->head;
        int count = 1;
        while (current != NULL) {
            printf("  %d. Player %d: %s (Age: %d, Wins: %d, Losses: %d)\n", 
                   count, current->id, current->name, current->age, 
                   current->gamesWon, current->gamesLost);
            current = current->next;
            count++;
        }
    }
    // Liste LG (Winners)
    printf("\nList LG (Winners - %d players):\n", LG->size);
    if (emptyQueue(LG)) {
        printf("  Empty\n");
    } else {
        Player *current = LG->head;
        int count = 1;
        while (current != NULL) {
            printf("  %d. Player %d: %s (Points: %d, Wins: %d, Losses: %d)\n", 
                   count, current->id, current->name, current->cumulativepts,
                   current->gamesWon, current->gamesLost);
            current = current->next;
            count++;
        }
    }
    
    // Liste LS (Losers)
    printf("\nList LS (Losers - %d players):\n", LS->size);
    if (emptyQueue(LS)) {
        printf("  Empty\n");
    } else {
        Player *current = LS->head;
        int count = 1;
        while (current != NULL) {
            printf("  %d. Player %d: %s (Wins: %d, Losses: %d)\n", 
                   count, current->id, current->name,
                   current->gamesWon, current->gamesLost);
            current = current->next;
            count++;
        }
    }
    printf("------------------------------------------------\n");
}

void sortLG(Queue *LG) {
    if (LG == NULL || LG->size < 2) return;
    printf("\n=== Sorting LG by cumulative points (descending) ===\n");
    bool inversed;
    do {
        inversed = false;
        Player *current = LG->head;
        Player *prev = NULL;
        
        while (current != NULL && current->next != NULL) {
            if (current->cumulativepts < current->next->cumulativepts) {
                // Échanger les deux nœuds
                Player *temp = current->next;
                current->next = temp->next;
                temp->next = current;
                
                if (prev == NULL) {
                    LG->head = temp;
                } else {
                    prev->next = temp;
                }
                
                // Mettre à jour tail si on échange le dernier
                if (current->next == NULL) {
                    LG->tail = current;
                }
                
                prev = temp;
                inversed = true;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (inversed);
    printf("LG sorted! Total players: %d\n", LG->size);//reminder of total players
}

void displayPlayerLosses(Queue *F, Queue *F1, Queue *F3, Queue *LG , int numLoss) {//search for players with GamesWon == 0
    printf("\n=== PLAYERS WITH %d WINS ===\n" , numLoss);
    bool found = false;
    
    // Vérifier dans F
    Player *current = F->head;
    while (current != NULL) {
        if (current->gamesLost == numLoss) {
            printf("  Player %d: name %s (File F)\n", current->id, current->name);
            found = true;
        }
        current = current->next;
    }
    
    // Vérifier dans F1
    current = F1->head;
    while (current != NULL) {
        if (current->gamesLost == numLoss) {
            printf("  Player %d: name %s (File F1)\n", current->id, current->name);
            found = true;
        }
        current = current->next;
    }
    
    // Vérifier dans F3
    current = F3->head;
    while (current != NULL) {
        if (current->gamesLost == numLoss) {
            printf("  Player %d: name %s (File F3)\n", current->id, current->name);
            found = true;
        }
        current = current->next;
    }
    if (!found) {//just the case that no players at all have losses of numLoss
        printf("  No players have %d losses\n" , numLoss);
    }
}


void displayPlayerWins(Queue *F, Queue *F1, Queue *F3, Queue *LG , int numWins) {//search for players with GamesWon == 0
    printf("\n=== PLAYERS WITH %d WINS ===\n" , numWins);
    bool found = false;
    
    // Vérifier dans F
    Player *current = F->head;
    while (current != NULL) {
        if (current->gamesWon == numWins) {
            printf("  Player %d: name %s (File F)\n", current->id, current->name);
            found = true;
        }
        current = current->next;
    }
    
    // Vérifier dans F1
    current = F1->head;
    while (current != NULL) {
        if (current->gamesWon == numWins) {
            printf("  Player %d: name %s (File F1)\n", current->id, current->name);
            found = true;
        }
        current = current->next;
    }
    
    // Vérifier dans F3
    current = F3->head;
    while (current != NULL) {
        if (current->gamesWon == numWins) {
            printf("  Player %d: name %s (File F3)\n", current->id, current->name);
            found = true;
        }
        current = current->next;
    }
    if (!found) {//just the case that no players at all have numWins
        printf("  No players have %d wins\n" , numWins);
    }
}



int main(){
    bool quit = false;
    int numPlayers = 0;
    Game games[100];
    int numGames = 0;
    //starting of game with rule set 1
    int score1 = 0;
    int score2 = 0;
    int results = 0;
    Queue *F = malloc(sizeof(Queue)); // creating F
    initQueue(F); // initializing queue
    Queue *F1 = malloc(sizeof(Queue));//creating the queue of priority 1
    initQueue(F1);
    Queue *F3 = malloc(sizeof(Queue));
    initQueue(F3);
    //to not repeat primitives we can just declare LG and LS as queues instead of lists and treat them with their list properties
    Queue * LG = malloc(sizeof(Queue));
    initQueue(LG);
    Queue * LS = malloc(sizeof(Queue));
    initQueue(LS);
    

    printf("Game initialization!\n");
    printf("Input the number of players!\n");
    scanf("%d" , &numPlayers);
    getchar();//AGAIN having to take the \n (possibility of using fflush() too)
    
    for(int i = 0; i < numPlayers; i++){
        createEnQueue(F);
    }
    Player * player1;
    Player * player2;
    for(int i = 0; i < 3*numPlayers; i++){
        Game game;
        game.gameNumber = getGameNumber(1);//putting one as an argument activates the increment putting 0 returns the game number of static variable as is 
        if(results == 0){//results start at 0 so at the beggining we pick two players
        player1 = selectPlayer(F1,F,F3) ;
        player2 = selectPlayer(F1,F,F3);
        }
        else if(results == 1){
            player2 = selectPlayer(F1,F,F3);
            if(player1 == NULL){//so this if statemnt is for if the player1 becomes null because it has been put inside LG or LS
                player1 = selectPlayer(F1,F,F3);
            }
        }
        else if(results ==2) {
            player1 = selectPlayer(F1,F,F3);
            if(player2 == NULL){
                player2 = selectPlayer(F1,F,F3);
            }
        }


        if (player1 == NULL || player2 == NULL){//verify that before game p1 and p2 are not null
            printf("Player1 or 2 are null before game"); break;
        }

        
        printf("Selected players: %s (ID: %d) vs %s (ID: %d)\n",player1->name, player1->id, player2->name, player2->id);
        //play game with rule1
        score1 = 0; score2 = 0;
        results = playGameRule1(player1, player2 , &game , &score1 ,&score2 );
        games[numGames++] = game;
        if(results == 2){//if player 2 won
            player2->gamesWon++;
            player1->gamesLost++;
            player2->cumulativepts = player2->cumulativepts + score2;
            player2->winStreak++;
            player1->winStreak = 0; //set winstreak of loser to zero
            //player2
            if(player2->gamesWon == 5){
                printf("Player : %s now has five wins he is on the winner's list" , player2->name); 
                enQueue(LG , player2);
                player2 = NULL;

            }
            else if(player2->winStreak == 3){
                enQueue(F1,player2);
                player2 = NULL;
            }

            if(player1->gamesLost == 5){
                printf("Player : %s now has five losses he is on the losers's list" , player1->name); 
                enQueue(LS , player1);
                player1 = NULL;
            }
            else if(player1->gamesLost == 3){
                enQueue(F3,player1);
                player1 = NULL;
            }
            else {
                enQueue(F , player1);
                player1 = NULL;
            }
        }
        else if(results == 1){//if player 1 won
            player1->gamesWon++;
            player2->gamesLost++;
            player1->cumulativepts = player1->cumulativepts + score1;
            player2->cumulativepts = player2->cumulativepts + score2;
            player1->winStreak++;
            player2->winStreak = 0; //set winstreak of loser to zero
            //player1
            if(player1->gamesWon == 5){
                printf("Player : %s now has five wins he is on the winner's list" , player1->name); 
                enQueue(LG , player1);
                player1 = NULL;
            }
            else if(player1->winStreak == 3){
                enQueue(F1,player1);
                player1 = NULL;
            }
            if(player2->gamesLost == 5){
                printf("Player : %s now has five losses he is on the losers's list" , player2->name); 
                enQueue(LS , player2);
                player2 = NULL;
            }
            else if(player2->gamesLost == 3){
                enQueue(F3,player2);
                player2 = NULL;
            }
            else{
                enQueue(F , player2);
                player2 = NULL;
            }
        }
        if(results == 0){ // Égalité
            printf("\nDraw! Both players go to end of F\n");
            enQueue(F, player1);
            enQueue(F, player2);
            player1 = NULL;
            player2 = NULL;
        }

        
        displayGame(&game);//displays the last game results 
/*
       if(emptyQueue(F) && emptyQueue(F1) && emptyQueue(F3)){
    if(player1 != NULL){
        enQueue(F , player1);
    }
    if(player2 != NULL){
        enQueue(F , player2);
    }
    // Only break if we also can't select players
    Player *test1 = selectPlayer(F1,F,F3);
    Player *test2 = selectPlayer(F1,F,F3);
    if(test1 == NULL || test2 == NULL){
        if(test1) enQueue(F, test1);  // Put back if we got one
        if(test2) enQueue(F, test2);  // Put back if we got one
        break;
    } else {
        // Put them back and continue
        enQueue(F, test1);
        enQueue(F, test2);
    }
} */
        }

    

    displayPlayerWins(F,F1,F3,LG,1);//display players with no wins
    displayPlayerWins(F,F1,F3,LG,2);
    displayPlayerWins(F,F1,F3,LG,3);

    displayPlayerLosses(F,F1,F3,LG,1);
    displayPlayerLosses(F,F1,F3,LG,2);
    displayPlayerLosses(F,F1,F3,LG,3);

    displayFilesState(F,F1,F3,LG,LS);//Displays all the state of all queues

    int numGamesSrat2 = 0; //keeps track of the number of games done in second strategy
    while(!emptyQueue(F) || !emptyQueue(F1) || !emptyQueue(F3)){//SECOND RULESET
        if (numGames >= 100) break;
        if(numGamesSrat2 == 2*numPlayers){
            while(!emptyQueue(F1)){
                enQueue(LG , deQueue(F1));
            }
            while(!emptyQueue(F)){
                enQueue(LS , deQueue(F));
            }
            while(!emptyQueue(F3)){
                enQueue(LS , deQueue(F3));
            }
            break;
        }
        Game game; 
        game.gameNumber = getGameNumber(1);
        numGamesSrat2++;
        if(results == 0 || results == -1){//0 means last game was equality minus one means game ended because we reached 16 rounds thus it allows us to between the two cases to know where to put the losing and winning player
        player1 = selectPlayer(F1,F,F3) ;
        player2 = selectPlayer(F1,F,F3);
        }
        else if(results == 1){
            player2 = selectPlayer(F1,F,F3);
            if(player1 == NULL){
                player1 = selectPlayer(F1,F,F3);
            }
        }
        else if (results == 2){
            player1 = selectPlayer(F1,F,F3);
            if(player2 == NULL){
                player2 = selectPlayer(F1,F,F3);
            }
        }
        if (player1 == NULL || player2 == NULL) {
            printf("Not enough players to continue. Ending tournament.\n");
            // Move any remaining players to appropriate lists
            while(!emptyQueue(F1)){
                enQueue(LG , deQueue(F1));
            }
            while(!emptyQueue(F)){
                // Decide based on win/loss ratio
                Player* p = deQueue(F);
                if(p->gamesWon > p->gamesLost){
                    enQueue(LG , p);
                } else {
                    enQueue(LS , p);
                }
            }
            while(!emptyQueue(F3)){
                enQueue(LS , deQueue(F3));
            }
            break;
        }

        printf("Selected players: %s (ID: %d) vs %s (ID: %d)\n",player1->name, player1->id, player2->name, player2->id);
        score1 = 0; score2 = 0;
        
        results = playGameRule2(player1, player2 , &game , &score1, &score2);//Second ruleset Game
         
        games[numGames++] = game;
        if(results == 2){//if player 2 won
            player2->gamesWon++;
            player1->gamesLost++;
            player1->newLosses++;
            player1->cumulativepts = player1->cumulativepts + score1; 
            player2->cumulativepts = player2->cumulativepts + score2;
            player2->winStreak++;
            player1->winStreak = 0; //set winstreak of loser to zero
            //player2
            if(player2->winStreak == 2){
                printf("Player : %s now has two wins in a row he is on the winner's list\n" , player2->name); 
                enQueue(LG , player2);
                player2 = NULL;
            }
            if(player1->newLosses == 2){
                printf("Player : %s now has two losses in the new ruleset he is on the losers's list\n" , player1->name); 
                enQueue(LS,player1);
                player1 = NULL;
            }
            else {
                enQueue(F , player1);
                player1 = NULL;
            }
        }
        if(results == 1){//if player 1 won
            player1->gamesWon++;
            player2->gamesLost++;
            player1->cumulativepts = player1->cumulativepts + score1; 
            player2->cumulativepts = player2->cumulativepts + score2;
            player2->newLosses++;
            player1->winStreak++;
            player2->winStreak = 0; //set winstreak of loser to zero
            //player1
            if(player1->winStreak == 2){
                printf("Player : %s now has two wins in a row he is on the winner's list\n" , player1->name); 
                enQueue(LG , player1);
                player1 = NULL;
            }
            if(player2->newLosses == 2){
                printf("Player : %s now has two losses in the new ruleset he is on the losers's list\n" , player2->name); 
                enQueue(LS,player2);
                player2 = NULL;
            }
            else {
                enQueue(F , player2);
                player2 = NULL;
            }

        }
        if(results == -1){//Case if the game stopped because of 16 rounds rule not 3 points difference rule
            if(score1 < score2){
                enQueue(F , player2);
                player2 = NULL;
                enQueue(F3 , player1);
                player1 = NULL;
            }
            else if(score1 > score2){
                enQueue(F , player1);
                player1 = NULL;
                enQueue(F3 , player2);
                player2 = NULL;
            }
        }
        if(results == 0 || score1 == score2){//the second case is for if results are -1 so the game stopped because of 16 rounds rule but score 1 is equal to score 2
            enQueue(F , player1);
            enQueue(F , player2);
            player1 = NULL;
            player2 = NULL;
        }
        displayGame(&game);
    }

    //display the three first winners (three first inside LG)
    Player *current = LG->head;
    int count = 0;
    while(current != NULL && count < 3){
        printf("  Player %d: %s (File F)\n", current->id, current->name);
        current = current->next;
        count++;
    }

    displayPlayerWins(F,F1,F3,LG,0);//display players with no wins
    displayPlayerWins(F,F1,F3,LG,1);//display players with 1 win etc
    displayPlayerWins(F,F1,F3,LG,2);


    displayPlayerLosses(F,F1,F3,LG,1);
    displayPlayerLosses(F,F1,F3,LG,2);

    sortLG(LG);//Sorting the list gagnant of winners 


    displayFilesState(F,F1,F3,LG,LS);//Displays all the state of all queues

    free(F);
    free(F1);
    free(F3);
    free(LG);
    free(LS);
    return 0;
}