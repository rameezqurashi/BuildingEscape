// Copyright Rameez Qurashi 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::OpenDoor()
{
	// Open door request handled in Blueprint
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	// Close door request handled in Blueprint
	OnCloseRequest.Broadcast();
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	check(Owner);
}

float UOpenDoor::GetTotalMassOfObjectsOnPlate()
{
	float TotalMass = 0.0f;

	//
	TArray <AActor*> OverlappingActors;
	check(PressurePlate);
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
    else
		CloseDoor();
}

