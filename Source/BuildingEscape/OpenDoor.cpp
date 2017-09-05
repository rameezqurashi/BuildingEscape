// Copyright Rameez Qurashi 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		OpenDoor();

	if ((OpenDoorTime > 0.0) && (GetWorld()->GetTimeSeconds() > (OpenDoorTime + DelayTime)))
		CloseDoor();
}

