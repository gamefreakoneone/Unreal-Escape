// Copyright this! 8======D~~


#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab(){
	UE_LOG(LogTemp, Warning, TEXT("Grabber Press"));
}

void UGrabber::Release(){
	UE_LOG(LogTemp, Warning, TEXT("Grabber Release"));
}

void UGrabber::FindPhysicsHandle(){
	// Checking for Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); // Returns the physics handle of the object having Grabber component
	if(PhysicsHandle){
		// Physics Handle is found
	}else{
		UE_LOG(LogTemp, Error, TEXT("No physics handle found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if(InputComponent){
		// UE_LOG(LogTemp, Warning, TEXT("Input componenet found %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); // this here refers to the class initiating this peice of code
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}else{
		UE_LOG(LogTemp, Error, TEXT("No input componenet found on %s"), *GetOwner()->GetName());
	}
}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
	// UE_LOG(LogTemp, Warning, TEXT("Grabber online!"));
	// ...
	// // Checking for Physics Handle
	// PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); // Returns the physics handle of the object having Grabber component
	// if(PhysicsHandle){
	// 	// Physics Handle is found
	// }else{
	// 	UE_LOG(LogTemp, Error, TEXT("No physics handle found on %s"), *GetOwner()->GetName());
	// }

	// InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// if(InputComponent){
	// 	// UE_LOG(LogTemp, Warning, TEXT("Input componenet found %s"), *GetOwner()->GetName());
	// 	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); // this here refers to the class initiating this peice of code
	// 	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	// }else{
	// 	UE_LOG(LogTemp, Error, TEXT("No input componenet found on %s"), *GetOwner()->GetName());
	// }
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetFirstPhysicsBodyInReach();
	// Get player viewpoint
	// FVector PlayerViewPointLocation;
	// FRotator PlayerViewPointRotation;
	// GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
	// // UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString()); // Displays the location of the dude while dereferencing shit
	// // ...

	// // Visualizing the reach of the player
	// FVector LineTraceEnd = PlayerViewPointLocation+(PlayerViewPointRotation.Vector() * Reach); // Converting Rotator to Vector makes it a unit vector
	// DrawDebugLine(
	// 	GetWorld(),
	// 	PlayerViewPointLocation,
	// 	LineTraceEnd,
	// 	FColor(14,248,255),
	// 	false,
	// 	0.f,
	// 	0,
	// 	5.f
	// );

	// FHitResult Hit;
	// // Ray cast out to a certain distance
	// FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());

	// GetWorld()->LineTraceSingleByObjectType(
	// 	OUT Hit,
	// 	PlayerViewPointLocation,
	// 	LineTraceEnd,
	// 	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	// 	TraceParams
	// );

	// // See what hits
	// AActor * ActorHit= Hit.GetActor();

	// if (ActorHit)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"),*(ActorHit->GetName())); //FString has to be dereferenced.
	// }
	
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{
	// Get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString()); // Displays the location of the dude while dereferencing shit
	// ...

	// Visualizing the reach of the player
	FVector LineTraceEnd = PlayerViewPointLocation+(PlayerViewPointRotation.Vector() * Reach); // Converting Rotator to Vector makes it a unit vector
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(14,248,255),
		false,
		0.f,
		0,
		5.f
	);

	FHitResult Hit;
	// Ray cast out to a certain distance
	FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what hits
	AActor * ActorHit= Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"),*(ActorHit->GetName())); //FString has to be dereferenced.
	}
	
	return Hit;
}
