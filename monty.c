#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	// C90 does not support type bool, C99 does with this include.

int prizeDoor = 0, gamesPlayed = 0, userPick = 0, gamesWon = 0, testGamesWon = 0;
bool doors[3];

void revealDoors(void)
{
	printf("\nDoor 1: %d, Door 2: %d, Door 3: %d.", doors[0], doors[1], doors[2]);
}

void randDoor(void)
{
	prizeDoor = rand()%3+1;	
	for(int x = 0; x < 3; x++)
		doors[x] = false;
	doors[prizeDoor-1] = true;
}

int montysPick(int userPick, int prevMonty, bool revealed)	// Picks a door which has no prize behind it, and is not the users pick
{
	int mPick = 0;	
	if(revealed)
	{
		for(int x = 0; x < 3; x++)
			if((userPick - 1) != x && (prevMonty - 1) != x)
				mPick = x;
	}
	else
	{
		for(int x = 0; x < 3; x++)
			if((userPick - 1) != x && doors[x] != true)
				mPick = x;
	}
	return mPick + 1;
}

void weSwitch(int *mPick, int *uPick, bool researchMode, bool alwaysSwitch)
{
	int opt = -1, temp = 0;
	
	switch(researchMode)
	{
		case false:
			printf("\nThere is no prize behind door %d.", *mPick);
			*mPick = montysPick(*uPick, *mPick, true);
			printf("\nWould you like to switch to door %d?", *mPick);
			printf("\n1. Yes.");
			printf("\n2. No.");
			while(opt < 1 || opt > 2)
			{
				printf("\nWould you like to switch?: ");
				scanf("%d", &opt);
				fflush(stdin);
			}
			if(opt == 1)
			{
				temp = *uPick;
				*uPick = *mPick;
				*mPick = temp;
			}
			break;
		case true:
			*mPick = montysPick(*uPick, *mPick, true);
			if(alwaysSwitch)
			{
				temp = *uPick;
				*uPick = *mPick;
				*mPick = temp;
			}
			break;
	}
}

int main()
{
	int opt = -1, mPick = 0, numTests = 0;
	while(opt != 3)
	{
		opt = -1;
		printf("\n1. Game Mode");
		printf("\n2. Research Mode");
		printf("\n3. Quit");
		while(opt > 3 || opt < 1)
		{
			printf("\nWhich mode: ");
			scanf("%d", &opt);
			fflush(stdin);
		}

		switch(opt)
		{
			case 1:		// Game Mode
				randDoor();		// Pick door to have prize behind it
				opt = -1;
				while(opt > 3 || opt < 1)
				{
					printf("\nPick a door!(1 - 3): ");
					scanf("%d", &opt);
					fflush(stdin);
				}
				userPick = opt;

				mPick = montysPick(userPick, 0, false);	// Pick an empty door that isnt the users pick
				weSwitch(&mPick, &userPick, false, false);	

				if(doors[userPick - 1])
				{
					gamesWon++;
					printf("\nYou have won!");
				}
				else
					printf("\nYou have not won!");
				if(doors[mPick - 1])
					printf("\nMonty has won!");
				else
					printf("\nMonty has not won!");

				revealDoors();
				gamesPlayed++;
				printf("\nGames played: %d, games won: %d.", gamesPlayed, gamesWon);

				userPick = -1;
				opt = -1;
				break;
			case 2:		// Research Mode
				opt = -1;
				printf("\n1.Yes.");
				printf("\n2. No.");

				while(opt > 2 || opt < 1)
				{
					printf("\nAlways switch? ");
					scanf("%d", &opt);
					fflush(stdin);
				}

				printf("\nNumber of tests to run: ");
				scanf("%d", &numTests);
				fflush(stdin);

				while(numTests > 0)
				{
					randDoor();		// Pick door to have prize behind it
					switch(opt)
					{
						case 1:		// Always switch
							userPick = 1;

							mPick = montysPick(userPick, 0, false);	// Pick an empty door that isnt the users pick
							weSwitch(&mPick, &userPick, true, true);	

							if(doors[userPick - 1])
								testGamesWon++;
							break;
						case 2:		// Never switch
							userPick = 1;

							mPick = montysPick(userPick, 0, false);	// Pick an empty door that isnt the users pick
							weSwitch(&mPick, &userPick, true, false);	

							if(doors[userPick - 1])
								testGamesWon++;
							break;
					}
					numTests--;
				}

				printf("\nGames won: %d.", testGamesWon);
				testGamesWon = 0;
				userPick = -1;
				opt = -1;
				break;
			case 3:		// Quit
				break;
		}
	}

	return 0;
}
