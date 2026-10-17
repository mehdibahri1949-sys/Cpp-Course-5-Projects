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
// Dtata Info {enums}
enum enChoices { stone = 1 , paper = 2 , scissor = 3  };
enum enWinner {player = 1 , computer = 2 , draw = 3 };
//  Struct for Round 1 
struct stReadInfo {
	short GameRound = 0;
	enChoices PlayerChoice;
	enChoices ComputerChoice;
	enWinner WinnerRound;
	string WinnerName;
};
//  Struct for Game Results 
struct stGameResults {
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner WinnerGame;
	string WinnerName;
};
// Round Times
int RoundTimes() {
	int Rounds = 0;
	do {
		cout << "Enter the number of rounds you want to play [ 1--To--10 ]: ";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds > 10);
	cout << endl;
	return Rounds;
}

void RoundBegin(short i) {
	cout << "Round Begin [" << i<<" ]\n";
}

// Get Choice User and then cast the value to enum (conversion int to Enum
enChoices ChoiceUser() {
	short choiceUser = 0;
	cout << "Your Choice : stone = [ 1 ] , paper = [ 2 ], scissor = [ 3 ]  : ";
	cin >> choiceUser;
	return (enChoices)choiceUser;
}
enChoices ChoiceComputer() {
	return (enChoices)RandomNumber(1, 3);
}

// Who win the Round

enWinner WhowintheRound(stReadInfo ReadInfo) {
	if(ReadInfo.PlayerChoice == ReadInfo.ComputerChoice)
		return enWinner::draw;
	// Players
	else if (ReadInfo.PlayerChoice == enChoices::stone && ReadInfo.ComputerChoice == enChoices::scissor)
		return enWinner::player;
	else if (ReadInfo.PlayerChoice == enChoices::paper && ReadInfo.ComputerChoice == enChoices::stone)
		return enWinner::player;
	else if (ReadInfo.PlayerChoice == enChoices::scissor && ReadInfo.ComputerChoice == enChoices::paper)
		return enWinner::player;
	
	else
		return enWinner::computer;
}
//Who win the Game

enWinner WhoWintheGame(short PlayerWinTimes , short ComputerWinTimes) {

	if(PlayerWinTimes > ComputerWinTimes)
		return enWinner::player;
	else if(ComputerWinTimes > PlayerWinTimes)
		return enWinner::computer;
	else
		return enWinner::draw;
}
// Winner Name 
string WinnerName(enWinner Winner) {
	string arrWinnerName[3] = { "Player" , "Computer" ,"Draw" };

	return arrWinnerName[Winner - 1];

}
//Print Screen Color
void PrintScreenColor(enWinner winner) {
	if (winner == enWinner::player)
		system("color 2F");
	else if (winner == enWinner::computer)
	{

		system("color 4F");
		cout << "\a";
	}
	else
		system("color 6F"); // yellow color
}
// Choice name convert enum to string7

string ChoiceName(enChoices choice) {

	if(choice == enChoices::stone)
		return "Stone";
	else if(choice == enChoices::paper)
		return "Paper";
	else
		return "Scissor";
}
// PrintRoundResult
void PrintRoundResult(stReadInfo ReadInfo) {
	//PrintRoundResult(ReadInfo.GameRound);
	cout << "\n____________ Round [ " << ReadInfo.GameRound << " ] ____________\n\n";

	cout << "Player Choice : " << ChoiceName(ReadInfo.PlayerChoice) << endl;
	cout << "Computer Choice : " << ChoiceName(ReadInfo.ComputerChoice) << endl;
	cout<< "Winner : [ " << WinnerName(ReadInfo.WinnerRound) <<" ]" << endl;
	PrintScreenColor(ReadInfo.WinnerRound);
	cout << "__________________________________________________________\n\n";
}

// Print Game Result
void PrintGameResult(stGameResults GameResults) {
cout << "\n \n----------------------Game Over winner :---------------------" << endl;
cout<< "\n____________ Game Result ____________\n\n";

cout << "Game Rounds : " << GameResults.GameRounds << endl;
cout << "Player Win Times : " << GameResults.PlayerWinTimes << endl;
cout << "Computer Win Times : " << GameResults.ComputerWinTimes << endl;
cout << "Draw Times : " << GameResults.DrawTimes << endl;
cout << "Winner : [" << GameResults.WinnerName <<" ]" <<endl;

}

stGameResults PlayGames(short HowManyRounds) {
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawWinTimes = 0;

    stReadInfo ReadInfo;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		RoundBegin(GameRound);
		ReadInfo.GameRound = GameRound;
	    ReadInfo.PlayerChoice = ChoiceUser();
	    ReadInfo.ComputerChoice = ChoiceComputer();
		ReadInfo.WinnerRound = WhowintheRound(ReadInfo);
		ReadInfo.WinnerName = WinnerName(ReadInfo.WinnerRound);
  
		PrintRoundResult(ReadInfo);

		if (ReadInfo.WinnerRound == enWinner::player)
			PlayerWinTimes++;
		else if (ReadInfo.WinnerRound == enWinner::computer)
			ComputerWinTimes++;
		else
			DrawWinTimes++;
	}

	/*
	
	struct stGameResults { 	short GameRounds = 0;	short PlayerWinTimes = 0;		short ComputerWinTimes = 0; short DrawTimes = 0; 	enWinner WinnerGame;	string WinnerName;
	*/
	return { HowManyRounds , PlayerWinTimes , ComputerWinTimes , DrawWinTimes , WhoWintheGame(PlayerWinTimes , ComputerWinTimes) , WinnerName(WhoWintheGame(PlayerWinTimes , ComputerWinTimes))};

}
void StartGame() {
	char PlayAgain = 'x';

	do {
		stGameResults GameResults = PlayGames(RoundTimes());
		PrintGameResult(GameResults);
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