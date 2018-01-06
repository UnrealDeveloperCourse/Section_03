// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
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
	// Helps define length of debug line
	float Reach = 100.f;

	void FindPhysicsHandleComponent();

	void SetupInputComponent();

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Get the first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Ray-cast and grab what is in reach
	void Grab();

	// Release the object
	void Release();

	// Returns current end of reach line
	const FVector GetReachLineEnd();

	// Returns current start of reach line
	const FVector GetReachLineStart();
};
