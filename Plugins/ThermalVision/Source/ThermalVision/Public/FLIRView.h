// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Components/PostProcessComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Light.h"
#include "EngineUtils.h"

#include "FLIRView.generated.h"

UENUM(BlueprintType)
enum class DISPLAY_TYPE : uint8
{
	INFERRAD UMETA(DisplayName = "Inferrad"),
	THERMAL UMETA(DisplayName = "Thermal"),
	SAR UMETA(DisplayName = "SAR")
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THERMALVISION_API UFLIRView : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UFLIRView();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		struct FPostProcessSettings PostProcessFLIR;

	UPROPERTY()
		struct FPostProcessSettings DefaultPostProcessSetting;

	UPROPERTY()
		UMaterialInterface* ThermalPP = nullptr;

	UPROPERTY()
		UMaterialInterface* InferradPP = nullptr;

	UPROPERTY()
		UMaterialInterface* SARPP = nullptr;

	UPROPERTY()
		UMaterialInstanceDynamic* CurrentMatInstanceDyn = nullptr;

	UPROPERTY()
		UCameraComponent* Camera;

	UPROPERTY()
		TArray<ALight*> CachedLights;

	UFUNCTION(BlueprintCallable)
		void InitializeFLIRVision(FPostProcessSettings PPSetting, UCameraComponent* CameraComponent, UMaterialInterface* ThermalPostProcess, UMaterialInterface* InferradPostProcess, UMaterialInterface* SARPostProcess, TArray<ALight*> Lights);

	UFUNCTION(BlueprintCallable)
		void TurnOnFLIRVision(TEnumAsByte<DISPLAY_TYPE> displayType);

	UFUNCTION(BlueprintCallable)
		void TurnOffFLIRVision();

	void SetAllThermalObject(int toggleType);

	template<typename T> void FindAllObjects(TArray<T*>& Out)
	{
		for (TObjectIterator<T> It; It; ++It)
		{
			Out.Add(*It);
		}
	}
};
