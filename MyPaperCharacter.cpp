// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunner.h"
#include "MyPaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "MySaveGame.h"
#include "EndlessRunnerGameMode.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);
//////////////////////////////////////////////////////////////////////////
// AMyPaperCharacter

AMyPaperCharacter::AMyPaperCharacter()
{
    // Setup the assets
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset;
        ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
        FConstructorStatics()
        : RunningAnimationAsset(TEXT("/Game/Sprites/Flipbooks/Rogue_Running.Rogue_Running"))
        , IdleAnimationAsset(TEXT("/Game/Sprites/Flipbooks/Rogue_Idle.Rogue_Idle"))
        {
        }
    };
    
    static FConstructorStatics ConstructorStatics;
    
    /// Set Trigger capsule component
    Trigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger"));
    Trigger->SetCapsuleHalfHeight(55.0f);
    Trigger->SetCapsuleRadius(28.0f);
    Trigger->AttachParent = RootComponent;
    
    // Delegate Trigger capsule component to OnOverlapBegin function
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyPaperCharacter::OnOverlapBegin);
    
    /// Set Animation assets
    RunningAnimation = ConstructorStatics.RunningAnimationAsset.Get();
    IdleAnimation = ConstructorStatics.IdleAnimationAsset.Get();
    GetSprite()->SetFlipbook(IdleAnimation);
    
    /// Use only Yaw from the controller and ignore the rest of the rotation.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;
    
    /// Set the size of collision capsule.
    GetCapsuleComponent()->SetCapsuleHalfHeight(55.0f);
    GetCapsuleComponent()->SetCapsuleRadius(28.0f);
    
    /// Configure character movement
    GetCharacterMovement()->GravityScale = 3.0f;
    GetCharacterMovement()->AirControl = 0.80f;
    GetCharacterMovement()->JumpZVelocity = 1000.0f;
    GetCharacterMovement()->GroundFriction = 3.0f;
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->MaxFlySpeed = 600.0f;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    // Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
    GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
  
    // Scale Sprite
    GetSprite()->RelativeScale3D = FVector(4.0f, 1.0f, 4.0f);
}

//////////////////////////////////////////////////////////////////////////
// Animation

void AMyPaperCharacter::UpdateAnimation()
{
    // Cast to Game Mode
    AEndlessRunnerGameMode* MyGameMode = MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();
    
    /// Checks if game is started and sets sprite animation accordingly
    UPaperFlipbook* DesiredAnimation = (MyGameMode->bGameStarted) ? RunningAnimation : IdleAnimation;
    if( GetSprite()->GetFlipbook() != DesiredAnimation 	)
    {
        GetSprite()->SetFlipbook(DesiredAnimation);
    }
}

// Called every frame
void AMyPaperCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    // Locks player's X position to 0
    SetActorLocation(FVector(0, GetActorLocation().Y, GetActorLocation().Z));
    
    UpdateAnimation();
    
}

// Player input setup
void AMyPaperCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    // Cast to Game Mode
    AEndlessRunnerGameMode* MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();

    // If game hasn't started yet
    if(! MyGameMode->bGameStarted)
    {
        // Setup input for Enter key to start the game
        InputComponent->BindAction("StartGame", IE_Pressed, this, &AMyPaperCharacter::StartGame);
    }
    else // otherwise
    {
        ///Setup input for Jumping
        InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
        InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    }
}

void AMyPaperCharacter::StartGame()
{
    // Cast to Game Mode
    AEndlessRunnerGameMode* MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();
    
    // Starts game
    MyGameMode->bGameStarted=true;
    
    SetupPlayerInputComponent(InputComponent);
    
    // Calls Broadcast event in BPs
    StartGameEvent.Broadcast();
}

/// Handle overlap triggers for character
void AMyPaperCharacter::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Cast to Game Mode
    AEndlessRunnerGameMode* MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();
    
    if(MyGameMode->bGameStarted)
    {
        if(OtherActor && (OtherActor!=this) && OtherComp &&(OtherActor->ActorHasTag("Obstacle"))) // if character overlaps an actor tagged 'Obstacle'
        {
            GameOver(); // Call Game over
        }
    }
}

void AMyPaperCharacter::GameOver()
{
    // Cast to Game Mode
    AEndlessRunnerGameMode* MyGameMode = GetWorld()->GetAuthGameMode<AEndlessRunnerGameMode>();
    
   // Stops game
    MyGameMode->bGameStarted=false;
    
    /// Get Current High Score
    int32 CurrentHighScore;
    UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    
    // If there is a current Save Game Slot
    if(UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex))
       {
           // Load High Score from Slot
           LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
           CurrentHighScore = LoadGameInstance->HighScore;
       }
    else // otherwise
    {
        // Set default High Score to 0
        CurrentHighScore = 0;
    }
    // If player's score is higher than the Current High Score
    if(MyGameMode->levelScore > CurrentHighScore)
    {
        /// Save High Score
        UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
        SaveGameInstance->HighScore = MyGameMode->levelScore;
        SaveGameInstance->bIsNewHighScore = true;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
    }
    else
    {
        // Re-save Current High Score
        UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
        SaveGameInstance->HighScore = CurrentHighScore;
        SaveGameInstance->bIsNewHighScore = false;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
    }
    // Broadcast Game Over to HUD BP
    GameOverEvent.Broadcast();
    
    // Clear player input
    InputComponent->ClearActionBindings();
    
}
