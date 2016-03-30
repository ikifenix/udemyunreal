// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
	FString ObjectName{ GetOwner()->GetName() };
	//	FString ObjectPos{ GetOwner()->GetActorLocation().ToString() };
	FString ObjectPos{ GetOwner()->GetTransform().GetLocation().ToString() };
	UE_LOG(LogTemp, Warning, TEXT("%s is at position: %s reporting for dutty"), *ObjectName, *ObjectPos);
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0 , 0),
		false,
		0.f,
		0.f,
		10.f
	);
	
	/*UE_LOG(LogTemp, Warning, TEXT("Position: %s , Direction: %s "), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointLocation.ToString()
	);*/
	

}

