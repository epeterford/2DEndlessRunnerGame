// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "MyPaperCharacter.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartGameEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNER_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
    
    /** Called every frame */
    virtual void Tick(float DeltaSeconds) override;
    
public:
    // Constructor
    AMyPaperCharacter();
    
    UPROPERTY(BlueprintAssignable)
    FStartGameEvent StartGameEvent;
    
    UPROPERTY(BlueprintAssignable)
    FGameOverEvent GameOverEvent;
    
    // Called when something enters the capsule trigger component
    UFUNCTION()
    void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    // Capsule trigger component
    UPROPERTY(VisibleAnywhere, Category = "Trigger Components")
    class UCapsuleComponent* Trigger;
    
protected:
    // The animation to play while running
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
    class UPaperFlipbook* RunningAnimation;
    
    // The animation to play while idle (standing still)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
    class UPaperFlipbook* IdleAnimation;
    
    /** Called to choose the correct animation to play based on the 
        character's movement state */
    void UpdateAnimation();
    
    
    // Starts the game
    void StartGame();
    
    // On Game Over
    void GameOver();
    
    // Setup player input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
