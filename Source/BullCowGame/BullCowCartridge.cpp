// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Containers/UnrealString.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    StartGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (!bCorrectCharNum(Input))
    {
        return;
    };

    // Check if the word is an isogram
    for (int32 i = 0; i < WordChars; i++)
    {
        for (int32 j = 0; j < WordChars - i - 1; j++)
        {
            int32 h = i + j + 1;
            if (HiddenWord[i] == HiddenWord[h])
            {
                PrintLine("An isogram please!");
                return;
            };
        };
    };

    // Check player input
    if (Input != TEXT(""))
    {
        if (Input != HiddenWord)
        {
            // Live check and deprecation
            if (Lives <= 0)
            {
                PrintLine(TEXT("You Lose!"));
                return;
            }
            else
            {
                PrintLine(TEXT("Try Again"));
                Lives--;
                return;
            };
        }
        else
        {
            PrintLine("You Win!");
            return;
        };
    };

    return;
}

void UBullCowCartridge::StartGame()
{
    // Setup important variables
    int32 RandomNum = FMath::RandRange(0, HiddenWords.Num() - 1);
    HiddenWord = HiddenWords[RandomNum];
    Lives = DLives;

    // Number of characters of the hidden word
    WordChars = HiddenWord.Len();
    
    // Little welcome to player
    PrintLine(TEXT("Welcome to BullCowGame"));
    PrintLine(FString::Printf(TEXT("Guess the %i"), WordChars));
    PrintLine(TEXT("Press enter to continue..."));

    return;
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


