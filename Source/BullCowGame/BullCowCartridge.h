// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void OnInput(const FString& Input) override;

	void ProcessGuess(const FString Word);

	UPROPERTY(EditAnywhere, Category = "Dictionary")
		TArray<FString> HiddenWords;

	

private:

	// Game Loop
	void StartGame();
	void PlayAgain(FString Answer);
	bool bCorrectCharNum(FString Word);

	// Important stats for the gameplay
	FString CharNum;
	int32 Lives;
	int32 WordChars;
	bool bFinished = false;
	FString HiddenWord;
};
