// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "EndlessRunnerGameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.

/*
This GameMode keeps track of the player's score, the speed of the level, and whether or not the game has started
*/
UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AEndlessRunnerGameMode();
    
    // Called when the game starts
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    
    // Is Game Started
    bool bGameStarted = false;
    
    float levelSpeed = 7.0f;
    
    // Player's score
    UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = PlayerScore)
    int32 levelScore;
    
    // Side view camera 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
    class UCameraComponent* SideViewCameraComponent;

private:
    float gameTime = 0.0f; 
};
