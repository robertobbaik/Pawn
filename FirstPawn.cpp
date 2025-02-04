// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPawn.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "FirstPawnController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AFirstPawn::AFirstPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AFirstPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFirstPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFirstPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	AFirstPawnController* PlayerController = Cast<AFirstPawnController>(GetController());

	EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AFirstPawn::Move);
	EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AFirstPawn::Look);
}

void AFirstPawn::Move(const FInputActionValue& value)
{
	FVector MoveDir = value.Get<FVector>();

	if (MoveDir.IsNearlyZero())
	{
		return;
	}

	MoveDir = MoveDir.GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MoveDir.ToString());
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(600.0f * DeltaTime * FVector(MoveDir.X, MoveDir.Y, 0));
}

void AFirstPawn::Look(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *value.ToString());
	FVector2D LookDirection = value.Get<FVector2D>();

	if (LookDirection.IsNearlyZero())
	{
		return;
	}

	SpringArm->SetRelativeRotation(FRotator(LookDirection.Y + SpringArm->GetDesiredRotation().Pitch,0, 0));
	SetActorRotation(FRotator(0, LookDirection.X + GetActorRotation().Yaw, 0));
}
