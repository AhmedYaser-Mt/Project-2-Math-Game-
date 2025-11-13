#include <iostream>
using namespace std;

enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperrationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbol(enOperrationType OpType)
{
    switch (OpType)
    {
    case enOperrationType::Add:
        return "+";
    case enOperrationType::Sub:
        return "-";
    case enOperrationType::Mult:
        return "*";
    case enOperrationType::Div:
        return "/";
    case enOperrationType::MixOp:
        return "Mix";
    }
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 1;

    do
    {
        cout << "How many Questions do you want to answer ? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions>100);

    return NumberOfQuestions;
}

short RandomNumber(short From, short To)
{
    short RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

enQuestionLevel ReadQuestionsLevel()
{
    short QuestionsLevel = 0;
    do
    {
        cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionsLevel;

    } while (QuestionsLevel < 1 || QuestionsLevel>4);

    return enQuestionLevel(QuestionsLevel);
}

enOperrationType ReadOpType()
{
    short OpType = 0;
    do
    {
        cout << "Enter Operration Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;

    } while (OpType < 1 || OpType>5);

    return enOperrationType(OpType);
}

struct stQuestion
{
    short Number1 = 0;
    short Number2 = 0;
    enQuestionLevel QuestionLevel;
    enOperrationType OperrationType;
    short CorrectAnswer = 0;
    short PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionsLevel;
    enOperrationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool IsPass = false;
};

short SimpleCalculator(short Number1, short Number2, enOperrationType OpType)
{
    switch (OpType)
    {
    case enOperrationType::Add:
        return (Number1 + Number2);
    case enOperrationType::Sub:
        return (Number1 - Number2);
    case enOperrationType::Mult:
        return (Number1 * Number2);
    case enOperrationType::Div:
        return (Number1 / Number2);
    default:
        return (Number1 + Number2);
    }
}

enOperrationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return enOperrationType(Op);
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperrationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
    {
        QuestionLevel = enQuestionLevel(RandomNumber(1, 3));
    }

    if (OpType == enOperrationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperrationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperrationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperrationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperrationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }

    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0;Question < Quizz.NumberOfQuestions;Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

short ReaQuestionAnswer()
{
    short Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperrationType);
    cout << "\n_______" << endl;
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

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :-( \n";
        cout << "The right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
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

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions;QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReaQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool Pass)
{
    if (Pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "________________________________\n\n";
    cout << "Final Results is " << GetFinalResultText(Quizz.IsPass);
    cout << "\n_______________________________\n\n";

    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "________________________________\n";
}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);

    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();

        cout << endl << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
