// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallDoorEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor();
	void CloseDoor();

	UPROPERTY(BlueprintAssignable)
		FCallDoorEvent HoldTheDoor;

	UPROPERTY(BlueprintAssignable)
		FCallDoorEvent CloseTheDoor;

private:

	UPROPERTY(EditAnywhere)
		float DelayToCloseDoor = 0.45f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float WeightToTriggeresurePlate = 20.f;


	float GetTotalWeightOnPresurePlate();
	
	//	UPROPERTY(VisibleAnywhere)
	
	//AActor* ActorThatOpens;		//Remember pawn inherits from actor
	float LastDoorOpenTime = 0.f;
};
