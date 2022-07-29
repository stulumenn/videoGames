#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXNAME 40
#define MAXGENRE 20
#define MAXPLATFORM 10

int calculateTheLine (const char *fileName);
void readTheLineFromFile(char array[200], FILE *fp, int lineNumber);
int seperatingLineRespectToComma(float information[][7], char genreArray[][MAXGENRE], char platformArray[][MAXPLATFORM], char nameArray[][MAXNAME], int genreSize, int platformSize, int lineCount);
void printThroughTheYears (float information[][7],char nameArray[][MAXNAME] ,int size, int year, int untilOrSince);
int informationOfAGame (char array[], int size, char nameArray[][MAXNAME], float information[][7],char genreArray[][MAXGENRE], char platformArray[][MAXPLATFORM]);
float averageOfTheUserScores (float information[][7], int size);
void geoInfOfAGame(char name[], float information[][7], int size, char nameArray[][MAXNAME]);
void calculatingFrequenceOfGenreTypes (float information[][7], char genreArray[][MAXGENRE], int genreSize, int size);
void calculatingFrequenceOfPlatformTypes (float information[][7], char platformArray[][MAXPLATFORM], int platformSize, int size);
int isContainsGenre (char array[][MAXGENRE], char string[], int size);
int isContainsPlatform (char array[][MAXPLATFORM], char string[], int size);

int main(){
	

	int selection, year, answer,returnedValue;
	int newGenreSize = 12;
	int newPlatformSize = 10;
	char name[MAXNAME];
	float averageOfTheScores;
	int lineCount = calculateTheLine ("VideoGames.txt");
	char lineStrings [200];
	char nameOfTheGames[lineCount][MAXNAME];
	char genreOfTheGames [newGenreSize][MAXGENRE];
	char platformOfTheGames [newPlatformSize][MAXPLATFORM]; 
	float informationAboutTheGames [lineCount][7];
	int returnFlag = seperatingLineRespectToComma(informationAboutTheGames, genreOfTheGames, platformOfTheGames, nameOfTheGames,newGenreSize,newPlatformSize,lineCount);

	printf("0: List of the Genres\n1: List of the Platforms\n2: List of the Games Through the Years\n3: All Informations of a Single Game\n6: Frequence of the Genres\n7: Frequence of the Platforms\n8: Exit\n");
	printf("Please select an operation\n");
	
	do
	{
		scanf(" %d", &selection);
		switch (selection){
			case 0:
					for(int i=0; i< newGenreSize; i++){
						printf("%s\n", genreOfTheGames[i]);
					}
					break;
			case 1:
					for(int i=0; i< newPlatformSize; i++){
						printf("%s\n", platformOfTheGames[i]);
					}
					break;
			case 2:
					printf("Enter a year:\n");
					scanf("%d", &year);
					printf("Until (0) or Since (1) %d:", year);
					scanf("%d", &answer);
					printThroughTheYears(informationAboutTheGames, nameOfTheGames, lineCount, year, answer);
					break;
			case 3:
					printf("Please enter the name of the game:\n");
					scanf("%s", name);
					returnedValue = informationOfAGame (name, lineCount, nameOfTheGames, informationAboutTheGames, genreOfTheGames, platformOfTheGames);
					break;
			case 4:
					averageOfTheScores = averageOfTheUserScores(informationAboutTheGames, lineCount);
					printf("Average: %f\n", averageOfTheScores);
					break;
			case 5:
					printf("Please enter the name of the game:\n");
					scanf("%s",name);
					geoInfOfAGame(name, informationAboutTheGames, lineCount, nameOfTheGames);
					break;
			case 6:
					calculatingFrequenceOfGenreTypes(informationAboutTheGames, genreOfTheGames, newGenreSize, lineCount);
					break;
			case 7:
					calculatingFrequenceOfPlatformTypes(informationAboutTheGames, platformOfTheGames, newPlatformSize, lineCount);
					break;
			case 8:
					break;
			default:
					printf("You didn't pick one of the choices. Try again.\n");
					break;
		}
	} while (selection != 8);
}

int calculateTheLine (const char *fileName){
	char ch;
	int i=1;
	FILE *fp = fopen (fileName, "r");
	while (ch != EOF){
		ch = fgetc(fp);
		if (ch == '\n'){
			i++;
		}
	}
	return i;
}
void readTheLineFromFile(char array[200], FILE *fp, int lineNumber){

	fgets(array, lineNumber, fp);

}
int seperatingLineRespectToComma(float information[][7], char genreArray[][MAXGENRE], char platformArray[][MAXPLATFORM], char nameArray[][MAXNAME], int genreSize, int platformSize, int lineCount){
		
	FILE *fp = fopen("VideoGames.txt", "r");
	int returnedValue=1;
	int genreCounter=0;
	int platformCounter=0;
	char string []="not_available";

	for (int k=0; k<lineCount; k++){
		char line[200];
		readTheLineFromFile(line, fp, 200);

		char *name = strtok(line, ",");
		strcpy(nameArray[k] , name);
	
		char *genre = strtok (NULL, ",");
		returnedValue = isContainsGenre(genreArray, genre, genreSize);
		if(returnedValue == 0){
			strcpy(genreArray[genreCounter], genre);
			genreCounter++;
		}
		for(int i=0; i<genreSize; i++){
			if (strcmp (genreArray[i],genre) == 0){
				information[k][0]=i;
			}
		}

		char *platform = strtok(NULL, ",");
		returnedValue = isContainsPlatform(platformArray, platform, platformSize);
		if(returnedValue == 0){
			strcpy(platformArray[platformCounter], platform);
			platformCounter++;
		}
		for(int i=0; i<platformSize; i++){
			if (strcmp (platformArray[i],platform) == 0){
				information[k][1]=i;
			}
		}
	
		char *year = strtok(NULL, ",");
		information[k][2] = atoi(year);
	
		char *NA = strtok(NULL, ",");
		information[k][3] = atof(NA);
	
		char *EU = strtok(NULL, ",");
		information[k][4] = atof(EU);
	
		char *global = strtok(NULL, ",");
		if(strcmp(string,global) == 0){
			information[k][5] = 1967;
		}
		else
			information[k][5] = atof(global);
	
		char *score = strtok(NULL, "\n");
		information[k][6] = atof(score);	

		if (k == lineCount-1){
			fclose(fp);
			return 1;
		}
	}
	return 0;
}

void printThroughTheYears (float information[][7],char nameArray[][MAXNAME] ,int size, int year, int untilOrSince){
	
	for(int i=0; i<size; i++){
		if (untilOrSince == 0){
			if (information[i][2] < year){
				printf ("%s\n", nameArray[i]);
			}
		}
		else if(untilOrSince == 1){
			if (information[i][2] >= year){
				printf ("%s\n", nameArray[i]);
			}
		}
		else
			printf("You didn't pick right number.\n");
	}
}
int informationOfAGame (char array[], int size, char nameArray[][MAXNAME], float information[][7],char genreArray[][MAXGENRE], char platformArray[][MAXPLATFORM]){

	int returnFlag=2;
	int i;
	int value;
	do 
	{
		i=0;
		while(i<size){
			returnFlag = strcmp(array, nameArray[i]);
			if(returnFlag==0)
			{	
				printf("Name: %s\n", nameArray[i]);
				value = information[i][0];
				printf("Genre: %s\n", genreArray[value]);
				value = information[i][1];
				printf("Platform: %s\n", platformArray [value]);
				printf("Year: %.0f\n", information[i][2]);
				printf("Sales In NA: %.2f\n", information[i][3]);
				printf("Sales In EU: %.2f\n", information[i][4]);
				if (information[i][5] == 1967){
					printf("Total Sales: Not Available\n");
				}
				else
					printf("Total Sales: %.2f\n", information[i][5]);
				printf("User Score: %.2f\n", information[i][6]);
				returnFlag = 1;
				return 1;
			}
			i++;
		}

		if (i==size) {
			printf("There is not a game name such like that. Try again.\n");
			scanf("%s", array);
		}
		
	} while (returnFlag!=1);
	return 0;
}

float averageOfTheUserScores (float information[][7], int size){
	float average;

	for(int i=0; i<size; i++){
		average = average + information[i][6];
	}
	return average;
}

void geoInfOfAGame(char name[], float information[][7], int size, char nameArray[][MAXNAME]){
	
	int returnFlag=0;
	do
	{
		for (int i=0; i<size; i++){
			if (name == nameArray[i]){
				if (information[i][4] > information[i][3]){
					printf("This game was more popular in Europe.\n");
				}
				else if (information[i][4]< information[i][3]){
					printf("This game was more popular in North America.\n");
				}
				else if (information[i][4] == information[i][3]){
					printf("This game had same popularity in Europe and North America.\n");
				}
				returnFlag=1;
			}
			else {
			printf("There is not a game name such like that. Try again.\n");
			scanf("%s", name);
			}
		}
	}while(returnFlag ==0);
}
void calculatingFrequenceOfGenreTypes (float information[][7], char genreArray[][MAXGENRE], int genreSize, int size){
	int array[genreSize];
	int counter=0;
	int k=0;
	
	for(int i=0; i<genreSize; i++){
		for(int j=0; j<size; j++){

			if (information[j][0]==i){
				counter++;
			}
		}
		array[k]=counter;
		counter=0;
		k++;
	}

	for(int i=0; i<genreSize; i++){
		printf("%s: 	%d\n", genreArray[i], array[i]);
	}
}
void calculatingFrequenceOfPlatformTypes (float information[][7], char platformArray[][MAXPLATFORM], int platformSize, int size){
	int array[platformSize];
	int counter=0;
	int k=0;

	for(int i=0; i<platformSize; i++){
		for(int j=0; j<size; j++){

			if (information[j][1]==i){
				counter++;
			}
		}
		array[k]=counter;
		counter=0;
		k++;
	}
	for(int i=0; i<platformSize; i++){
		printf("%s: 	%d\n", platformArray[i], array[i]);
	}

}

int isContainsGenre (char array[][MAXGENRE], char string[], int size){
	int returnFlag=1;
	for(int i=0; i<size; i++){
		returnFlag=strcmp(array[i], string);
		if (returnFlag ==0){
			return 1;
		}
	}
	if(returnFlag !=0){
		return 0;
	}
	return returnFlag;
}
int isContainsPlatform (char array[][MAXPLATFORM], char string[], int size){
	int returnFlag=1;
	for(int i=0; i<size; i++){
		returnFlag=strcmp(array[i], string);
		if (returnFlag ==0){
			return 1;
		}
	}
	if(returnFlag !=0){
		return 0;
	}
	return returnFlag;
}










