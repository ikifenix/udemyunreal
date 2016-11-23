// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();		//player character
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
	if (GetTotalWeightOnPresurePlate() > WeightToTriggeresurePlate)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();		//save the current time in seconds
	}
	if (GetWorld()->GetTimeSeconds() >= (LastDoorOpenTime + DelayToCloseDoor))		//check if is time to close the door
	{
		CloseDoor();
	}
}


float UOpenDoor::GetTotalWeightOnPresurePlate()
{
	TArray<AActor*> MeshesOnPresurePlate;
	float ActualWeight = 0.f;
//	FString ObjectName;

	PressurePlate->GetOverlappingActors(MeshesOnPresurePlate);

	for (const auto& MeshesOverlaping : MeshesOnPresurePlate)
	{
//		ObjectName = MeshesOverlaping->GetName();
		ActualWeight += MeshesOverlaping->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

//	ObjectName = FString::SanitizeFloat(ActualWeight);
//	UE_LOG(LogTemp, Warning, TEXT("%s Total mass"), *ObjectName);

	return ActualWeight;
}



