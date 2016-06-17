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
        gameTime += GetWorld()->GetDeltaSeconds()*2; // Ever half second
        
        if(gameTime >= 1) // Increase score by one every half second
        {
            levelScore += int32(gameTime);
            gameTime -= int32(gameTime);
        }
        
        /// Set speed based on score
        /*if(levelScore>100)
        {
            levelSpeed = 10.0f;
        }
        else if(levelScore>75)
        {
            levelSpeed = 8.0f;
        }
        else if(levelScore>50)
        {
            levelSpeed = 6.5f;
        }
        else
        {
            levelSpeed = 5.0f;
        }*/
    }
    
}
