// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome tto BullCowGame, Player."));
    PrintLine(TEXT("How many cows are in this place"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // Check player input
    if (Input != TEXT(""))
    {
            // Guess the isogram
            if (HiddenWord == Input)
            {
                PrintLine(TEXT("You Win!"));
            }
            else
            {
                PrintLine(TEXT("Try Again"));
                ClearScreen();
                Lives--;

                // Checking the number of lives
                if (Lives <= 0)
                {
                    PrintLine(TEXT("You Lose"));
                };
            };
    }
    else
    {
        ClearScreen();
    };
}

