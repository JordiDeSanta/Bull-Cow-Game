// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Number of characters of the hidden word
    FString CharNum;
    CharNum.AppendInt(HiddenWord.Len());
    
    // Presentation phrase
    FString Phrase = TEXT("Guess the " + CharNum + " characters word (isogram)");
    
    // Little welcome to player
    PrintLine(TEXT("Welcome to BullCowGame"));
    PrintLine(Phrase);
    PrintLine(TEXT("Press enter to continue..."));

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Check player input
    if (Input != TEXT(""))
    {
        if (Input != HiddenWord)
        {
            if (Lives <= 0)
            {
                PrintLine(TEXT("You Lose!"));
            }
            else
            {
                PrintLine(TEXT("Try Again"));
                Lives--;
            };
        }
        else
        {
            PrintLine("You Win!");
        };  
    }
}

