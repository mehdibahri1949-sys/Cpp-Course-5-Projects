#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<Windows.h>

using namespace std;
                              /*  CHOICES  */
// Enums
enum enLevels { Easy = 1, Medium = 2, Hard = 3, MixLevel = 4 };
enum enOperators { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, MixOp = 5 };

/*  Principles && Importants Function */ 
//SimpleCalculator
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
int SimpleCalculator(int Num1, int Num2, enOperators Operator) {
	switch (Operator)
	{
	case enOperators::Addition:
		return Num1 + Num2;
		break;
	case enOperators::Subtraction:
		return Num1 - Num2;
		break;
	case enOperators::Multiplication:
		return Num1 * Num2;
		break;
	case enOperators::Division:
		return Num1 / Num2;
		break;
	default:
		return 0;
		break;
	}
}

                          /* Get Importand Values */
enOperators GetRandomOperator() {
	short Op = RandomNumber(1, 4);
	return (enOperators)Op;
}

//HowManyQuestions
short HowManyQuestions() {
	short NumbersOfQuestion = 0;
	do {
		cout << "How many questions do you want to answer [1--To--10] : ";
		cin >> NumbersOfQuestion;
	} while (NumbersOfQuestion < 1 || NumbersOfQuestion>10);   
	return NumbersOfQuestion;
}
//GetLevel
enLevels GetLevel(){
	short Level;
	do {
		cout << "Enter the level of difficulty [ Easy = 1, Medium = 2, Hard = 3, MixLevel = 4 ]: ";
		cin >> Level;
	} while (Level < 1 || Level > 4);

		return (enLevels)Level;
}
//GetOperator
enOperators GetOperator() {
	short Op;
	do {
		cout << "Enter the operator [ Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, MixOp = 5 ]: ";
		cin >> Op;
	} while (Op < 1 || Op > 5);

	return (enOperators)Op;
}
        /* Structs Info */
struct stQuestion {
	int Number1 = 0;
	int Number2 = 0;
	enOperators OperatorType;
	enLevels QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool IsAnswerCorrect = false;
};
struct stQuizz {
	stQuestion QuestionList[100];

	short HowManyQuestions = 0;
	enLevels LevelQuizz;
	enOperators OperatorQuizz;
	short RightAnswers = 0;
	short WrongAnswers = 0;
	bool IsPass = false;
};
// GenerateQuestions
stQuestion GenerateQuestion(enLevels Level , enOperators Operator)
{
	stQuestion Question;
	// Implementation for generating a single question
	//treat Case Mix
	if (Level == enLevels::MixLevel)
	{
		Level = (enLevels)RandomNumber(1, 3);

	}
	if (Operator == enOperators::MixOp)
	{
		Operator = GetRandomOperator();

    }
	switch (Level)
	{
		// Easy
		case enLevels::Easy:
			Question.Number1 = RandomNumber(1, 10);
			Question.Number2 = RandomNumber(1, 10);
			Question.QuestionLevel = Level;
			Question.OperatorType = Operator;
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperatorType);

			return Question;
        //Medium
		case enLevels::Medium:
			Question.Number1 = RandomNumber(10, 50);
			Question.Number2 = RandomNumber(10, 50);
			Question.QuestionLevel = Level;
			Question.OperatorType = Operator;
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperatorType);

			return Question;
		//Hard
		case enLevels::Hard:
			Question.Number1 = RandomNumber(50, 100);
			Question.Number2 = RandomNumber(50, 100);
			Question.QuestionLevel = Level;
			Question.OperatorType = Operator;
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperatorType);

			return Question;
	}
	return Question;
}
// GenerateQuizzQuestions
void GenerateQuizzQuestions(stQuizz &Quizz)
{

	// Implementation for generating quiz questions
	for (short i = 0; i < Quizz.HowManyQuestions; i++)
	{
		Quizz.QuestionList[i] = GenerateQuestion(Quizz.LevelQuizz, Quizz.OperatorQuizz);
	}
}
/*   Small Functions That Do single Task*/
int ReadPlayerAnswer() {
	int PlayerAnswer = 0;
	cin >> PlayerAnswer;
	return PlayerAnswer;
}
//Get Symbol op
char GetSymbolOperator(enOperators Op) {

	switch (Op)
	{
	case enOperators::Addition:
		return '+';
		break;

	case enOperators::Subtraction:
		return '-';
		break;

	case enOperators::Multiplication:
		return '*';
		break;

	case enOperators::Division:
		return '/';
		break;
	}

}
// Get Level Name
string GetOpName(enOperators Op) {
	switch (Op)
	{
	case enOperators::Addition:
		return "Addition";
		break;
	case enOperators::Subtraction:
		return "Subtraction";
		break;
	case enOperators::Multiplication:
		return "Multiplication";
		break;
	case enOperators::Division:
		return "Division";
		break;
		case enOperators::MixOp:
		return "Mix Operation";
		break;
	default:
		return "Unknown";
	}
}
bool IsRightAnswer(int PlayerAnswer, int CorrectAnswer) {
	return PlayerAnswer == CorrectAnswer;
}
// Print The Question
void PrintTheQuestion(stQuizz Quizz , short Number1ofTheQuestion) {

	cout << "Question [" << Number1ofTheQuestion + 1 << "/" << Quizz.HowManyQuestions << "]\n";
	cout << Quizz.QuestionList[Number1ofTheQuestion].Number1 << " "<<GetSymbolOperator(Quizz.QuestionList[Number1ofTheQuestion].OperatorType)<<" " << Quizz.QuestionList[Number1ofTheQuestion].Number2 <<" ?= ";
	cout << "\n------------------------------\n";

}

// Get Level Name
string GetLevelName(enLevels Level) {
	switch (Level)
	{
	case enLevels::Easy:
		return "Easy";
		break;
	case enLevels::Medium:
		return "Medium";
		break;
	case enLevels::Hard:
		return "Hard";
		break;
	case enLevels::MixLevel:
		return "Mix";
		break;
	default:
		return "Unknown";
	}
}
/*   Small Functions That Do single Task*/


//Correct Question Number
void CorrectQuestionNumber(stQuizz &Quizz, short QuestionNumber) {
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.WrongAnswers++;
		Quizz.QuestionList[QuestionNumber].IsAnswerCorrect = false;
		cout << "Wrong Answer  :(\n";
		system("color 4F");
		cout << "\a"; 
		cout << "The Right Answer is : " << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
	}
	else
	{ 
		Quizz.QuestionList[QuestionNumber].IsAnswerCorrect = true;
		Quizz.RightAnswers++;
		system("color 2F");
		cout << "Right Answer :)";
	}
	cout << "\n---------------------\n";
	
}
string GetFinalResult(bool Result) {
	if (Result == true)
	return "Pass";
	else 
	return "Fail";

}
// AskAndCorretctQuestionList
void AskAndCorretctQuestionList(stQuizz &Quizz) {
	
	bool isCorrectAnswer = true;
	for(short i = 0 ; i< Quizz.HowManyQuestions; i++)
	{	// Implementation for asking and correcting each question
	
		PrintTheQuestion(Quizz, i);
		Quizz.QuestionList[i].PlayerAnswer = ReadPlayerAnswer();

		Quizz.QuestionList[i].IsAnswerCorrect = IsRightAnswer(Quizz.QuestionList[i].PlayerAnswer , Quizz.QuestionList[i].CorrectAnswer);
		CorrectQuestionNumber(Quizz, i);
	}
	Quizz.IsPass = (Quizz.RightAnswers > Quizz.WrongAnswers);
	
}
/* Add New* Thing :  Numbers of Quiz  */

short NumbersOfQuizz() {
	short QuizzNumbers = 0;
	do {

		cout << "Pls enter The Numbers Of Quizz : ";
		cin >> QuizzNumbers;

	} while (QuizzNumbers < 1 || QuizzNumbers > 10); 
	return QuizzNumbers;
}
/* Add New* Thing :  Numbers of Quiz  */


// Print Result
void PrintResult(stQuizz Quizz) {
	cout << "\n'***********************'\n";
	cout<< GetFinalResult(Quizz.IsPass);
	cout << "\n'***********************'\n";

	cout << "Number of Questionss : " << Quizz.HowManyQuestions << endl;
	cout << "Number of Right Answers : " << Quizz.RightAnswers << endl;
	cout << "Number of False Answers : " << Quizz.WrongAnswers << endl;
	cout << "Quiz Level : " << GetLevelName(Quizz.LevelQuizz) << endl;
	cout << "OperationType Level in Quizz : " << GetOpName(Quizz.OperatorQuizz) << endl;
	cout << "\n---------------------------\n";
}
/* Global Summery Result */

void GLOBAL_RESULT(stQuizz QuizzList[] , short NumberOfQuizz) {
	cout << "\n######### FINAL SUMMARY #########\n";
	for (short i = 0; i < NumberOfQuizz; i++)
	{
		cout << " ************* Quizz : " << i +1<< " **********\n";
			cout<< QuizzList[i].RightAnswers << " Right / "
			<< QuizzList[i].WrongAnswers << " Wrong : "  
			<< " Result is this Quizz "<<GetFinalResult(QuizzList[i].IsPass) << endl;
		cout << "\n----------------------------------\n";
	}
}

void PlayGameMath() {
	
	stQuizz QuizzList[100];
	short NumberOfQuizz = NumbersOfQuizz();
	for (short i = 0; i < NumberOfQuizz; i++)
	{
		cout << "\n-----Quiz : " << i + 1 << "------\n";
	QuizzList[i].HowManyQuestions = HowManyQuestions();
	QuizzList[i].LevelQuizz = GetLevel();
	QuizzList[i].OperatorQuizz = GetOperator();

	GenerateQuizzQuestions(QuizzList[i]);
	AskAndCorretctQuestionList(QuizzList[i]);
	PrintResult(QuizzList[i]);
	}
	GLOBAL_RESULT(QuizzList, NumberOfQuizz);
}

void StartGame() {
	char TryAgain = 'Y';
	do {
		system("color 07");
		PlayGameMath();
		cout << "\n\n\nTry Again Y/N ? ";
		cin >> TryAgain;
	} while (TryAgain == 'Y' || TryAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}