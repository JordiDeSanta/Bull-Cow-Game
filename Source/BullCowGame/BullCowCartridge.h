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

	UPROPERTY(EditAnywhere, Category = "Lives")
		int32 Lives;

	UPROPERTY(EditAnywhere, Category = "Dictionary")
		TArray<FString> HiddenWords;

private:

	void StartGame();

	bool bCorrectCharNum(FString Word);

	FString CharNum;

	int32 WordChars;

	int32 DLives = 3;

	FString HiddenWord;
};
