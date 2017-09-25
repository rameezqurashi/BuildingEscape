// Copyright Rameez Qurashi 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	void OpenDoor();

	void CloseDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// The owner of this door
	AActor* Owner;

	// Door open angle
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.0;

	// Pressure plate to open door
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float WeightToOpenDoor;

	UPROPERTY(EditAnywhere)
	float DelayTime = 1.0;

	float OpenDoorTime = -1.0;

	float GetTotalMassOfObjectsOnPlate();
};
