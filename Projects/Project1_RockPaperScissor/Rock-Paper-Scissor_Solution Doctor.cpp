#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
// D A T A    I N F 0
enum enGameChoices{stone  = 1  , paper = 2 , scissors = 3};
enum enWinner {Player = 1  , Computer = 2 , Draw = 3 };

struct stReadInfo {
	short GameRound;
	enGameChoices PlayerChoice;
	enGameChoices ComputerChoice;
	enWinner WinnerRound;
	string WinnerName;
};

struct stGameResults {
	short GameRounds;
	short PlayerWinTimes;
	short ComputerWinTimes;
	short DrawTimes;
	enWinner WinnerGame;
	string WinnerName;
};

int RoundTimes() {
	int Rounds = 0;
	do {
		cout << "Enter the number of rounds you want to play [ 1--To--10 ]: ";
		cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);
	cout << endl;
	return Rounds;
}
// Ask user to enter the choice STONE OR PAPER OR SCISOR
enGameChoices GetChoiceUser() {
	short ChoiceUser = 0;
	do {
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> ChoiceUser;
	} while (ChoiceUser < 1 || ChoiceUser > 3);

	return (enGameChoices)ChoiceUser;
}
enGameChoices GetChoiceComputer() {
	return (enGameChoices)RandomNumber(1 , 3);
}
// Purpose : Who win the Round 
enWinner WhoWinTheRound(stReadInfo ReadInfo) {
	
	if (ReadInfo.PlayerChoice == ReadInfo.ComputerChoice)
		return enWinner::Draw;
	switch (ReadInfo.PlayerChoice)
	{
	  case enGameChoices::stone:
		if (ReadInfo.ComputerChoice == enGameChoices::scissors)
		 	return enWinner::Player;
		break;
	  case enGameChoices::paper:
       if (ReadInfo.ComputerChoice == enGameChoices::stone)
			  return enWinner::Player;
		  break;
	  case enGameChoices::scissors:
		  if (ReadInfo.ComputerChoice == enGameChoices::paper)
			  return enWinner::Player;
		  break;
	}
	return enWinner::Computer;
}
 // who win The Full Game
enWinner WhoWinTheGame(short PlayerWinTimes , short ComputerWinTimes) {

	if (PlayerWinTimes == ComputerWinTimes)
		return enWinner::Draw;
	else if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else
		return enWinner::Computer;
}
// string : FUNCTION Convert enum To String Representation
string ChoiceName(enGameChoices choice) {

	string arrChoices[3] = {"stone", "paper" , "scissors"};
	return arrChoices[choice - 1];
}
void PrintScreenColor(enWinner winner)
{
	if(winner == enWinner::Player)
		system("color 2F");// Print player winning color
	else if (winner == enWinner::Computer)
	{
		system("color 4F");// Print computer winning color
	    cout << "\a";
	}
	else 
		system("color 6F");
}
// string  Winner Name : FUNCTION Convert enum To String Representation
string WinnerName(enWinner Winner)
{
	string arrWinners[3] = { "Player" , "Computer" , "Draw" };
	return arrWinners[Winner - 1];
}

void PrintResultRound(stReadInfo ReadInfo) {
	cout << "\n____________ Round [ " << ReadInfo.GameRound << " ] ____________\n\n";
	cout << "Player Choice : " << ChoiceName(ReadInfo.PlayerChoice) << endl;
	cout << "Computer Choice : " << ChoiceName(ReadInfo.ComputerChoice) << endl;
	cout << "Winner in this Round : [" << ReadInfo.WinnerName<<" ]"<<endl;

	PrintScreenColor(ReadInfo.WinnerRound);
	cout << "_________________________________________\n" << endl;
}
// Function: PlayGame
// Purpose: Runs the game for a given number of rounds and determines the final winner.
stGameResults PlayGame(short HowManyRounds) {
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short Draws = 0;

	stReadInfo ReadInfo;
	for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		ReadInfo.GameRound = GameRound;
		ReadInfo.PlayerChoice = GetChoiceUser();
		ReadInfo.ComputerChoice = GetChoiceComputer();
		ReadInfo.WinnerRound = WhoWinTheRound(ReadInfo);
		ReadInfo.WinnerName = WinnerName(ReadInfo.WinnerRound);

		PrintResultRound(ReadInfo);
		if (ReadInfo.WinnerRound == enWinner::Player)
			PlayerWinTimes++;
		else if (ReadInfo.WinnerRound == enWinner::Computer)
			ComputerWinTimes++;
		else
			Draws++;

	}


	return { HowManyRounds , PlayerWinTimes  , ComputerWinTimes ,  Draws , WhoWinTheGame(PlayerWinTimes ,  ComputerWinTimes)  , WinnerName(WhoWinTheGame(PlayerWinTimes ,  ComputerWinTimes)) };
}

void StartGame() {
	char PlayAgain = 'Y';
	do {
		system("cls");  // Clear the screen before starting a new game.
		stGameResults GamesResults = PlayGame(RoundTimes());        // Play x rounds.
		cout << "\n \n----------------------Game Over winner :---------------------" << endl;
		       cout<<"----------------------Game Result ------------------------" << endl;

			   cout << "Total Rounds : " << GamesResults.GameRounds << endl;
			   cout << "Player Won Times : " << GamesResults.PlayerWinTimes << endl;
			   cout << "Computer Won Times : " << GamesResults.ComputerWinTimes << endl;
			   cout << "Draw Times : "  << GamesResults.DrawTimes << endl;
			   cout << "Winner  [ " << GamesResults.WinnerName<<" ]" <<endl;
			   cout << "\n Try Again ? YES OR NO (Y/N) :  ";
			   cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}