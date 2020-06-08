// Fill out your copyright notice in the Description page of Project Settings.


#include "ThermalObject.h"

// Sets default values for this component's properties
UThermalObject::UThermalObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UThermalObject::BeginPlay()
{
	Super::BeginPlay();

	// ...TODO TIGER
	USceneComponent* RootObject = GetOwner()->GetRootComponent();

	TArray<USceneComponent*> childSceneObjects;

	RootObject->GetChildrenComponents(true, childSceneObjects);

	TArray<UMeshComponent*> meshes;

	for (int i = 0; i < childSceneObjects.Num(); i++)
	{
		TArray<UMeshComponent*> currentMeshes;

		childSceneObjects[i]->GetOwner()->GetComponents<UMeshComponent>(currentMeshes, true);

		meshes.Append(currentMeshes);
	}

	InitializeMaterial(meshes);

	
}

void UThermalObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}

void UThermalObject::SetMaterialVisualType(int visualType)
{
	int heatVision = 0;

	if (visualType == 1)
		heatVision = 1;

	//TS_LOG("Setting All Material from dynamic material buffer, length: %d", dynamicMaterialBuffer.Num());

	for (int i = 0; i < dynamicMaterialBuffer.Num(); i++)
	{
		// go through all dynamic material buffer
		if (dynamicMaterialBuffer[i] != nullptr)
		{
			float OutParameterValue = 0;

			if ((dynamicMaterialBuffer[i])->GetScalarParameterValue(TEXT("HeatToggle"), OutParameterValue, false))
			{
				//TS_LOGD("Heat Toggle Modification");
				(dynamicMaterialBuffer[i])->SetScalarParameterValue(TEXT("HeatToggle"), heatVision);
			}
		}
	}

	AActor* owner = GetOwner();

	if (!owner)
		return;

	TArray<UMeshComponent*> CurrentMeshComponents;

	owner->GetComponents<UMeshComponent>(CurrentMeshComponents, true);

	for (int i = 0; i < CurrentMeshComponents.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("actor name: %s"), *(owner->GetName()));

		if (heatVision == 1)
			CurrentMeshComponents[i]->SetRenderCustomDepth(true);
		else
			CurrentMeshComponents[i]->SetRenderCustomDepth(false);
		
	}
}


// Called every frame
void UThermalObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UThermalObject::InitializeMaterial(TArray<UMeshComponent*> myArray)
{

	UMeshComponent* currentMeshComponent = nullptr;

	//TS_LOG("Current Static Mesh Array Num: %d, Getting all Materials from Static Mesh", myArray.Num());


	for (int i = 0; i < myArray.Num(); i++)
	{
		currentMeshComponent = myArray[i];


		//TS_LOG("modifying static mesh name %d", i);

		TArray<UMaterialInterface*> currentMaterials = currentMeshComponent->GetMaterials();

		for (int j = 0; j < currentMaterials.Num(); j++)
		{
			// ok our material buffer does not contain current material
			// add to material buffer
			UMaterialInstanceDynamic* currentDynamicMat = currentMeshComponent->CreateAndSetMaterialInstanceDynamic(j);

			if (!dynamicMaterialBuffer.Contains(currentDynamicMat))
				dynamicMaterialBuffer.Add(currentDynamicMat);
		}
	}
}

