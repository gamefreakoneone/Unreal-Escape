// Copyright this! 8======D~~


#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw=InitialYaw+90;
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentYaw= FMath::Lerp(CurrentYaw,TargetYaw,0.02);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	// UE_LOG(LogTemp, Warning TEXT(%s), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);

	// FRotator OpenDoor(0.f,TargetYaw,0.f);
	// OpenDoor.Yaw=FMath::Lerp(CurrentYaw,TargetYaw,0.02);
	// GetOwner()->SetActorRotation(OpenDoor);


	// CurrentRotation.Yaw=90.f;

	// FRotator OpenDoor(0.f ,90.f,0.f );

	// GetOwner()->SetActorRotation(OpenDoor);	// ...
}

