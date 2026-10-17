#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<Windows.h>
using namespace std;

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

short HowManyQuestions() {
	short NumbersOfQuestion = 0;
	do {

	cout << "How many questions do you want to answer [1--To--10] : ";
	cin >> NumbersOfQuestion;
	} while (NumbersOfQuestion<1 || NumbersOfQuestion>10);
	return NumbersOfQuestion;
}
enum enQuestionsLevels { Easy = 1, Medium = 2, Hard = 3, MixLevel = 4 };
enum enOperators { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, MixOp = 5 };
struct stQuestion{
	int Number1 = 0;
	int Number2 = 0;
	enOperators OperatorType;
	enQuestionsLevels QuestionLevel;
	int CorrectAnswer = 0;
	int	PlayerAnswer = 0;
	bool IsAnswerCorrect = false;
};

struct stQuizz {
	stQuestion QuestionList[100];
	short HowManyQuestions = 0;
	short RightAnswers = 0;
	short WrongAnswers = 0;
	enQuestionsLevels QuizzLevel;
	enOperators QuizzOperator;
	bool IsPass = false;
};
//GetQuestionLevel
enQuestionsLevels GetQuestionLevel() {
	short level;
	cout << "Choose The Level Of The Quiz :  Easy = 1, Medium = 2, Hard = 3, MixLevel = 4  ";
	cin >> level;
	return (enQuestionsLevels)level;
}
// GetQuestionOperator
enOperators GetQuestionOperator() {
	short Operator;
	cout << "Choose The Operator Of The Quiz :  Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, MixOp = 5  ";
	cin >> Operator;
	return (enOperators)Operator;
}
// GetRandomOperator
enOperators GetRandomOperator() {
	short Op = RandomNumber(1, 4);
	return (enOperators)Op;
}
int SimpleCalculator(int Num1 , int Num2 , enOperators Operator) {
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
// GetOperatorSymbol
char GetOperatorSymbol(enOperators Op) {
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
	default:
		return ' ';
	}
}
// OpToOperatorText
string OpToOperatorText(enOperators QuestionLevel)
{
	string arrOpToOperatorText[5] = { "Addition","Substraction","Multiplicaton","Division" , "MixOp"};
	return arrOpToOperatorText[QuestionLevel - 1];
}

// Get Level Name
string GetLevelName(enQuestionsLevels Level) {
	switch (Level)
	{
	case enQuestionsLevels::Easy:
		return "Easy";
		break;
	case enQuestionsLevels::Medium:
		return "Medium";
		break;
	case enQuestionsLevels::Hard:
		return "Hard";
		break;
	case enQuestionsLevels::MixLevel:
		return "Mix";
		break;
	default:
		return "Unknown";
	}
}
// GenerateQuestion 
stQuestion GenerateQuestion(enQuestionsLevels QuestionLevel , enOperators Operator) {

	stQuestion Question;
	if(QuestionLevel == enQuestionsLevels::MixLevel)
	{
		QuestionLevel = (enQuestionsLevels)RandomNumber(1, 3);
	}
	if (Operator == enOperators::MixOp)
	{
		Operator = GetRandomOperator();
	}

	Question.OperatorType = Operator;
	/* Switch Case */
 
	switch (QuestionLevel)
	{
		case enQuestionsLevels::Easy:
			Question.Number1 = RandomNumber(1, 10);
			Question.Number2 = RandomNumber(1, 10);

			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperatorType);
			Question.QuestionLevel = QuestionLevel;
			return Question;

		case enQuestionsLevels::Medium:
			// Generate medium question 
			Question.Number1 = RandomNumber(10, 50);
			Question.Number2 = RandomNumber(10, 50);
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperatorType);  
        	Question.QuestionLevel = QuestionLevel;  // struct stQuestion || int	PlayerAnswer = 0 ||	bool IsAnswerCorrect = false;		
			return Question;

		case enQuestionsLevels::Hard:
			// Generate hard question
			Question.Number1 = RandomNumber(50, 100);
			Question.Number2 = RandomNumber(50, 100);
			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperatorType);
			Question.QuestionLevel = QuestionLevel;
			return Question;
	}
	
	return Question;
}

//GenerateQuizzQuestion

void GenerateQuizzQuestion(stQuizz& Quizz) {
	for (short Question = 0; Question < Quizz.HowManyQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuizzLevel , Quizz.QuizzOperator);
	}
}
// IS Correct Answer
bool isCorrectAnswer(stQuizz Quizz , short QuestionNumber) {
	if(Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		return true;
	}
	return false;
}
// Print The Question;
void PrintQuestion(stQuizz Quizz , short QuestionNumber) {
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.HowManyQuestions << "]\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << " "<< GetOperatorSymbol(Quizz.QuestionList[QuestionNumber].OperatorType) << " "<< Quizz.QuestionList[QuestionNumber].Number2 << " = ?\n";
	cout << "----------------------------------\n";
}


// { Ask / Correct } Question Liste
void AskAndCorrectQuestionLists(stQuizz& Quizz) {

	for (int i = 0; i < Quizz.HowManyQuestions;i++)
	{
		PrintQuestion(Quizz, i);
		cin >> Quizz.QuestionList[i].PlayerAnswer;
		if (isCorrectAnswer(Quizz, i))
		{
			system("color 2F");
			Quizz.RightAnswers++;
			cout << "\nRight Answer\n";
		}
		else
		{
			system("color 4F");
			cout << "\a";
			Quizz.WrongAnswers++;
			cout << "\nWrong Answer\n";
			cout << "The Right Answer is : " << Quizz.QuestionList[i].CorrectAnswer << endl;
		}
	}
	Quizz.IsPass = (Quizz.RightAnswers > Quizz.WrongAnswers);
}
// Print Result
void PrintResult(stQuizz Quizz) {
	cout << "\n'***********************'\n";
	if(Quizz.IsPass)
	{
		cout << "\nCongratulations! You passed the quiz.\n";
	}
	else
	{
		cout << "\nSorry, you failed the quiz.\n";
	}
	cout << "\n'***********************'\n";
	cout << "Number of Question : " << Quizz.HowManyQuestions << endl;
	cout << "Number of Right Answers : " << Quizz.RightAnswers << endl;
	cout << "Number of False Answers : " << Quizz.WrongAnswers << endl;
	cout << "Questions Level : " << GetLevelName(Quizz.QuizzLevel) << endl;
	cout << "OperationType Level : " << OpToOperatorText(Quizz.QuizzOperator) << endl;
}
//PlayGameMath
void PlayGameMath() {
	stQuizz Quizz;
	char TryAgain = 'Y';
	do {
		system("color 07");
	Quizz.HowManyQuestions = HowManyQuestions();
	Quizz.QuizzLevel = GetQuestionLevel();
	Quizz.QuizzOperator = GetQuestionOperator();
	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionLists(Quizz);
	PrintResult(Quizz);
	cout << "\nTry Again ? [Y/N] : ";
	cin >> TryAgain;
	} while (TryAgain == 'Y' || TryAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	PlayGameMath();
	return 0;
}