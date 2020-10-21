// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Number of characters of the hidden word
    WordChars = HiddenWord.Len();
    CharNum.AppendInt(WordChars);

    
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

bool UBullCowCartridge::bCorrectCharNum(FString Word)
{
    // Check number of characters
    if (WordChars != Word.Len())
    {
        FString Phrase = TEXT("" + CharNum + " characters please!");
        PrintLine(Phrase);
        return false;
    };

    return true;
}


