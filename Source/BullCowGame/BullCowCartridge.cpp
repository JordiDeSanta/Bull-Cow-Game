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
    ClearScreen();

    // Check if you lose or win
    if (bFinished)
    {
        PlayAgain(Input);
    };

    // Check characters in the word
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

    // Check if is the correct word
    if (Input != TEXT(""))
    {
        if (Input != HiddenWord)
        {
            // Live check and deprecation
            if (Lives <= 0)
            {
                PrintLine(TEXT("You Lose!"));
                bFinished = true;
                PrintLine(TEXT("Want to play again? y/n"));
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
            bFinished = true;
            PrintLine(TEXT("Want to play again? y/n"));
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

    // Number of characters of the hidden word and lives
    WordChars = HiddenWord.Len();
    Lives = WordChars - 1;
    
    // Little welcome to player
    PrintLine(TEXT("Welcome to BullCowGame"));
    PrintLine(FString::Printf(TEXT("Guess the %i characters word"), WordChars));
    PrintLine(FString::Printf(TEXT("You have %i opportunities"), Lives + 1));
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


