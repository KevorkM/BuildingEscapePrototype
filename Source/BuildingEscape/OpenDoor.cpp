// Copyright KMG 


#include "OpenDoor.h"
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
		// Physics handle is found
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"),
			*GetOwner()->GetName());
		
	}


}
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume.	
	if (GetTotalMassOfActorOnPlate()> TriggerMass) {//TODO make into a patameter
		OnOpen.Broadcast();
	}
	else {
		OnClose.Broadcast();
	}
	}

float UOpenDoor::GetTotalMassOfActorOnPlate(){
	float TotalMass = 0.f;

	//Find all the overlapping actors
	TArray<AActor*>OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
	}

	return TotalMass;
}
