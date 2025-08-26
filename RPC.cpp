#include <iostream>   
#include <cstdlib>    
#include <ctime>      
using namespace std;


enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };



enum enWinner { Player1 = 1, Player2 = 2, Draw = 3 };



struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice Player2Choice;
    enWinner Winner;
    string WinnerName;
};



struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Player2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};




enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{

    if (RoundInfo.Player1Choice == RoundInfo.Player2Choice)
        return enWinner::Draw;


    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.Player2Choice == enGameChoice::Paper) ? enWinner::Player2 : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.Player2Choice == enGameChoice::Scissors) ? enWinner::Player2 : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.Player2Choice == enGameChoice::Stone) ? enWinner::Player2 : enWinner::Player1;
    }
}


enWinner WhoWonTheGame(short Player1WinTimes, short player2WinTimes)
{
    if (Player1WinTimes > player2WinTimes) return enWinner::Player1;
    else if (player2WinTimes > Player1WinTimes) return enWinner::Player2;
    else return enWinner::Draw;
}


string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}


string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Player2", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}


enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

enGameChoice ReadPlayer2Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}


void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.Player2Choice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;
}


stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, Player2WinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.Player2Choice = ReadPlayer2Choice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Player2)
            Player2WinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return { HowManyRounds, Player1WinTimes, Player2WinTimes, DrawTimes, WhoWonTheGame(Player1WinTimes, Player2WinTimes), WinnerName(WhoWonTheGame(Player1WinTimes, Player2WinTimes)) };
}


void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");
        stGameResults GameResults = PlayGame(3);
        cout << "\nGame Over! Winner: " << GameResults.WinnerName << endl;

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
    
    StartGame();
    return 0;
}
