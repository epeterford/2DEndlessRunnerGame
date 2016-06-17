// Fill out your copyright notice in the Description page of Project Settings.

#include "EndlessRunner.h"
#include "MySaveGame.h"


UMySaveGame::UMySaveGame()
{
    SaveSlotName = TEXT("HighScoreSlot");
    UserIndex = 0;
}

