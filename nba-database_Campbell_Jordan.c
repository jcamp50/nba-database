#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 30 

//player struct
typedef struct{

    //player components
    char name[SIZE];
    int age;
    char team[SIZE];
    char pos[SIZE];
    double ppg;
    
}player_t;

void hardcodeDB(player_t players[], int *total); //Populate and insert 6 initial records
void displayOptions(int *choice);//Show menu options
void displayPlayers(player_t players[], int *total); //Show all records in the database
player_t insertPlayer(); //Insert a new record
int searchPlayer(player_t players[], int *total); //Search for a record
void removePlayer(player_t players[], int *total); //Remove a record
char* strlower(char string[]); //lowercase a full string

int main()
{   
    //Open file to write records to
    FILE *fptr = fopen("Records.txt", "w"); 

    if(fptr == NULL) //Check if file opened properly
    {
       printf("Records file did not open successfully!\n");
    }
    else
    {
        //total variable will track total records
        int total; 
        int *totalptr = &total;

        int choice = 0;
        int *choiceptr = &choice;

        printf("Welcome to the 2022 NBA Player Database\n");
        
        player_t nbaPlayers[SIZE]; //Array of player_t structs

        hardcodeDB(nbaPlayers, totalptr);
        

        while(choice != 5) //Repeat while user doesn't choose 5 (exit)
        {
            //show menu
            displayOptions(choiceptr);

            switch(choice)
            {
                case 1:
                    if(total == SIZE) //Don't allow insertation of a record if database if full
                    {
                        printf("Database full! Please remove a record before adding another\n");
                        break;
                    }
                    else
                    {
                        nbaPlayers[total] = insertPlayer(); //store record returned by insert into record array
                        total++; //increment totat records
                        break;
                    }

                case 2:
                    //if choice is 2 call remove function
                    removePlayer(nbaPlayers, totalptr);
                    break;

                case 3:
                    //if choice is 3 call search function
                    searchPlayer(nbaPlayers, totalptr);
                    break;

                case 4:
                    //if choice is 4 call display function
                    displayPlayers(nbaPlayers, totalptr);
                    break;

                default:
                    break;
            }
        }

        printf("Now exiting...\n");

  
        fprintf(fptr, "2022 NBA Player Records\n");
        for(int i = 0; i < total; ++i) //traverse database up to value of total (number of records)
        {
            //Write the components of each struct at i to the file
            fprintf(fptr, "=================================================================\n");
            fprintf(fptr, "Player Name:       %s", nbaPlayers[i].name);
            fprintf(fptr, "Player Age:        %d\n", nbaPlayers[i].age); 
            fprintf(fptr, "Player Team:       %s", nbaPlayers[i].team);
            fprintf(fptr, "Player Position:   %s\n", nbaPlayers[i].pos);
            fprintf(fptr, "Player PPG:        %.1lf\n", nbaPlayers[i].ppg);
        }
        fprintf(fptr, "=================================================================\n");
    }

    //close file pointer
    fclose(fptr);

    return 0;
}

void displayOptions(int *choice)
{
    char trash[SIZE];
    int x = 0;

    do{
        //Display menu
        printf("=================================================================\n");
        printf("Please choose one of the following options\n");
        printf("1. Insert a new player into the database\n");
        printf("2. Remove a player from the database\n");
        printf("3. Search for a player in the database\n");
        printf("4. Display all players in the database\n");
        printf("5. Exit the database\n");
        printf("=================================================================\n");
        printf("Choice: ");
        if(scanf("%d", &x) != 1) //if scanf did not properly read int
        {
            fgets(trash, SIZE, stdin); //store input in trash string
        }
    }while(x < 1 || x > 5); //repeat while input is invalid

    *choice = x; //Value at dereferenced choice ptr is set to x
}
void hardcodeDB(player_t players[], int *total)
{
    //Create 6 players to fill the array
    player_t player1;
    strcpy(player1.name, "Luka Doncic\n");
    player1.age = 23;
    strcpy(player1.team, "Dallas Mavericks\n");
    strcpy(player1.pos, "PG");
    player1.ppg = 33.1;

    player_t player2;
    strcpy(player2.name, "Stephen Curry\n");
    player2.age = 34;
    strcpy(player2.team, "Golden State Warriors\n");
    strcpy(player2.pos, "PG");
    player2.ppg = 31.4 ;

    player_t player3;
    strcpy(player3.name, "Giannis Antetokounmpo\n");
    player3.age = 27;
    strcpy(player3.team, "Milwaukee Bucks\n");
    strcpy(player3.pos, "PF");
    player3.ppg = 30.9 ;

    player_t player4;
    strcpy(player4.name, "Kevin Durant\n");
    player4.age = 34;
    strcpy(player4.team, "Brooklyn Nets\n");
    strcpy(player4.pos, "PF");
    player4.ppg = 29.3 ;

    player_t player5;
    strcpy(player5.name, "Jason Tatum\n");
    player5.age = 24;
    strcpy(player5.team, "Boston Celtics\n");
    strcpy(player5.pos, "SF");
    player5.ppg = 30.5 ;

    player_t player6;
    strcpy(player6.name, "Lebron James\n");
    player6.age = 37;
    strcpy(player6.team, "Los Angeles Lakers\n");
    strcpy(player6.pos, "SF");
    player6.ppg = 25.8 ;

    //Assign players to the first 6 positions of the array
    players[0] = player1;
    players[1] = player2;
    players[2] = player3;
    players[3] = player4;
    players[4] = player5;
    players[5] = player6;

    *total = 6; //set total to 6

}

void displayPlayers(player_t players[], int *total)
{
    printf("=================================================================\n");
    printf("Displaying all players in database\n");

    //traverse the array from index 0  up to total (num elements in array)
    for(int i = 0; i < *total; ++i)
    {
        printf("=================================================================\n");
        //display each component of record at index i
        printf("Player Name:       %s", players[i].name);
        printf("Player Age:        %d\n", players[i].age); 
        printf("Player Team:       %s", players[i].team);
        printf("Player Position:   %s\n", players[i].pos);
        printf("Player PPG:        %.1lf\n", players[i].ppg);
    }

}

player_t insertPlayer()
{
    //Declare a new player_t type struct
    player_t newPlayer;
    

    int result;

    //Declare trash string
    char trash[SIZE];

    printf("=================================================================\n");
    printf("Enter Information for the player you want to insert\n");
    printf("=================================================================\n");
    printf("Enter player first and last name: ");
    fgets(trash, SIZE, stdin); //clear \n appended to printf statement
    fgets(newPlayer.name, SIZE, stdin); //store user input in newPlayer name
    

    do{
        
        printf("Enter player age: ");
        result = scanf("%d", &newPlayer.age); //store user input in newPlayer age
        if(result != 1) //if scanf did not properly read int
        {
            fgets(trash, SIZE, stdin); //store input in trash string
            printf("Please enter a positive integer for age\n");
        }
        else if(newPlayer.age < 0) //Invalid age entered
        {
            printf("Please enter a positive integer for age\n");
        }
    }while(result != 1 || newPlayer.age < 0); //while input is invalid
    


    printf("Enter player team: ");
    fgets(trash, SIZE, stdin); //clear \n appended to printf statement
    fgets(newPlayer.team, SIZE, stdin); //store user input in newPlayer team

    do{
        printf("Enter player position: ");
        scanf("%s", newPlayer.pos); //store user input in newPlayer pos
        if(strcmp(newPlayer.pos, "PG") != 0 && strcmp(newPlayer.pos, "PF") != 0 && strcmp(newPlayer.pos, "SG") != 0 && strcmp(newPlayer.pos, "SF") != 0 && strcmp(newPlayer.pos, "C") != 0)
        {
            printf("Please one of the following positions: PG, PF, SG, SF, C\n");
        }

        
    }while(strcmp(newPlayer.pos, "PG") != 0 && strcmp(newPlayer.pos, "PF") != 0 && strcmp(newPlayer.pos, "SG") != 0 && strcmp(newPlayer.pos, "SF") != 0 && strcmp(newPlayer.pos, "C") != 0);
    //repeat while improper position entered
    
    do{
        printf("Enter player PPG: ");
        result = scanf("%lf", &newPlayer.ppg); 
        if(result != 1)//if scanf did not properly read double
        {
            fgets(trash, SIZE, stdin); //store input in trash string
            printf("Please enter a positive decimal or integer  for PPG\n");
        }
        else if(newPlayer.ppg < 0) //Invalid age entered
        {
            printf("Please enter a positive decimal or integer for PPG\n");
        }

    }while(result != 1 || newPlayer.ppg < 0);
    //while input is invalid

    return newPlayer; //return the newplayer struct 

}

int searchPlayer(player_t players[], int *total)
{
    char trash[SIZE];
    char searchName[SIZE]; //name to search for
    int found = 0; //found true/false
    int searchIdx = 100;
    char searchLwr[SIZE]; //lowercase search name
    char playerLwr[SIZE]; //lowercase player name
    char tempName[SIZE];

    int i = 0;

    printf("=================================================================\n");
    printf("Enter the name of the player to search for: ");
    fgets(trash, SIZE, stdin); //clear \n appended to printf statement
    if(strcmp(trash, "\n") == 0) //if trash holds \n
    {
        fgets(searchName, SIZE, stdin); //read input and store in searchName
    }
    else
    {
        strcpy(searchName, trash); //copy trash in to searchName
    }

    strcpy(searchLwr, strlower(searchName)); //copy lowercase searchName to searchLwr
    
    while(i < *total && found == 0) //while total records has not been reached and found is false;
    {
        //copy player at i name
        strcpy(tempName, players[i].name);
        //lowercase the copy and copy it to playerLwr
        strcpy(playerLwr, strlower(tempName));

        //compare normal and lowercase names
        if(strcmp(players[i].name, searchName) == 0 || strcmp(playerLwr, searchLwr) == 0)
        {
            searchIdx = i; //set searchIdx to the index the player was found at
            found = 1; //set found to true    
        }
        i++; //increment i
    }

    if(found == 1) //if found is true
    {
        //Display all components for player at searchIdx
        printf("Player found!\n");
        printf("=================================================================\n");
        printf("Player Name:       %s", players[searchIdx].name);
        printf("Player Age:        %d\n", players[searchIdx].age); 
        printf("Player Team:       %s", players[searchIdx].team);
        printf("Player Position:   %s\n", players[searchIdx].pos);
        printf("Player PPG:        %.1lf\n", players[searchIdx].ppg);

    }
    else
    {
        printf("Player not found!\n");
    }

    return searchIdx; //return index player was found at, or 100 if not found
}

char* strlower(char string[])
{

    for(int i = 0; i < strlen(string); ++i) //for the every char in string
    {
        string[i] = tolower(string[i]); //char at i is set to lowercase;
    }

    return string; //return lowercase string
}

void removePlayer(player_t players[], int *total)
{
    
    int result = 0;

    printf("=================================================================\n");
    printf("Checking if the player to remove exists in the database\n");

    //searchPlayer() return the index of a player if found, returns 100 if not
    result = searchPlayer(players, total);
    
    if(result != 100) //if player found
    {
        printf("=================================================================\n");
        printf("Removing %s", players[result].name); //print name of player to be removed

        //from index of player to be removed up to total
        for(int i = result; i < *total; ++i)
        {   
            //set struct at i to be struct at i + 1
            players[i] = players[i + 1];
        }

        *total -= 1;
        /*
            Record at the last index before total can no longer be accessed after total was shifted -1
            It will get overwritten when user inputs a new record at total
        */
    }


}
