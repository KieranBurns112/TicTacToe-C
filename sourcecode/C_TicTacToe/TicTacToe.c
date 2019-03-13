#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void declutter() {
  //Make 20 blank lines to declutter the game suface
  for (int i = 0; i < 30; i++) {
    printf(" \n");
  }
}

void introText() {
  //Text for "homescreen" of game
  declutter();
  printf("Welcome to Kieran's C CMD TicTacToe!\n");
  printf("The rules are simple!\n");
  printf("Two opponents take turns placing a marker in a 3x3 grid.\n");
  printf("The goal is to line up three of your markers in a straight line!\n");
  printf("(The straight line can be horizontal, vertical or diagonal)\n \n");
  printf("The game will indicate when it is a players turn, and will\n");
  printf("require keyboard input followed by the 'Enter' key.\n");
  printf("The format for input is as follows:'ColumnRow'.\n");
  printf("For example, if you wish to input your piece into Column A, Row 1\n");
  printf("then the input will be 'A1'.\n");
  printf("Moves can be Undone by entering 'Undo'.\n");
  printf("You can end a game at any time with the 'Home' command.\n \n");
}

void homeText(){
  printf("- To Play a game, type 'Play' then press the 'Enter' key.\n");
  printf("- To Replay a previous game, type 'Replay' then press the 'Enter' key.\n");
  printf("- To Exit, type 'Quit' then press the 'Enter' key.\n \n \n");
}

int homeScreen() {
  int choice = 0; //Variable to determine what should be currently being done
  char userInput[6]; //Variable to store raw text input from the user

  homeText();

  while (choice == 0) { //Loop until a choice is made
    printf("> ");
    scanf("%s",userInput); //Take input from user

    //Loop through all input characters and set them all to lower case for
    //processing.
    for(int i = 0; i < 7; i++) {
      userInput[i] = tolower(userInput[i]);
    }
    //

    //Handle each possible user input to decide what the program should be
    //doing.
    if (strcmp(userInput, "quit") == 0 || strcmp(userInput, "'quit'") == 0) {
      choice = -1; //Set action to end the program.
    }
    else if (strcmp(userInput, "play") == 0 || strcmp(userInput, "'play'") == 0) {
      choice = 1; //Set action to start playing a game.
    }
    else if (strcmp(userInput, "replay") == 0 || strcmp(userInput, "'replay'") == 0) {
      choice = 2; //Set action to open the replay menu.
    }
    else {
      printf("Invalid Input! Try 'Play', 'Replay', or 'Quit'!\n \n \n");
    }
    //
  }
  return choice;
}

//Removes '\n' character from lines for reading in commands and names.
char *removeNewline(char *inLine) {
  for (int i = 0; i < strlen(inLine); i++) {
    if (inLine[i] == '\n') {
      inLine[i] = 0;
    }
  }
  return inLine;
}
//

void game(int saveLocation) {
  char player1[15];
  char player2[15];
  int nameConfirm = 0;
  int gameOver = 0;
  int skipping = 0;
  char board[3][3]; //Each Var can be X or O
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y <3; y++) {
      board[x][y] = '.';
    }
  }
  int currentTurn = 1; //Can be 1 or 2 (1 = player 1, 2 = player 2)
  FILE *currentGame;
  int fileLine = 0;
  char filename[30];

  if (saveLocation == 0) {  //If a save is not being loaded
    while (nameConfirm == 0) {
      int playerValid;

      printf("Enter Player Names:\n");

      //Take in player 1's name
      printf("Player 1 (X):\n\n");
      playerValid = 0;
      while (playerValid == 0) {
        printf("> ");
        scanf("%s",player1);
        if(strlen(player1) > 15) {
          printf("\n\n Invalid Name, Name must be below 16 Characters!\n\n\n");
        }
        else {
          playerValid = 1;
        }
      }
      //

      //Take in player 2's name
      printf("\n \nPlayer 2 (O):\n \n");
      playerValid = 0;
      while (playerValid == 0) {
        printf("> ");
        scanf("%s",player2);
        if(strlen(player2) > 15) {
          printf("\n\n Invalid Name, Name must be below 16 Characters!\n\n\n");
        }
        else {
          playerValid = 1;
        }
      }
      //

      declutter(); //Clean the Screen

      //Display both players names in an X vs Y format with character based
      //boxes.
      printf("|----------------|      |----------------|\n");
      printf("|%s",player1);
      for (int nameLength = strlen(player1); nameLength < 16; nameLength++) {
        printf(" ");
      }
      printf("|  VS  ");
      printf("|%s", player2);
      for (int nameLength = strlen(player2); nameLength < 16; nameLength++) {
        printf(" ");
      }
      printf("|\n");
      printf("|----------------|      |----------------|\n");
      //

      //Confirm play with the two given names
      printf("\n \nPlay with these Names? (y/n)\n \n");

      char yesno[2];
      int ynConfirm = 0;

      while (ynConfirm == 0) {
        printf("> ");
        scanf("%s", yesno);
        for(int i = 0; i < 3; i++) {
          yesno[i] = tolower(yesno[i]);
        }

        if (strcmp(yesno, "y") == 0 || strcmp(yesno, "'y'") == 0)  {
          declutter();
          nameConfirm = 1;
          ynConfirm = 1;
        }
        else if (strcmp(yesno, "n") == 0 || strcmp(yesno, "'n'") == 0)  {
          declutter();
          ynConfirm = 1;
        }
        else {
          printf("\n \n Try 'y' or'n'!\n \n");
        }
      }
    }

    //Check existing game logs to create new uniquely named game log
    FILE *ar = fopen("allReplays.txt", "a+");
    int lines = 0;
    char read;
    if (ar != NULL) {
      lines += 1;
      while(!feof(ar)) {
        read = fgetc(ar);
        if (read == '\n')
        {
          lines += 1;
        }
      }
    }
    sprintf(filename, "replays/%d.txt", (lines));
    fputs(filename, ar);
    fputs("\n", ar);
    fclose(ar);
    //

    currentGame = fopen(filename, "w+");  //Create and Open the file for the
                                          //current game.

    //Add Player names to the current game file
    fputs(player1, currentGame);
    fputs("\n", currentGame);
    fputs(player2, currentGame);
    fputs("\n", currentGame);
    fileLine += 2;
    //
  }
  else { //If a save is being loaded
    sprintf(filename, "replays/%d.txt", (saveLocation));
    currentGame = fopen(filename, "r+");   //Open selected file for Reading
                                          //and writing.

    //Load in names for player1 and player2, which should be the first 2
    //lines of a vaild save file.
    fgets(player1, 15, currentGame);
    removeNewline(player1);
    fgets(player2, 15, currentGame);
    removeNewline(player2);
    fileLine += 2;
    //

    char readPosition[5]; //Variable to store read in position from file

    while(fgets(readPosition, 5, currentGame)) { //Read in next line of file if
                                                //one exists.

      //Remove ' ' from read in position
      int checkPos = 0;
      if (readPosition[0] == '\'') {
        checkPos = 1;
      }
      //

      //Place marker for loaded in position on the board
      //[ALTERNATE VERSION OF CODE USED IN ACTUAL GAME LOOP BELOW]
      int desiredX;
      int desiredY;

      if (readPosition[checkPos] == 'a') {
        desiredX = 0;
      }
      else if (readPosition[checkPos] == 'b') {
        desiredX = 1;
      }
      else if (readPosition[checkPos] == 'c') {
        desiredX = 2;
      }

      if (readPosition[checkPos + 1] == '1') {
        desiredY = 0;
      }
      else if (readPosition[checkPos + 1] == '2') {
        desiredY = 1;
      }
      else if (readPosition[checkPos + 1] == '3') {
        desiredY = 2;
      }

      if (currentTurn == 1) {
        board[desiredX][desiredY] = 'X';
        currentTurn += 1;
      }
      else {
        board[desiredX][desiredY] = 'O';
        currentTurn -= 1;
      }

      fileLine += 1;
      //
    }

    skipping = 1; //Skip playing phase of first turn to ensure the correct
                  //instuctions are shown in the case that the loaded game
                  //has already been won and requires an 'undo' action.
  }


  while (gameOver == 0) {
    if (skipping == 0) {
      //Display Game Board
      printf("    A  %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
      printf("      ---+---+---\n");
      printf("    B  %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
      printf("      ---+---+---\n");
      printf("    C  %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
      printf("       1   2   3 \n");
      //

      //Display Current Player's turn

      if (currentTurn == 1) {
        printf("\n \n  %s's Turn! (X):\n \n \n", player1);
      }
      else if (currentTurn == 2) {
        printf("\n \n  %s's Turn! (O):\n \n \n", player2);
      }
      //

      int turnOver = 0;    //Indicate that it's still a player's turn
      char userInput[5];  //Variable to hold user input
      while (turnOver == 0) {
        //Accept Current Player's action
        printf("> ");
        scanf("%s",userInput);
        for(int i = 0; i < 6; i++) {
          userInput[i] = tolower(userInput[i]);
        }
        //

        //Check in case user is using ' ' around their input
        int checkPos = 0;
        if (userInput[0] == '\'') {
          checkPos = 1;
        }

        int inputError = 0; //1 = Invalid input format, 2 = Space in use
                            //3 = No more Undo actions

        //Validate each possible user input to decide what the program should
        //be.
        if (userInput[checkPos] == 'a' || userInput[checkPos] == 'b' || userInput[checkPos] == 'c') {
          if (userInput[checkPos + 1] == '1' || userInput[checkPos + 1] == '2' || userInput[checkPos + 1] == '3') {
            int desiredX;
            int desiredY;
            if (userInput[checkPos] == 'a') {
              desiredX = 0;
            }
            else if (userInput[checkPos] == 'b') {
              desiredX = 1;
            }
            else if (userInput[checkPos] == 'c') {
              desiredX = 2;
            }

            if (userInput[checkPos + 1] == '1') {
              desiredY = 0;
            }
            else if (userInput[checkPos + 1] == '2') {
              desiredY = 1;
            }
            else if (userInput[checkPos + 1] == '3') {
              desiredY = 2;
            }

            if (board[desiredX][desiredY] == '.') {
              if (currentTurn == 1) {
                board[desiredX][desiredY] = 'X';
              }
              else {
                board[desiredX][desiredY] = 'O';
              }
              fputs(userInput, currentGame);
              fputs("\n", currentGame);
              fileLine += 1;
              turnOver = 1;
            }
            else {
              inputError = 2;
            }
          }
          else {
            inputError = 1;
          }
        }
        else if (strcmp(userInput, "undo") == 0 || strcmp(userInput, "'undo'") == 0)  {
          if (fileLine > 2) {
            char removeLine[5]; //The position to remove
            fclose(currentGame);  //Close file that's open for editing
            FILE *gameRemoveTurn = fopen(filename, "r");

            //Find the position to remove
            for (int i = 0; i < fileLine + 2; i++)
            {
              fgets(removeLine, 5, gameRemoveTurn);
            }
            //

            fclose(gameRemoveTurn);

            removeNewline(removeLine);

            //Change board marker at desired location back to '.'
            //[ALTERNATE VERSION OF CODE USED ABOVE]
            int checkPos = 0;
            if (userInput[0] == '\'') {
              checkPos = 1;
            }

            int desiredX;
            int desiredY;

            if (removeLine[checkPos] == 'a') {
              desiredX = 0;
            }
            else if (removeLine[checkPos] == 'b') {
              desiredX = 1;
            }
            else if (removeLine[checkPos] == 'c') {
              desiredX = 2;
            }

            if (removeLine[checkPos + 1] == '1') {
              desiredY = 0;
            }
            else if (removeLine[checkPos + 1] == '2') {
              desiredY = 1;
            }
            else if (removeLine[checkPos + 1] == '3') {
              desiredY = 2;
            }

            board[desiredX][desiredY] = '.';
            //

            currentGame = fopen(filename, "r"); //Reopen editing file on line 1
            FILE *tempFile = fopen("temp.txt", "w"); //open a temp file
            char tempLine[30];
            int tempLineNumber = 0;

            //Add every line from the original file to the temp file except
            //the one that's being removed.
            while(fgets(tempLine, 30, currentGame)) {
              tempLineNumber += 1;
              if (tempLineNumber != fileLine) {
                fputs(tempLine, tempFile);
              }
            }
            //

            //Close both open files
            fclose(currentGame);
            fclose(tempFile);
            //

            //Delete the original file and rename the temp file to the original
            //to take it's place.
            remove(filename);
            rename("temp.txt", filename);
            //

            //Open the "new" original file and head to the end of the file to
            //be added on to with new turns.
            currentGame = fopen(filename, "r+");
            while(fgets(tempLine, 30, currentGame)) {}

            fileLine -= 1;
            turnOver = 1;
          }
          else {
            inputError = 3;
          }
        }
        else if (strcmp(userInput, "home") == 0 || strcmp(userInput, "'home'") == 0)  {
          //Close any open file streams here
          fclose(currentGame);
          turnOver = 1;
          gameOver = 1;
        }
        else {
          inputError = 1;
        }
        //

        //Error Messages for invalid inputs
        if (inputError != 0) {
          if (inputError == 1) {
            printf("\n \nInvalid Input! Input should be formatted like 'A1' or 'Undo'!\n \n");
          }
          else if (inputError == 2){
            printf("\n \nInvalid Input! The chosen space is already in use!\n \n");
          }
          else if (inputError == 3){
            printf("\n \nInvalid Input! No more Undo Actions Available!\n \n");
          }
        }
        //
      }
    }

    int remainingSpaces = 0;
    char winner;
    int winnerFound = 0;

    //Win states
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[2][0] == board[1][1] && board[1][1] == board[0][2])) {
      if (board[1][1] == 'X') {
        winner = 'X';
        winnerFound = 1;
      }
      else if (board[1][1] == 'O') {
        winner = 'O';
        winnerFound = 1;
      }
    }
    else {
      for (int k = 0; k < 3; k++) {
        if (board[k][0] == board[k][1] && board[k][1] == board[k][2]) {
          if (board[k][0] == 'X') {
            winner = 'X';
            winnerFound = 1;
          }
          else if (board[k][0] == 'O') {
            winner = 'O';
            winnerFound = 1;
          }
        }
        else if (board[0][k] == board[1][k] && board[1][k] == board[2][k]) {
          if (board[0][k] == 'X') {
            winner = 'X';
            winnerFound = 1;
          }
          else if (board[0][k] == 'O') {
            winner = 'O';
            winnerFound = 1;
          }
        }
      }
    }
    //

    //Check if any board spaces are unclaimed
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == '.') {
          remainingSpaces += 1;
        }
      }
    }
    //

    declutter();

    if (skipping == 0) {
      if (currentTurn == 1) {
        currentTurn += 1;
      }
      else {
        currentTurn -= 1;
      }
    }
    else {  //Do not change the turn counter if nobody has played.
      skipping = 0;   //Ensure all gameplay is now active, regardless of if the
                      //game is new or a resumed game.
    }

    if (remainingSpaces == 0 || winnerFound > 0) {
      printf("        Game Over!\n");
      if (winnerFound != 0) {
        if (winner == 'X') {
          printf(" The winner is %s!\n \n", player1);
        }
        else if (winner == 'O') {
          printf(" The winner is %s!\n \n", player2);
        }
      }
      else {
        printf("       It's a Draw!\n");
      }
      printf("- To undo the last move and keep playing, try 'Undo'.\n");
      printf("- To retun to the main meny, try 'Home'.\n \n \n");
      //Log game HERE!!!
    }
    //
  }
}

void replayMenu(){
  FILE *ar = fopen("allReplays.txt", "a+");
  int lines = 0;
  char read;
  if (ar != NULL) {
    lines += 1;
    while(!feof(ar)) {
      read = fgetc(ar);
      if (read == '\n')
      {
        lines += 1;
      }
    }
  }
  fclose(ar);
  char filename[30];
  for (int i = 1; i < lines; i++)
  {
    sprintf(filename, "replays/%d.txt", (i));

    FILE *checkNames = fopen(filename, "r");
    char name1[15];
    char name2[15];

    fgets(name1, 15, checkNames);
    removeNewline(name1);
    fgets(name2, 15, checkNames);
    removeNewline(name2);

    fclose(checkNames);

    printf(" %d - %s VS %s\n\n", i, name1, name2);
  }

  int selection;
  int selectionFound = 0;

  printf("\n\n\n Choose a game to Replay!\n\n");

  while(selectionFound == 0) {
    printf("> ");
    selectionFound = scanf("%d", &selection);

    if (selectionFound != 0) {
      if (selection < 1 || selection > (lines - 1 ))
      selectionFound = 0;
    }

    if (selectionFound == 0) {
      printf("\n\n\nInvalid Selection! If in doubt, try 1!\n\n");
    }
  }

  game(selection); //Load the game with the selected file
}

int main(int argc, char **argv) {
  int currentChoice = 0;
  introText();
  do {
    currentChoice = homeScreen();
    declutter(); //Declutter the screen
    if (currentChoice == 1) {
      game(0);
      currentChoice = 0;
    }
    else if (currentChoice == 2) {
      replayMenu();
      currentChoice = 0;
    }
  } while (currentChoice != -1);
  return(0);
}
