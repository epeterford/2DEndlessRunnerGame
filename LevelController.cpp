// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunner.h"
#include "LevelController.h"
#include "PaperPlatform.h"
#include "Obstacle_01.h"
#include <stdlib.h>
#include <time.h>

#define OUT

// Sets default values
ALevelController::ALevelController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();
    
}

// Called every frame
void ALevelController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    // Get actors currently overlapping platform spawn box
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OUT OverlappingActors);
    
    // If no actors are currently overlapping platform spawn box
    if(OverlappingActors.Num()<1)
    {
        SpawnPlatform();
        ChanceToSpawnObstacles();
    }
}

void ALevelController::SpawnPlatform()
{
    /// Spawn New Platform
    APaperPlatform* movingPlatform = GetWorld()->SpawnActor<APaperPlatform>(APaperPlatform::StaticClass(), platLoc, defaultRot);
    
}

void ALevelController::ChanceToSpawnObstacles()
{
    // Initialize random seed
    srand(time(NULL));
    
    // Generate random number between 1 and 100
    int32 randNum;
    randNum = rand() % 100;
    
    /// Spawn obstacles based on probability
    if(randNum>=90)
    {
        SpawnObstacle1();
        SpawnObstacle2();
        SpawnObstacle3();
    }
    else if(randNum>=60)
    {
        SpawnObstacle1();
        SpawnObstacle2();
    }
    else if(randNum>=25)
    {
        SpawnObstacle1();
    }
}

void ALevelController::SpawnObstacle1()
{
    AObstacle_01* obstacle1 = GetWorld()->SpawnActor<AObstacle_01>(AObstacle_01::StaticClass(), obstacleLoc, defaultRot);
}

void ALevelController::SpawnObstacle2()
{
     AObstacle_01* obstacle2 = GetWorld()->SpawnActor<AObstacle_01>(AObstacle_01::StaticClass(), obstacle2Loc, defaultRot);
}
void ALevelController::SpawnObstacle3()
{
    AObstacle_01* obstacle3 = GetWorld()->SpawnActor<AObstacle_01>(AObstacle_01::StaticClass(), obstacle3Loc, defaultRot);
}
