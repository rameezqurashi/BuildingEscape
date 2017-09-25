// Copyright Rameez Qurashi 2017

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include <assert.h>

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
	FindPhysicsHandle();
	BindGrabberKeys();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	assert(PhysicsHandle);
}

void UGrabber::BindGrabberKeys()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	assert(InputComponent);

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab()
{
	FHitResult Hit;
	Hit = GetNearestPhysicsBodyInReach();

	auto ComponentToGrab = Hit.GetComponent();

	if (Hit.Actor != NULL)
	{
		assert(PhysicsHandle);
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}
}

void UGrabber::Release()
{
	assert(PhysicsHandle);
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetNearestPhysicsBodyInReach()
{
	FRotator PlayerRotation;
	FVector PlayerLocation;
	FVector GrabberEndPoint;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	GrabberEndPoint = PlayerLocation + (PlayerRotation.Vector() * Reach);

	/// Get the object that our line is touching
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(Hit,
		PlayerLocation,
		GrabberEndPoint,
		ECollisionChannel::ECC_PhysicsBody,
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));

	return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Set location of grabbed component
	if (PhysicsHandle->GrabbedComponent != NULL)
	{
		FRotator PlayerRotation;
		FVector PlayerLocation;
		FVector GrabberEndPoint;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
		GrabberEndPoint = PlayerLocation + (PlayerRotation.Vector() * Reach);

		PhysicsHandle->SetTargetLocation(PlayerLocation);
	}
}