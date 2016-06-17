// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunner.h"
#include "MovingPlatform.h"
#include "EndlessRunnerGameMode.h"

// Sets default values for this component's properties
UMovingPlatform::UMovingPlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
    
}


// Called every frame
void UMovingPlatform::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // Cast to Game Mode
    AEndlessRunnerGameMode* const MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();
    
    if(MyGameMode->bGameStarted) // If Game is started
    {
        /// Move's platform
        platformLocation = GetOwner()->GetActorLocation();
        platformLocation.X -= platformSpeed;
        GetOwner()->SetActorLocation(platformLocation,false);
    
    }
}

