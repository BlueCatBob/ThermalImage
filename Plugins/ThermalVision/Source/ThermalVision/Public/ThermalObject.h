// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Components//StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThermalObject.generated.h"

#define TS_LOG(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define TS_LOGD(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x)) );}

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERMALVISION_API UThermalObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThermalObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void InitializeMaterial(TArray<UMeshComponent*> myArray);

	UFUNCTION(BlueprintCallable)
		void SetMaterialVisualType(int visualType);

	// this holds material buffer for all added materials
	TArray<UMaterialInstanceDynamic*> dynamicMaterialBuffer;

	TArray<UMaterialInterface*> materialBuffer;
};
