#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// File pointer
FILE *fptr;

// Structure for feet and inches of a fighter's height
struct Measurements{
	int feet;
	int inches;
};

// Structure for stats of a fighter
struct Stats{
	char givenName[99];
	char nickName[99];
	char surname[99];
	char weightClass[18];
	char country[99];
	int wins;
	int losses;
	int KOs;
	int age;
	float weight;
	Measurements height;
};

// Structure for temporary storage of feet and inches of a fighter's height
struct EditedMeasurements{
	int feet;
	int inches;
};

// Structure for temporary storage of stats for a fighter
struct EditedStats{
	char givenName[99];
	char nickName[99];
	char surname[99];
	char weightClass[18];
	char country[99];
	int wins;
	int losses;
	int KOs;
	int age;
	float weight;
	EditedMeasurements EditedHeight;
};

// Prototyping
int fighterCount();
void readIn(Stats fighter[], int count);
void printData(Stats fighter[], int count);
int search(int count);
void input(Stats fighter[], int &count);
void add(Stats fighter[], int count);
void printFighter(Stats fighter[], int count, int placeholder);
void edit(Stats fighter[], EditedStats Editedfighter, int placholder, int count);
void inputEdit(EditedStats &Editedfighter);
void remove(Stats fighter[], int placeholder, int count);
void selectedPlayer(char firstName[], char lastName[], int placeholder);

int main(){
	// Declaring variables
	int count = 0;
	int invalid[3];
	int placeholder = 0;
	int keywordType = 0;
	char response[3];
	char back;
	int mainScreen = 0;
	char removal;
	int invalidKeyword;
	int screenSize = 0;
	char firstName[20];
	char lastName[20];
	
	// loop to enable user to return to the mainscreen
	while (mainScreen == 0){
		// Setting entire array to 0
		for (int i = 0; i < 3; i++){
			invalid[i] = 0;
		}
		
		// Sequence to count how many fighters, allocate memory, and read in all the stats
		count = fighterCount();			
		Stats fighter[count];	
		readIn(fighter, count);
		
		// Allocating memory
		EditedStats Editedfighter;
		
		// Clear screen
		system("cls");
		
		// Instructing user to increase screen size
		if (screenSize == 0){
			printf("**Important** Right-click name (^^^^^), and select properties. \nChange the Screen buffer size Width to 160, and Window size Width to 155\n\n");
		}
		
		// Ensuring that the user is only instructed to increase screen size once
		screenSize++;
		
		// Introduction, and prompting user to either add an entry, or proceed to the database
		printf("Welcome to my database! \nIt includes the statistics for the top 3 MMA fighters in 6 major weightclasses\n\n");
		printf("To proceed to the database, enter \"d\" \n\n");
		printf("To add stats for a new fighter, enter \"a\" \n\n");
		
		// Loop to repeat prompt if an invalid response is entered
		while(invalid[0] == 0){
			// Resetting default loop condition
			invalid[0] = 1;
			
			// Reading in response
			scanf("%c", &response[0]);
			fflush(stdin);
			
			// Proceeding based on user's response
			if(response[0] == 'a'){
				// Making room for another set of stats at the end of the fighter array
				count++;
				Stats fighter[count];
				count--;
				readIn(fighter, count);
				count++;
				
				// Clear screen
				system("cls");
				
				// Function for user to enter data for a new entry
				input(fighter, count);
				
				// Function to add new entry into the text file
				add(fighter, count);
				
				// Clear screen
				system("cls");
				
				// Giving user the option to return to the main screen, or to exit, and reading in response
				printf("To return to the main screen, enter \"m\". To exit, enter any other character: ");
				fflush(stdin);
				scanf("%c", &back);
				fflush(stdin);
				
				// Creating conditions necessary to escape program loop, if the user chooses to exit
				if (back != 'm'){
					mainScreen++;
				}
			}
			else if(response[0] == 'd'){
				// Clear screen
				system("cls");
				
				// Prompting user to either view database, or search for an entry
				printf("Would you like to view the database (\"d\"), or search for a specific competitor (\"s\")\n\n");
				
				// Sequence to count how many fighters, allocate memory, and read in all the stats
				count = fighterCount();
				Stats fighter[count];
				readIn(fighter, count);
				
				// Loop to repeat prompt if an invalid response is entered		
				while (invalid[1] == 0){
					// Resetting default loop condition
					invalid[1] = 1;
					
					// Reading in user's response
					scanf("%c", &response[1]);
					fflush(stdin);
					
					// Proceeding based on user's response
					if(response[1] == 'd'){
						// Clear screen
						system("cls");
						
						// Function to print out database for user viewing
						printData(fighter, count);
						
						// Promting user to either return to main screen, or to exit, and reading in response
						printf("\nTo return to the main screen, enter \"m\", to exit, enter any other character: ");
						fflush(stdin);
						scanf("%c", &back);
						fflush(stdin);
						
						// Creating conditions necessary to escape program loop, if the user chooses to exit
						if (back != 'm'){
							mainScreen++;
						}
					}
					else if(response[1] == 's'){
						// Clear screen
						system("cls");
						
						// Creating conditions necessary to begin the following loop
						invalidKeyword = 0;
						
						// Loop to repeat search prompt if the searched keyword is invalid
						while (invalidKeyword == 0){			
							//Resetting default loop conditions
							invalidKeyword = 1;
							
							// Setting the value of the placeholder variable, as the value returned by the function used 
							// to search for, and locate a specific competitor by keyword
							placeholder = search(count);
							
							// Clear screen
							system("cls");
							
							// Ensuring that the sequence only proceeds if the keyword refers to an entry contained in the database
							if (placeholder != -1){
								// Function to return the full name of the selected fighter
								selectedPlayer(firstName, lastName, placeholder);
								
								// Subtracting headers from placeholder value
								placeholder -= 11;
								
								// Giving user full name of selected fighter, by determining where in the line the keyword was located
								if (placeholder % 12 == 1){
									printf("First name detected: %s %s\n\n", firstName, lastName);
								}
								else if (placeholder % 12 == 2){		
									printf("Nickname detected: %s %s\n\n", firstName, lastName);
								}
								else if (placeholder % 12 == 3){								
									printf("Last name detected: %s %s\n\n", firstName, lastName);
								}
							}
							else{
								// Informing user of the invalid keyword
								printf("Invalid keyword\n\n");
								
								// Creating conditions necessary to repeat loop
								invalidKeyword--;
							}
						}
						
						// Promting user to either view, edit or remove selected competitor
						printf("Would you like to view (\"v\"), edit (\"e\"), or remove (\"r\") the competitor\n\n");
						
						// Sequence to count how many fighters, allocate memory, and read in all the stats
						count = fighterCount();
						Stats fighter[count];
						readIn(fighter, count);
						
						// Loop to repeat prompt if an invalid response is entered		
						while (invalid[2] == 0){
							// Resetting default loop condition
							invalid[2] = 1;
							
							// Reading in response
							fflush(stdin);
							scanf("%c", &response[2]);
							fflush(stdin);
							
							// Proceeding based on user's response
							if (response[2] == 'v'){
								// Function to print stats of a selected fighter for user viewing
								printFighter(fighter, count, placeholder);
								
								// Promting user to either return to main screen, or to exit, and reading in response
								printf("To return to the main screen, enter \"m\", to exit, enter any other character: ");
								fflush(stdin);
								scanf("%c", &back);
								fflush(stdin);
								
								// Creating conditions necessary to escape program loop, if the user chooses to exit
								if (back != 'm'){
									mainScreen++;
								}
							}
							else if (response[2] == 'e'){
								// Function for user to input new data for an existing entry
								inputEdit(Editedfighter);
								
								// Sequence to count how many fighters, allocate memory, and read in all the stats
								count = fighterCount();
								Stats fighter[count];
								readIn(fighter, count);
								
								// Function to write in edited data for an existing entry into text file
								edit(fighter, Editedfighter, placeholder, count);														
								
								// Promting user to either return to main screen, or to exit, and reading in response
								printf("To return to the main screen, enter \"m\". To exit, enter any other character: ");
								fflush(stdin);
								scanf("%c", &back);
								fflush(stdin);
								
								// Creating conditions necessary to escape program loop, if the user chooses to exit
								if (back != 'm'){
									mainScreen++;
								}
							}
							else if (response[2] == 'r'){
								// Clear screen
								system("cls");
								
								// Promt user for confirmation in removing the selected entry from the database, and reading in response
								printf("To proceed in deleting '%s %s' from the database, enter \"d\". To cancel, enter any other character: ", firstName, lastName);
								fflush(stdin);
								scanf("%c", &removal);
								fflush(stdin);
								
								// If user confirms
								if (removal == 'd'){
									// Function to delete an entire entry from the text file										
									remove(fighter, placeholder, count);
								}	
								
								// Promting user to either return to main screen, or to exit, and reading in response
								printf("To return to the main screen, enter \"m\". To exit, enter any other character: ");
								fflush(stdin);
								scanf("%c", &back);
								fflush(stdin);
								
								// Creating conditions necessary to escape program loop, if the user chooses to exit
								if (back != 'm'){
									mainScreen++;
								}
								
							}
							else{
								// Creating condiions to restart loop
								invalid[2]--;
								
								// Informing user that response is invalid
								printf("\nInvalid response\n\n");
							}
						}
					}
					else{
						// Creating condiions to restart loop
						invalid[1]--;
					
						// Informing user that response is invalid
						printf("\nInvalid response\n\n");
					}
				}
			}
			else{
				// Creating condiions to restart loop
				invalid[0]--;
				
				// Informing user that response is invalid
				printf("\nInvalid response\n\n");
			}
			
			// Sequence to count how many fighters, allocate memory, and read in all the stats
			count = fighterCount();
			Stats fighter[count];
			readIn(fighter, count);
		}
	}
	
	// Clear screen
	system("cls");
	
	return 0;
}

// Function to return the number of fighters/entries in the text file
int fighterCount(){	
	// Declaring variables
	int wordCount = 1;
	char junk[99];
	
	// Opening text file to be read from
	fptr = fopen("fightersCompleted.txt", "r");
	
	// In case text file doesn't exist	
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Scanning all the words in the text file to count them
	while (!feof(fptr)){	
		fscanf(fptr, "%s", junk);			
		
		// Incrementing a counter variable 
		wordCount++;	
	}
	
	// Closing text file
	fclose(fptr);
	
	// Subtracting headers from the total, and dividing by the number of words per entry, to determine how many entries
	return (wordCount - 11) /12;
}

// Function for user to enter data for a new entry
void input(Stats fighter[], int &count){
	// Prompting user to enter each stat, and assigning it to its respective variable
	printf("Enter the following data, and use \"n/a\" for unknown word stats (all number stats are required)\nUse underscores instead of spaces.\n\n");
	printf("First Name: ");
	scanf("%s", &fighter[count].givenName);
	printf("\nNickname: ");
	scanf("%s", &fighter[count].nickName);
	printf("\nLast Name: ");
	scanf("%s", &fighter[count].surname);
	printf("\nWeightclass: ");
	scanf("%s", &fighter[count].weightClass);
	printf("\nCountry: ");
	scanf("%s", &fighter[count].country);
	printf("\nAge: ");
	scanf("%d", &fighter[count].age);
	printf("\nWins: ");
	scanf("%d", &fighter[count].wins);
	printf("\nLosses: ");
	scanf("%d", &fighter[count].losses);
	printf("\nKOs: ");
	scanf("%d", &fighter[count].KOs);
	printf("\nHeight (only feet): ");
	scanf("%d", &fighter[count].height.feet);
	printf("\nHeight (only inches): ");
	scanf("%d", &fighter[count].height.inches);
	printf("\nWeight (lbs): ");
	scanf("%f", &fighter[count].weight);
	
	// Clear screen
	system("cls");
}

// Function to read in fighter stats from the text file
void readIn(Stats fighter[], int count){
	// Declaring variables
	char headers[12];
	
	// Opening text file to be read from
	fptr = fopen("fightersCompleted.txt", "r");
	
	// In case text file doesn't exist
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Moving file pointer to after headers, by assigning them to a junk variable
	for (int h = 1; h < 12; h++){
		fscanf(fptr, "%s", headers);
	}
	
	// Reading in stats from the textfile, and assigning them to their respective variables
	for (int i = 0; i < count; i++) {
		fscanf(fptr, "%s", &fighter[i].givenName);	
		fscanf(fptr, "%s", &fighter[i].nickName);	
		fscanf(fptr, "%s", &fighter[i].surname);
		fscanf(fptr, "%s", &fighter[i].weightClass);
		fscanf(fptr, "%s", &fighter[i].country);
		fscanf(fptr, "%d", &fighter[i].age);
		fscanf(fptr, "%d", &fighter[i].wins);	
		fscanf(fptr, "%d", &fighter[i].losses);	
		fscanf(fptr, "%d", &fighter[i].KOs);
		fscanf(fptr, "%d", &fighter[i].height.feet);	
		fscanf(fptr, "%d", &fighter[i].height.inches);
		fscanf(fptr, "%f", &fighter[i].weight);
	}
	
	// Closing text file
	fclose(fptr);
}

// Function to add new entry into the text file
void add(Stats fighter[], int count){
	// Opening text file to be added to
	fptr = fopen("fightersCompleted.txt", "a");
	
	// In case text file doesn't exist	
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Writing each stat into text file
	fprintf(fptr, "%s ", fighter[count].givenName);
	fprintf(fptr, "%s ", fighter[count].nickName);
	fprintf(fptr, "%s ", fighter[count].surname);
	fprintf(fptr, "%s ", fighter[count].weightClass);
	fprintf(fptr, "%s ", fighter[count].country);
	fprintf(fptr, "%d %d %d %d %d %d %.0f\n", fighter[count].age, fighter[count].wins, fighter[count].losses, fighter[count].KOs, fighter[count].height.feet, fighter[count].height.inches, fighter[count].weight);
	
	// Closing text file
	fclose(fptr);
}

// Function to print out database for user viewing
void printData(Stats fighter[], int count){
	// Declaring variables
	float winPercentage;
	float KOpercentage;
	
	// Printing headers
	printf("Name\t\tNickname\tLastname\tWeightclass\tCountry\t\tAge\tWins\tLosses\tKOs\tHeight\tWeight(lbs)\tKO/Win\tWin/Total\n\n");
	
	// Looping sequence for each entry
	for (int i = 0; i < count; i++){
		//Calculating stats that are dependant on other stats
		winPercentage = fighter[i].wins * 100 / (fighter[i].losses + fighter[i].wins);
		KOpercentage = fighter[i].KOs * 100 / fighter[i].wins;
		
		// Determining how many tabs are necessary to make the table orderly, based on how long each string is
		if (strlen(fighter[i].givenName) < 8){
			printf("%s\t\t", fighter[i].givenName);
		}
		else{
			printf("%s\t", fighter[i].givenName);
		}

		if (strlen(fighter[i].nickName) < 8){
			printf("%s\t\t", fighter[i].nickName);
		}
		else{
			printf("%s\t", fighter[i].nickName);
		}
		
		if (strlen(fighter[i].surname) < 8){
			printf("%s\t\t", fighter[i].surname);
		}
		else{
			printf("%s\t", fighter[i].surname);
		}
		
		if (strlen(fighter[i].weightClass) < 8){
			printf("%s\t\t", fighter[i].weightClass);
		}
		else if(strlen(fighter[i].weightClass) < 16 && strlen(fighter[i].weightClass) > 7){
			printf("%s\t", fighter[i].weightClass);
		}
		else{
			printf("%s", fighter[i].weightClass);
		}
		
		if (strlen(fighter[i].country) < 8){
			printf("%s\t\t", fighter[i].country);
		}
		else{
			printf("%s\t", fighter[i].country);
		}
		
		// Printing definitive stats, and dependant stats
		printf("%d\t%d\t%d\t%d\t%d'%d\"\t%.1f\t\t", fighter[i].age, fighter[i].wins, fighter[i].losses, fighter[i].KOs, fighter[i].height.feet, fighter[i].height.inches, fighter[i].weight);
		printf("%.1f%%\t%.1f%%\n", KOpercentage, winPercentage);
	}
}

//Function for user to search for a specific entry, and return where in the text file it is located
int search(int count){
	// Declaring variables
	char keyword[99];
	char match[99];
	int placeholder = 0;
	
	// Ensuring that no competitors' names already match the comparison variable
	strcpy(match, " ");
	
	// Prompting user to search for a competitor, and stating specifications
	printf("To search, enter a keyword (ie. first name, last name or nickname). \n\nBe sure to include any necesary capital letters, and use underscores instead of spaces: ");
	scanf("%s", &keyword);
	
	// Opening text file to be read from
	fptr = fopen("fightersCompleted.txt", "r");
	
	// In case text file doesn't exist
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Systematically comparing each word in the text file, to the entered keyword
	while (strcmp(keyword, match) != 0){
		// Incrementing a variable to keep track of where the file pointer is located
		placeholder++;
		
		// Assigning each word to a constantly updated variable
		fscanf(fptr, "%s", match);
		
		// Escapes loop when file pointer becomes greater than word count
		if (placeholder > count * 12 + 11){
			// Setting return value to a distinct value indicating that the entered keyword could not be found
			placeholder = -1;
			
			// Creating necessary conditions to escape loop
			strcpy(match, keyword);
		}

	}
	
	// Closing text file
	fclose(fptr);
	
	// Returning where in the text file the keyword is located
	return placeholder;
}

// Function to print stats of a selected fighter for user viewing
void printFighter(Stats fighter[], int count, int placeholder){
	// Declaring variables
	char junk[20];
	char string[5][99];
	int integer[6];
	float weight;
	float winPercentage;
	float KOpercentage;
	
	// Adjusting placeholder to be immediately before the selected player's line, based on where in the line it is located
	if (placeholder % 12 == 1){
		placeholder--;
	}
	else if (placeholder % 12 == 2){
		placeholder -= 2;
	}
	else if (placeholder % 12 == 3){
		placeholder -= 3;
	}
	
	// Opening text file to be read from
	fptr = fopen("fightersCompleted.txt", "r");
	
	// In case text file doesn't exist
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Assigning headers to a junk variable
	for (int g = 1; g <= 11; g++){
		fscanf(fptr, "%s", junk);
	}
	
	// Assigning all the words before the placeholder to a junk variable
	for (int h = 1; h <= placeholder; h++){
		fscanf(fptr, "%s", junk);
	}
	
	// Reading in all the stats from the selected entry
	fscanf(fptr, "%s %s %s %s %s", string[0], string[1], string[2], string[3], string[4]);
	fscanf(fptr, "%d %d %d %d %d %d %f", &integer[0], &integer[1], &integer[2], &integer[3], &integer[4], &integer[5], &weight);
	
	// Closing text file
	fclose(fptr);
	
	//Calculating stats that are dependant on other stats
	winPercentage = integer[1] * 100 / (integer[2] + integer[1]);
	KOpercentage = integer[3] * 100 / integer[1];
	
	// Clear screen
	system("cls");
	
	// Printing headers
	printf("Name\t\tNickname\tLastname\tWeightclass\tCountry\t\tAge\tWins\tLosses\tKOs\tHeight\tWeight(lbs)\tKO/Win\tWin/Total\n\n");
	
	// Determining how many tabs are necessary to make the table orderly, based on how long each string is
	if (strlen(string[0]) < 8){
		printf("%s\t\t", string[0]);
	}
	else{
		printf("%s\t", string[0]);
	}
	
	if (strlen(string[1]) < 8){
		printf("%s\t\t", string[1]);
	}
	else{
		printf("%s\t", string[1]);
	}
	
	if (strlen(string[2]) < 8){
		printf("%s\t\t", string[2]);
	}
	else{
		printf("%s\t", string[2]);
	}
	
	if (strlen(string[3]) < 8){
		printf("%s\t\t", string[3]);
	}
	else if(strlen(string[3]) > 15){
		printf("%s", string[3]);
	}
	else{
		printf("%s\t", string[3]);
	}
	
	if (strlen(string[4]) < 8){
		printf("%s\t\t", string[4]);
	}
	else{
		printf("%s\t", string[4]);
	}
	
	// Printing definitive stats, and dependant stats
	printf("%d\t%d\t%d\t%d\t%d'%d\"\t%.1f\t\t", integer[0], integer[1], integer[2], integer[3], integer[4], integer[5], weight);
	printf("%.1f%%\t%.1f%%\n\n", KOpercentage, winPercentage);
}

// Function for user to input new data for an existing entry
void inputEdit(EditedStats &Editedfighter){
	// Clear screen
	system("cls");
	// Prompting user to enter each stat, and assigning it to its respective variable in a temporary storage
	printf("Enter the new data for the selected competitor, and use \"n/a\" for unknown word stats (all number stats are required)\nUse underscores instead of spaces.\n\n");
	printf("First Name: ");
	scanf("%s", &Editedfighter.givenName);	
	printf("\nNickname: ");
	scanf("%s", &Editedfighter.nickName);	
	printf("\nLast Name: ");
	scanf("%s", &Editedfighter.surname);	
	printf("\nWeightclass: ");
	scanf("%s", &Editedfighter.weightClass);	
	printf("\nCountry: ");
	scanf("%s", &Editedfighter.country);	
	printf("\nAge: ");
	scanf("%d", &Editedfighter.age);	
	printf("\nWins: ");
	scanf("%d", &Editedfighter.wins);	
	printf("\nLosses: ");
	scanf("%d", &Editedfighter.losses);
	printf("\nKOs: ");
	scanf("%d", &Editedfighter.KOs);	
	printf("\nHeight (only feet): ");
	scanf("%d", &Editedfighter.EditedHeight.feet);
	printf("\nHeight (only inches): ");
	scanf("%d", &Editedfighter.EditedHeight.inches);
	printf("\nWeight (lbs): ");
	scanf("%f", &Editedfighter.weight);
	
	// Clear screen
	system("cls");
}

// Function to write in edited data for an existing entry into text file
void edit(Stats fighter[], EditedStats Editedfighter, int placeholder, int count){
	// Declaring variables
	int line = 0;
	int startPoint = 0;
	
	// Adjusting placeholder to be immediately before the selected player's line, based on where in the line it is located
	if (placeholder % 12 == 1){
		placeholder--;
	}
	else if (placeholder % 12 == 2){
		placeholder -= 2;
	}
	else if (placeholder % 12 == 3){
		placeholder -= 3;
	}
	
	// Calculating amount of lines based on how many words
	line = placeholder / 12;
	
	// Opening text file to be written into
	fptr = fopen("fightersCompleted.txt", "w");
	
	// In case text file doesn't exist
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Writing in headers
	fprintf(fptr, "Name Nickname Lastname Weightclass Country Age Wins Losses KOs Height Weight(lbs)\n");
	
	// Writing in all the data before the edited entry
	for (int k = 0; k < line; k++){
		fprintf(fptr, "%s ", fighter[k].givenName);
		fprintf(fptr, "%s ", fighter[k].nickName);
		fprintf(fptr, "%s ", fighter[k].surname);
		fprintf(fptr, "%s ", fighter[k].weightClass);
		fprintf(fptr, "%s ", fighter[k].country);
		fprintf(fptr, "%d %d %d %d %d %d %.0f\n", fighter[k].age, fighter[k].wins, fighter[k].losses, fighter[k].KOs, fighter[k].height.feet, fighter[k].height.inches, fighter[k].weight);
	}
	
	// Writing in the new data for the edited entry
	fprintf(fptr, "%s ", Editedfighter.givenName);
	fprintf(fptr, "%s ", Editedfighter.nickName);
	fprintf(fptr, "%s ", Editedfighter.surname);
	fprintf(fptr, "%s ", Editedfighter.weightClass);
	fprintf(fptr, "%s ", Editedfighter.country);
	fprintf(fptr, "%d %d %d %d %d %d %.0f\n", Editedfighter.age, Editedfighter.wins, Editedfighter.losses, Editedfighter.KOs, Editedfighter.EditedHeight.feet, Editedfighter.EditedHeight.inches, Editedfighter.weight);
	
	// Marking the starting point as one line after the edited entry
	startPoint = line + 1;
	
	// Writing in the rest of the data after the edited entry
	for (int l = startPoint; l < count; l++){
		fprintf(fptr, "%s ", fighter[l].givenName);
		fprintf(fptr, "%s ", fighter[l].nickName);
		fprintf(fptr, "%s ", fighter[l].surname);
		fprintf(fptr, "%s ", fighter[l].weightClass);
		fprintf(fptr, "%s ", fighter[l].country);
		fprintf(fptr, "%d %d %d %d %d %d %.0f\n", fighter[l].age, fighter[l].wins, fighter[l].losses, fighter[l].KOs, fighter[l].height.feet, fighter[l].height.inches, fighter[l].weight);
	}
	
	// Closing text file
	fclose(fptr);
}

// Function to delete an entire entry from the text file
void remove(Stats fighter[], int placeholder, int count){
	// Declaring variables
	int line = 0;
	int startPoint = 0;
	
	// Adjusting placeholder to be immediately before the selected player's line, based on where in the line it is located=
	if (placeholder % 12 == 1){
		placeholder--;
	}
	else if (placeholder % 12 == 2){
		placeholder -= 2;
	}
	else if (placeholder % 12 == 3){
		placeholder -= 3;
	}
	
	// Calculating amount of lines based on how many words
	line = placeholder / 12;
	
	// Opening text file to be written into
	fptr = fopen("fightersCompleted.txt", "w");
	
	// In case text file doesn't exist
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Printing headers
	fprintf(fptr, "Name Nickname Lastname Weightclass Country Age Wins Losses KOs Height Weight(lbs)\n");
	
	// Writing in data before the removed entry
	for (int k = 0; k < line; k++){
		fprintf(fptr, "%s ", fighter[k].givenName);
		fprintf(fptr, "%s ", fighter[k].nickName);
		fprintf(fptr, "%s ", fighter[k].surname);
		fprintf(fptr, "%s ", fighter[k].weightClass);
		fprintf(fptr, "%s ", fighter[k].country);
		fprintf(fptr, "%d %d %d %d %d %d %.0f\n", fighter[k].age, fighter[k].wins, fighter[k].losses, fighter[k].KOs, fighter[k].height.feet, fighter[k].height.inches, fighter[k].weight);
	}
	
	// Marking the starting point as one line after the removed entry
	startPoint = line + 1;
	
	// Writing in the rest of the data, after the removed entry
	for (int l = startPoint; l < count; l++){
		fprintf(fptr, "%s ", fighter[l].givenName);
		fprintf(fptr, "%s ", fighter[l].nickName);
		fprintf(fptr, "%s ", fighter[l].surname);
		fprintf(fptr, "%s ", fighter[l].weightClass);
		fprintf(fptr, "%s ", fighter[l].country);
		fprintf(fptr, "%d %d %d %d %d %d %.0f\n", fighter[l].age, fighter[l].wins, fighter[l].losses, fighter[l].KOs, fighter[l].height.feet, fighter[l].height.inches, fighter[l].weight);
	}
	
	// Closing text file
	fclose(fptr);
}

// Function to return the full name of the selected fighter
void selectedPlayer(char firstName[], char lastName[], int placeholder){
	// Declaring variables
	char junk[99];
	
	// Opening text file to be read from
	fptr = fopen("fightersCompleted.txt", "r");
	
	// In case text file doesn't exist
	if (fptr == NULL){
		printf("Error, file not opened properly");
	}
	
	// Assigning headers to a junk variable
	for (int x = 1; x <= 11; x++){
		fscanf(fptr, "%s", junk);
	}
	
	// Subtracting number of headers from placeholder value
	placeholder -= 11;
	
	// Ensuring that only the words before the selected entry are read into a junk variable, based on where in the line the placeholder is located
	if (placeholder % 12 == 1){
		for (int j = 1; j < placeholder; j++){
			fscanf(fptr, "%s", junk);
		}
	}
	else if (placeholder % 12 == 2){		
		for (int j = 1; j < placeholder - 1; j++){
			fscanf(fptr, "%s", junk);
		}
	}
	else if (placeholder % 12 == 3){								
		for (int j = 1; j < placeholder - 2; j++){
			fscanf(fptr, "%s", junk);
		}
	}
	
	// Assigning first and last name to variables, and reading nickname into a junk variable
	fscanf(fptr, "%s %s %s", firstName, junk, lastName);
	
	// Closing text file
	fclose(fptr);
}
