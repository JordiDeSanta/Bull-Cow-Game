// Fill out your copyright notice in the Description page of Project Settings.

#include "BullCowCartridge.h"
#include "Containers/UnrealString.h"
#include "Kismet/KismetSystemLibrary.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    StartGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    Bulls = 0;
    Cows = 0;
    ClearScreen();

    // Check if you won or lost
    if (bFinished)
    {
        PlayAgain(Input);
    };

    // Check if is the correct word
    if (Input != TEXT(""))
    {
        ProcessGuess(Input);
    };

    return;
}

void UBullCowCartridge::ProcessGuess(const FString Word)
{
    // Check characters in the word
    if (!bCorrectCharNum(Word))
    {
        return;
    };

    // Check isogram
    if (!bCheckIsogram(Word))
    {
        return;
    };

    // Try statement
    if (Word != HiddenWord && Lives <= 1)
    {
        PrintLine(TEXT("You Lose!"));
        bFinished = true; // Game finished (Lose)
        PrintLine(TEXT("Want to play again? y/n"));
        return;
    };

    // Lose statement
    if (Word != HiddenWord)
    {
        PrintLine(TEXT("Try Again"));
        Lives--; // Decrease lives
        PrintLine(FString::Printf(TEXT("You have %i opportunities"), Lives));
        PrintLine(FString::Printf(TEXT("The word have %i characters of length"), WordChars));
        BullsAndCows(Word);
        return;
    };
    
    // Win statement
    if (Word == HiddenWord)
    {
        PrintLine("You Win!");
        bFinished = true; // Game finished (Win)
        HiddenWords.RemoveSingle(HiddenWord); // Remove from the dictionary to no repeat
        PrintLine(TEXT("Want to play again? y/n"));
        return;
    };
}

void UBullCowCartridge::BullsAndCows(const FString InputBCG)
{
    for (int32 i = 0; i < WordChars; i++)
    {
        if (InputBCG[i] == HiddenWord[i])
        {
            Bulls++;
        }
        else
        {
            Cows++;
        }
    }

    // Print quantity of bulls & cows in the input
    PrintLine(FString::Printf(TEXT("Bulls: %i, Cows: %i"), Bulls, Cows));
}

bool UBullCowCartridge::bCorrectCharNum(FString Word)
{
    // Check number of characters
    if (WordChars != Word.Len())
    {
        PrintLine(FString::Printf(TEXT("%i characters please!"), WordChars));
        return false;
    };

    return true;
}

bool UBullCowCartridge::bCheckIsogram(const FString WordToCheck)
{
    for (int32 i = 0; i < WordChars; i++)
    {
        for (int32 j = 0; j < WordChars - i - 1; j++)
        {
            int32 h = i + j + 1;
            if (WordToCheck[i] == WordToCheck[h])
            {
                PrintLine("An isogram please!");
                return false; // Isn´t an isogram
            };
        };
    };

    return true; // Is an isogram
}

void UBullCowCartridge::StartGame()
{
    // Setup important variables
    int32 RandomNum = FMath::RandRange(0, HiddenWords.Num() - 1);
    HiddenWord = HiddenWords[RandomNum];

    // Number of characters of the hidden word and lives
    WordChars = HiddenWord.Len();
    Lives = WordChars;

    // Little welcome to player
    PrintLine(TEXT("Welcome to BullCowGame"));
    PrintLine(TEXT("Bulls are the number of correct letters in your guess and Cows wrong letters"));
    PrintLine(FString::Printf(TEXT("Guess the %i characters word"), WordChars));
    PrintLine(FString::Printf(TEXT("You have %i opportunities"), Lives));
    PrintLine(TEXT("Press enter to continue..."));

    return;
}

void UBullCowCartridge::PlayAgain(FString Answer)
{
    if (Answer == "y")
    {
        // Play again
        bFinished = false;
        StartGame();
    }
    else if (Answer == "n")
    {
        // Quit game
        auto Player = GetWorld()->GetFirstLocalPlayerFromController();
        auto Controller = GetWorld()->GetFirstPlayerController();
        UKismetSystemLibrary::QuitGame(Player, Controller, EQuitPreference::Quit, true);
    }

    return;
}


