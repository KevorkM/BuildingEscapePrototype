// Copyright KMG 

#pragma once

#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	// how far ahead of the player can we reach in cm
	float Reach = 100.f;
		
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Ray-Cast And grab what is in reach
	void Grab();
	
	// Called when grab is released
	void Release();

	// Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) input component
	void SetupInputComponent();

	//Return hit first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	
	// returns current Start of reach line
	FVector GetReachLineStart();
	// returns current end of reach line
	FVector GetReachLineEnd();
};

