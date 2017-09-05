// Copyright Rameez Qurashi 2017

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FRotator PlayerRotation;
	FVector PlayerLocation;
	FVector GrabberEndPoint;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	GrabberEndPoint = PlayerLocation + (PlayerRotation.Vector() * Reach);

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), 
		*(PlayerLocation.ToString()), *(PlayerRotation.ToString()));

	DrawDebugLine(GetWorld(), PlayerLocation, GrabberEndPoint,
		FColor(255, 0, 0), false, -1.0, 0, 10.0);
}

