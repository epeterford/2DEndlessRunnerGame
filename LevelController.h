// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyPlatform.h"
#include "LevelController.generated.h"

/*
LevelController spawns platforms when needed and determines how many obstacles(from 0-3) to spawn on each platform
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENDLESSRUNNER_API ALevelController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
private:
    // Obstacles Z position
    const float OBSTACLE_Z_POS = 212.0f;
    
    // Default spawn rotation
    FRotator defaultRot = FRotator(0,0,0);
    
    // Platform spawn location
    FVector platLoc = FVector(1841,0,77);
    
    /// Obstacles spawn locations
    FVector obstacleLoc = FVector(1824, 0, OBSTACLE_Z_POS);
    FVector obstacle2Loc = FVector(1865, 0, OBSTACLE_Z_POS);
    FVector obstacle3Loc = FVector(1906, 0, OBSTACLE_Z_POS);
 
    /// Spawn functions
    void SpawnPlatform();
    void SpawnObstacle1();
    void SpawnObstacle2();
    void SpawnObstacle3();
    
    // Obstacle spawn probablity 
    void ChanceToSpawnObstacles();
};
