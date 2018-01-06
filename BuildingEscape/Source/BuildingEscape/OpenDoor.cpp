// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#define OUT


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
	Owner = GetOwner();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *Owner->GetName())
	}

	// Uncomment to output rotation
	/*
	FString ObjectRotation = Owner->GetActorRotation().ToString();
	FString ObjectName = Owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Rotation: %s\n"), *ObjectName, *ObjectRotation);
	*/
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{	
	float TotalMass = 0.f;

	// find all overlapping actors
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	// sum their masses
	for (const auto* OverlappingActor : OverlappingActors)
	{
		FString ActorName = OverlappingActor->GetName();
		TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		// log out what is on the pressure plate
		///UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate\n"), *ActorName)
	}

	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	} else {
		OnClose.Broadcast();
	}
}


