// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunner.h"
#include "PaperPlatform.h"
#include "EndlessRunnerGameMode.h"



APaperPlatform::APaperPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    platformSpeed = 2.0f;
    GetRenderComponent()->SetMobility(EComponentMobility::Movable);
    // Setup the assets
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UPaperSprite> PlatformSpriteAsset;
        FConstructorStatics()
        : PlatformSpriteAsset(TEXT("/Game/2DSideScroller/Sprites/Ledge.Ledge"))
        {
        }
    };
    
    static FConstructorStatics ConstructorStatics;
    
    PaperSprite = ConstructorStatics.PlatformSpriteAsset.Get();
    
    GetRenderComponent()->SetSprite(PaperSprite);
    
}

void APaperPlatform::BeginPlay()
{
    
    Super::BeginPlay();
    SetActorLocation(FVector(GetActorLocation().X, 0, 77), true);
    
}
// Called every frame
void APaperPlatform::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
   // Cast to Game Mode
    AEndlessRunnerGameMode* const MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();
   
    if(MyGameMode->bGameStarted) // If Game is started
    {
        /// Move's platform
        platformLocation = GetActorLocation();
        platformLocation.X -= MyGameMode->levelSpeed;
        SetActorLocation(platformLocation,false);
    
        if(platformLocation.X<-2000)
        {
            Destroy();
        }
    }
}