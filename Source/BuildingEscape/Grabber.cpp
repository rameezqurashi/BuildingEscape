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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have an associated physics handle!"), *(GetOwner()->GetName()));
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a player input component!"), *(GetOwner()->GetName()));
	}

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);

	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
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

	/// Get player's location and rotation
//	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
//		*(PlayerLocation.ToString()), *(PlayerRotation.ToString()));

	/// Draw red debug line
	DrawDebugLine(GetWorld(), PlayerLocation, GrabberEndPoint,
		FColor(255, 0, 0), false, -1.0, 0, 10.0);

	/// Get the object that our line is touching
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(Hit,
		PlayerLocation,
		GrabberEndPoint,
		ECollisionChannel::ECC_PhysicsBody,
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	
	if (Hit.Actor != NULL)
		UE_LOG(LogTemp, Warning, TEXT("Currently hitting %s"), *(Hit.GetActor()->GetName()));
}