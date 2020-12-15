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
	OpenAngle+=InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a PressurePlate"), *GetOwner()->GetName());	// This informs us if the pressure plate is set or not.
	}
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); // This sets the default player. GetFirstPlayerController gets the user first
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)){
		OpenDoor(DeltaTime);
		DoorLastOpened=GetWorld()->GetTimeSeconds();
	}else
	{
		if(GetWorld()->GetTimeSeconds()-DoorLastOpened>DoorCloseDelay){
			CloseDoor(DeltaTime);
		}
		
	}
	


	// UE_LOG(LogTemp, Warning TEXT(%s), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw);

	// FRotator OpenDoor(0.f,OpenAngle,0.f);
	// OpenDoor.Yaw=FMath::Lerp(CurrentYaw,OpenAngle,0.02);
	// GetOwner()->SetActorRotation(OpenDoor);


	// CurrentRotation.Yaw=90.f;

	// FRotator OpenDoor(0.f ,90.f,0.f );

	// GetOwner()->SetActorRotation(OpenDoor);	// ...
}

void UOpenDoor::OpenDoor(float DeltaTime){
	
	CurrentYaw= FMath::Lerp(CurrentYaw,OpenAngle,DeltaTime*DoorOpenSpeed); // Dont worry about framerate

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime){

	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime*DoorCloseSpeed);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation); 
}