#include <iostream>
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationsType { Add = 1, Sub = 2, Mul = 3, Div = 4, mix = 5 };

enum enRightOrWrong { Right = 1, Wrong = 2 };

enum enPassOrFail { Pass = 1, Fail = 2, Draw = 3 };

struct stQuestionsInfo
{
    short RoundNumber = 0;
    short Operand1 = 0;
    short Operand2 = 0;
    short Answer = 0;
    short CorrectAnswer;
    char Operator;
    enOperationsType OperationsType;
    enQuestionsLevel QuestionsLevel;
    enRightOrWrong RightOrWrong;
    string RightOrWrongName;
};

struct stGameResults
{
    short NumberOfQuestions = 0;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    enPassOrFail PassOrFail;
    string PassOrFailName = "";
    enQuestionsLevel QuestionsLevel;
    string QuestionsLevelName = "";
    enOperationsType OperationsType;
    string OperationsTypeName = "";
};

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionsLevel = 1;

    do
    {
        cout << "\nEnter Questions Level: [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionsLevel;

    } while (QuestionsLevel < 1 || QuestionsLevel >4);

    return enQuestionsLevel(QuestionsLevel);
}

enOperationsType ReadOperationsType()
{
    short OperationsType = 1;

    do
    {
        cout << "\nEnter Operations Type: [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OperationsType;

    } while (OperationsType < 1 || OperationsType >5);

    return enOperationsType(OperationsType);
}

string QuestionsLevelName(enQuestionsLevel QuestionsLevel)
{
    string arrQuestionsLevel[4] = { "Easy","Med","Hard","Mix" };
    return arrQuestionsLevel[QuestionsLevel - 1];
}

string OperationsTypeName(enOperationsType OperationsType)
{
    string arrOperationsType[5] = { "Add","Sub","Mul","Div","Mix" };
    return arrOperationsType[OperationsType - 1];
}

string RightOrWrongName(enRightOrWrong RightOrWrong)
{
    string arrRightOrWrong[2] = { "Right","Wrong" };
    return arrRightOrWrong[RightOrWrong - 1];
}

string PassOrFailName(enPassOrFail PassOrFail)
{
    string arrPassOrFail[3] = { "Pass","Fail","Draw" };
    return arrPassOrFail[PassOrFail - 1];
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

enPassOrFail WhatIsFinalResult(short NumberOfRightQuestions, short NumberOfWrongQuestions)
{
    if (NumberOfRightQuestions > NumberOfWrongQuestions)
        return enPassOrFail::Pass;
    else if (NumberOfRightQuestions < NumberOfWrongQuestions)
        return enPassOrFail::Fail;
    else
        return enPassOrFail::Draw;
}

string GetFinalResultFace(enPassOrFail PassOrFail)
{
    switch (PassOrFail)
    {
    case enPassOrFail::Pass:
        return ":-)";
        break;
    case enPassOrFail::Fail:
        return ":-(";
        break;
    default:
        return ":-|";
    }
}

void SetAnswerScreenColor(enRightOrWrong RightOrWrong)
{
    switch (RightOrWrong)
    {
    case enRightOrWrong::Right:
        system("color 2F");
        break;

    case enRightOrWrong::Wrong:
        system("color 4F");
        cout << "\a";
        break;
    }
}

void SetFinalScreenColor(enPassOrFail PassOrFail)
{
    switch (PassOrFail)
    {
    case enPassOrFail::Pass:
        system("color 2F");
        break;

    case enPassOrFail::Fail:
        system("color 4F");
        cout << "\a";
        break;

    default:
        system("color 6F");
    }
}

void PrintFinalResultsScreen(enPassOrFail PassOrFail)
{
    SetFinalScreenColor(PassOrFail);

    cout << "\n____________________________________________________________\n\n";
    cout << "        Final Results is " << PassOrFailName(PassOrFail) << " " << GetFinalResultFace(PassOrFail);
    cout << "\n____________________________________________________________\n\n";

}

void PrintFinalResultsInfo(stGameResults GameResults)
{
    cout << "Number of Questions: " << GameResults.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GameResults.QuestionsLevelName << endl;
    cout << "OpType             : " << GameResults.OperationsTypeName << endl;
    cout << "Number of Right Answers: " << GameResults.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << GameResults.NumberOfWrongAnswers << endl;
    cout << "____________________________________________________________\n\n";
}

stGameResults FillGameResults(stQuestionsInfo QuestionsInfo, short HowManyRounds, short NumberOfRightAnswers, short NumberOfWrongAnswers)
{
    stGameResults GameResults;

    GameResults.PassOrFail = WhatIsFinalResult(NumberOfRightAnswers, NumberOfWrongAnswers);
    GameResults.PassOrFailName = PassOrFailName(GameResults.PassOrFail);
    GameResults.NumberOfQuestions = HowManyRounds;
    GameResults.QuestionsLevelName = QuestionsLevelName(QuestionsInfo.QuestionsLevel);
    GameResults.OperationsTypeName = OperationsTypeName(QuestionsInfo.OperationsType);
    GameResults.NumberOfRightAnswers = NumberOfRightAnswers;
    GameResults.NumberOfWrongAnswers = NumberOfWrongAnswers;

    return GameResults;
}

short GetRandomOperands(enQuestionsLevel QuestionsLevel)
{
    switch (QuestionsLevel)
    {
    case enQuestionsLevel::Easy:
        return RandomNumber(1, 10);
        break;

    case enQuestionsLevel::Med:
        return RandomNumber(10, 50);
        break;

    case enQuestionsLevel::Hard:
        return RandomNumber(50, 200);
        break;

    case enQuestionsLevel::Mix:
        return RandomNumber(1, 200);
        break;
    }
}

char GetRandomOperator()
{
    char Operator;
    do
    {
        Operator = char(RandomNumber(42, 47));

    } while (!(Operator == '+' || Operator == '-' || Operator == '*' || Operator == '/'));

    return Operator;
}

char GetOperationsType(enOperationsType OperationsType)
{
    switch (OperationsType)
    {
    case enOperationsType::Add:
        return '+';
        break;

    case enOperationsType::Sub:
        return '-';
        break;

    case enOperationsType::Mul:
        return '*';
        break;

    case enOperationsType::Div:
        return '/';
        break;

    case enOperationsType::mix:
        return GetRandomOperator();
        break;
    }
}

stQuestionsInfo FillQuestionsInfo()
{
    stQuestionsInfo QuestionsInfo;

    QuestionsInfo.QuestionsLevel = ReadQuestionsLevel();
    QuestionsInfo.OperationsType = ReadOperationsType();

    return QuestionsInfo;
}

void GenerateQuestions(stQuestionsInfo& QuestionsInfo)
{
    QuestionsInfo.Operand1 = GetRandomOperands(QuestionsInfo.QuestionsLevel);
    QuestionsInfo.Operand2 = GetRandomOperands(QuestionsInfo.QuestionsLevel);
    QuestionsInfo.Operator = GetOperationsType(QuestionsInfo.OperationsType);
}

void PrintQuestions(stQuestionsInfo& QuestionsInfo)
{
    cout << QuestionsInfo.Operand1 << endl;
    cout << QuestionsInfo.Operand2 << " " << QuestionsInfo.Operator << endl;
    cout << "_____________________\n";
    cin >> QuestionsInfo.Answer;
}

short GetCorrectAnswer(stQuestionsInfo& QuestionsInfo)
{
    switch (QuestionsInfo.Operator)
    {
    case '+':
        return (QuestionsInfo.Operand1 + QuestionsInfo.Operand2);
        break;

    case '-':
        return (QuestionsInfo.Operand1 - QuestionsInfo.Operand2);
        break;

    case '*':
        return (QuestionsInfo.Operand1 * QuestionsInfo.Operand2);
        break;

    case '/':
        return (QuestionsInfo.Operand1 / QuestionsInfo.Operand2);
        break;
    }
}

void RightOrWrongAnswer(stQuestionsInfo& QuestionsInfo)
{
    QuestionsInfo.CorrectAnswer = GetCorrectAnswer(QuestionsInfo);

    if ((QuestionsInfo.Answer) == (QuestionsInfo.CorrectAnswer))
        QuestionsInfo.RightOrWrong = enRightOrWrong::Right;
    else
        QuestionsInfo.RightOrWrong = enRightOrWrong::Wrong;
}

void PrintQuestionResult(stQuestionsInfo& QuestionsInfo)
{
    switch (QuestionsInfo.RightOrWrong)
    {
    case enRightOrWrong::Right:
        cout << "\nRight Answer :-)\n\n";
        SetAnswerScreenColor(QuestionsInfo.RightOrWrong);
        break;

    default:
        cout << "\nWrong Answer :-(\n";
        cout << "The Right Answer is: " << (QuestionsInfo.CorrectAnswer) << endl << endl;
        SetAnswerScreenColor(QuestionsInfo.RightOrWrong);
    }
}

stGameResults PlayGame(short HowManyQuestions)
{
    stQuestionsInfo QuestionsInfo = FillQuestionsInfo();
    short  NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;

    for (short GameRound = 1;GameRound <= HowManyQuestions;GameRound++)
    {
        cout << "\nQuestion [" << GameRound << "/" << HowManyQuestions << "]\n\n";
        QuestionsInfo.RoundNumber = GameRound;
        GenerateQuestions(QuestionsInfo);
        PrintQuestions(QuestionsInfo);
        RightOrWrongAnswer(QuestionsInfo);
        PrintQuestionResult(QuestionsInfo);

        switch (QuestionsInfo.RightOrWrong)
        {
        case enRightOrWrong::Right:
            NumberOfRightAnswers++;
            break;
        default:
            NumberOfWrongAnswers++;
        }
    }

    return FillGameResults(QuestionsInfo, HowManyQuestions, NumberOfRightAnswers, NumberOfWrongAnswers);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyQuestions());
        PrintFinalResultsScreen(GameResults.PassOrFail);
        PrintFinalResultsInfo(GameResults);

        cout << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
