// Copyright Rameez Qurashi 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = NULL;
	UInputComponent* InputComponent = NULL;

	// Find attached physics handle
	void FindPhysicsHandle();

	// Bind grabber keys to attached input component
	void BindGrabberKeys();

	// Grab object within reach
	void Grab();
	
	// Release grabbed object
	void Release();

	// Return hit for physics body within reach
	const FHitResult GetNearestPhysicsBodyInReach();
};
