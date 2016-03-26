// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();


	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	//GetOwner()->SetActorRotation(FRotator(0.f, 70.f, 0.f));

	/***************************************************/
	/*********** Lo mismo pero con variables ***********/
	/***************************************************/
	//AActor* Owner{ GetOwner()};
	//FRotator NewRotation{ 0.f ,70.f ,0.f };
	//Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::OpenDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume if the actorthatopens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();		//open the door
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() >= (LastDoorOpenTime + DelayToCloseDoor))		//check if is time to close the door
	{
		CloseDoor();
	}
}


