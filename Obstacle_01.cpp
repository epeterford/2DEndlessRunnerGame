// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunner.h"
#include "Obstacle_01.h"
#include "EndlessRunnerGameMode.h"


AObstacle_01::AObstacle_01()
{
    PrimaryActorTick.bCanEverTick = true;
    
    // Set obstacle to moveable
    GetRenderComponent()->SetMobility(EComponentMobility::Movable);

    //Setup the assets
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UPaperSprite> PlatformSpriteAsset;
        FConstructorStatics()
        : PlatformSpriteAsset(TEXT("/Game/Sprites/Obstacles/SpikeObstacle.SpikeObstacle"))
        {
        }
    };
    
    static FConstructorStatics ConstructorStatics;
    
    // Setup and attach Box trigger component to obstacle
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    Trigger->SetBoxExtent(FVector(23.0f, 32.0f, 45.0f));
    Trigger->AttachParent = RootComponent;
    
    // Set sprite
    PaperSprite = ConstructorStatics.PlatformSpriteAsset.Get();
    GetRenderComponent()->SetSprite(PaperSprite);
    
    GetRenderComponent()->SetCollisionProfileName(TEXT("NoCollision"));
    
    this->Tags.Add(FName("Obstacle"));
}

void AObstacle_01::BeginPlay()
{
    
    Super::BeginPlay();
    
    //Position correctly on spawn
    SetActorLocation(FVector(GetActorLocation().X, 0, 214), true);
}

void AObstacle_01::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    // Cast to Game Mode
    AEndlessRunnerGameMode* const MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();
    
    if(MyGameMode->bGameStarted) // If Game is started
    {
        /// Move's obstacle towards character
        obstacleLocation = GetActorLocation();
        obstacleLocation.X -= MyGameMode->levelSpeed;
        SetActorLocation(obstacleLocation,false);
        
        /// Destroy obstacle if past character and out of view
        if(obstacleLocation.X<-2000)
        {
            Destroy();
        }
        
    }
}