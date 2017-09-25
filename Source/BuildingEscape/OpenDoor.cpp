// Copyright Rameez Qurashi 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include <assert.h>

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::OpenDoor()
{
	// Set rotation
	assert(Owner);
	Owner->SetActorRotation(FRotator(0.0, OpenAngle, 0.0));

	OpenDoorTime = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	// Set rotation
	assert(Owner);
	Owner->SetActorRotation(FRotator(0.0, 0.0, 0.0));
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	assert(Owner);
}

float UOpenDoor::GetTotalMassOfObjectsOnPlate()
{
	float TotalMass = 0.0f;

	//
	TArray <AActor*> OverlappingActors;
	if (PressurePlate)
		PressurePlate->GetOverlappingActors(OverlappingActors);

	for (auto& OverlappingActor : OverlappingActors)
	{
		TotalMass += OverlappingActor->GetRootPrimitiveComponent()->GetMass();
	}

	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfObjectsOnPlate() >= WeightToOpenDoor)
	{
		OpenDoor();
	}
    else if ((OpenDoorTime > 0.0) && (GetWorld()->GetTimeSeconds() > (OpenDoorTime + DelayTime)))
		CloseDoor();
}

