// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "EndlessRunner.h"
#include "EndlessRunnerGameMode.h"
#include "MyPaperCharacter.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AMyPaperCharacter::StaticClass();
}

void AEndlessRunnerGameMode::BeginPlay()
{
    Super::BeginPlay();
    levelScore = 0;
}

void AEndlessRunnerGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    if(bGameStarted)
    {
        gameTime += GetWorld()->GetDeltaSeconds()*2; // Every half second
        
        if(gameTime >= 1) // Increase score by one every half second
        {
            levelScore += int32(gameTime);
            gameTime -= int32(gameTime);
        }
    }
    
}
