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
	// Set rotation
	Owner->SetActorRotation(FRotator(0.0, OpenAngle, 0.0));

	OpenDoorTime = GetWorld()->GetTimeSeconds();
}

void UOpenDoor::CloseDoor()
{
	// Set rotation
	Owner->SetActorRotation(FRotator(0.0, 0.0, 0.0));
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
}

float UOpenDoor::GetTotalMassOfObjectsOnPlate()
{
	float TotalMass = 0.0f;

	//
	TArray <AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (auto& OverlappingActor : OverlappingActors)
	{
		TotalMass += OverlappingActor->GetRootPrimitiveComponent()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Actor(s) on Plate: %s"), *(OverlappingActor->GetName()));
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
		UE_LOG(LogTemp, Warning, TEXT("Weight on Plate: %f"), GetTotalMassOfObjectsOnPlate());
	}
    else if ((OpenDoorTime > 0.0) && (GetWorld()->GetTimeSeconds() > (OpenDoorTime + DelayTime)))
		CloseDoor();
}

