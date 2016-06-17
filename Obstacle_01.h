// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "Obstacle_01.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AObstacle_01 : public APaperSpriteActor
{
    GENERATED_BODY()
    
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
	
public:
    AObstacle_01();
    
    // Box trigger component
    UPROPERTY(VisibleAnywhere, Category = "Switch Components")
    class UBoxComponent* Trigger;
    
private:
    // Obstacle Current Location
    FVector obstacleLocation;
    
    
protected:
    // The sprite to attach
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sprites)
    class UPaperSprite* PaperSprite;
};
