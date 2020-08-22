// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// FString Log=TEXT("Hello");
	// FString* PtrLog=&Log;

	// Log.Len();
	// (*PtrLog).Len();
	// PtrLog->Len();

	// UE_LOG(LogTemp, Warning, TEXT("%s") , **PtrLog);

	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("The abject name is %s"), *GetOwner()->GetName());
	FString ObjectPosition=GetOwner()->GetActorLocation().ToString();//Gives the textual representaion of the vector
	UE_LOG(LogTemp, Warning, TEXT("%s position in the world.%s"),*ObjectName,*ObjectPosition);
}

// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}