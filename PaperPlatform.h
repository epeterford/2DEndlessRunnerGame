// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "PaperPlatform.generated.h"
/**
 *PaperPlatform gets level speed from EndlessRunnerGameMode and moves towards the player along the X axis
 * Once the PaperPlatform passes a certain X position it destroys itself
 */
UCLASS()
class ENDLESSRUNNER_API APaperPlatform : public APaperSpriteActor
{
	GENERATED_BODY()
    virtual void BeginPlay() override;
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    
public:
    APaperPlatform();
    
    
private:
    UPROPERTY(EditAnywhere)
    float platformSpeed; // Speed of platform
    
    // Platform's current location
    FVector platformLocation;
protected:
    // The sprite to attach
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sprites)
    class UPaperSprite* PaperSprite;
};
