// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPawnController.h"
#include "EnhancedInputSubsystems.h"

AFirstPawnController::AFirstPawnController()
{
	
}

void AFirstPawnController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	Subsystem->AddMappingContext(InputMappingContext, 0);
}
