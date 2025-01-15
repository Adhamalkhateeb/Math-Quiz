#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbol(enOperationType Op)
{
    switch (Op)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mul:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy", "Med", "Hard" , "Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

short ReadHowManyQuestions()
{
    short number;
    cout << "Enter number of Questions you Want ?";
    cin >> number;
    return number;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Choose Difficulty questions: [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OperationType;
    do
    {
        cout << " Choose Operation Type: [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);
    return (enOperationType)OperationType;
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAanswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;

};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType Op)
{
    switch (Op)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mul:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{

    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
    {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }
    if (OperationType == enOperationType::MixOp)
    {
        OperationType = GetRandomOperationType();
    }

    Question.OperationType = OperationType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAanswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
    case enQuestionLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAanswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAanswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;

        return Question;
    }

    return Question;
}

void GenerateQuizQuestions(stQuizz& Quiz)
{
    for (int Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OpType);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintQuestion(stQuizz quiz, short NumberOfQuestion)
{
    cout << "\n";
    cout << "Question [" << NumberOfQuestion + 1 << "/" << quiz.NumberOfQuestions << "] \n\n";
    cout << quiz.QuestionList[NumberOfQuestion].Number1 << endl;
    cout << quiz.QuestionList[NumberOfQuestion].Number2 << " ";
    cout << GetOpTypeSymbol(quiz.QuestionList[NumberOfQuestion].OperationType);
    cout << "\n-------------\n";
}

void CorrectQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAanswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :-( \n";
        cout << "The Right Answer is : ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAanswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer :-) \n";
    }

    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintQuestion(Quiz, QuestionNumber);

        Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectQuestionAnswer(Quiz, QuestionNumber);
    }

    Quiz.IsPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool pass)
{
    if (pass)
        return "Pass :-)";
    else
        return  "Fail:-(";
}

void PrintQuizResults(stQuizz& Quiz)
{
    cout << "\n";
    cout << "------------------------------\n\n";
    cout << "FinalResultIs " << GetFinalResultsText(Quiz.IsPass);
    cout << "--------------------------------\n\n";

    cout << "Number of Questions : " << Quiz.NumberOfQuestions << endl;
    cout << "Question Level      : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
    cout << "OperationType       : " << GetOpTypeSymbol(Quiz.OpType) << endl;
    cout << "Number Of Right Answers: " << Quiz.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong answers: " << Quiz.NumberOfWrongAnswers << endl;
    cout << "------------------------------------\n";
}

void PlayMathGame()
{
    stQuizz Quiz;
    Quiz.NumberOfQuestions = ReadHowManyQuestions();
    Quiz.QuestionLevel = ReadQuestionLevel();
    Quiz.OpType = ReadOpType();

    GenerateQuizQuestions(Quiz);
    AskAndCorrectQuestionListAnswer(Quiz);
    PrintQuizResults(Quiz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char TestAgain = 'y';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << "\n\nDo You Want To play Again ? ";
        cin >> TestAgain;
    } while (TestAgain == 'y' || TestAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}