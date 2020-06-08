// Fill out your copyright notice in the Description page of Project Settings.


#include "FLIRView.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "ThermalObject.h"

// Sets default values for this component's properties
UFLIRView::UFLIRView()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFLIRView::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFLIRView::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFLIRView::InitializeFLIRVision(FPostProcessSettings PPSetting, UCameraComponent* CameraComponent, UMaterialInterface* ThermalPostProcess, UMaterialInterface* InferradPostProcess, UMaterialInterface* SARPostProcess, TArray<ALight*> Lights)
{
	PostProcessFLIR = PPSetting;
	Camera = CameraComponent;
	ThermalPP = ThermalPostProcess;
	InferradPP = InferradPostProcess;
	SARPP = SARPostProcess;

	DefaultPostProcessSetting = Camera->PostProcessSettings;

	CachedLights = Lights;
}

void UFLIRView::TurnOnFLIRVision(TEnumAsByte<DISPLAY_TYPE> displayType)
{

	switch (displayType)
	{
	case DISPLAY_TYPE::INFERRAD:

		PostProcessFLIR.bOverride_ColorSaturation = true;
		PostProcessFLIR.ColorSaturation.X = 1;
		PostProcessFLIR.ColorSaturation.Y = 1;
		PostProcessFLIR.ColorSaturation.Z = 1;

		PostProcessFLIR.bOverride_WhiteTemp = true;
		PostProcessFLIR.WhiteTemp = 4500;

		PostProcessFLIR.bOverride_ColorSaturationShadows = true;
		PostProcessFLIR.ColorSaturationShadows.X = 1;
		PostProcessFLIR.ColorSaturationShadows.Y = 1;
		PostProcessFLIR.ColorSaturationShadows.Z = 1;


		PostProcessFLIR.bOverride_ColorContrastShadows = true;
		PostProcessFLIR.ColorContrastShadows.X = 0.5;

		PostProcessFLIR.bOverride_VignetteIntensity = true;
		PostProcessFLIR.bOverride_GrainJitter = true;
		PostProcessFLIR.bOverride_GrainIntensity = true;

		PostProcessFLIR.VignetteIntensity = 1;
		PostProcessFLIR.GrainJitter = 1;
		PostProcessFLIR.GrainIntensity = 1;

		if (InferradPP)
		{
			CurrentMatInstanceDyn = UMaterialInstanceDynamic::Create(InferradPP, this);

			FWeightedBlendable WeightedBlendable;
			WeightedBlendable.Object = Cast<UObject>(CurrentMatInstanceDyn);
			WeightedBlendable.Weight = 1;

			PostProcessFLIR.WeightedBlendables.Array.Empty();
			PostProcessFLIR.WeightedBlendables.Array.Add(WeightedBlendable);
		}


		break;

	case DISPLAY_TYPE::THERMAL:

		PostProcessFLIR.bOverride_ColorSaturation = true;
		PostProcessFLIR.ColorSaturation.X = 1;
		PostProcessFLIR.ColorSaturation.Y = 1;
		PostProcessFLIR.ColorSaturation.Z = 1;

		PostProcessFLIR.bOverride_WhiteTemp = true;
		PostProcessFLIR.WhiteTemp = 4500;

		PostProcessFLIR.bOverride_ColorSaturationShadows = true;
		PostProcessFLIR.ColorSaturationShadows.X = 0.5;
		PostProcessFLIR.ColorSaturationShadows.Y = 0.5;
		PostProcessFLIR.ColorSaturationShadows.Z = 0.5;

		PostProcessFLIR.bOverride_ColorContrastShadows = true;
		PostProcessFLIR.ColorContrastShadows.X = 0.5;


		PostProcessFLIR.bOverride_VignetteIntensity = true;
		PostProcessFLIR.bOverride_GrainJitter = true;
		PostProcessFLIR.bOverride_GrainIntensity = true;

		PostProcessFLIR.VignetteIntensity = 0.2;
		PostProcessFLIR.GrainJitter = 0.9;
		PostProcessFLIR.GrainIntensity = 0.8;

		if (ThermalPP)
		{
			CurrentMatInstanceDyn = UMaterialInstanceDynamic::Create(ThermalPP, this);

			FWeightedBlendable WeightedBlendable;
			WeightedBlendable.Object = Cast<UObject>(CurrentMatInstanceDyn);
			WeightedBlendable.Weight = 1;

			PostProcessFLIR.WeightedBlendables.Array.Empty();
			PostProcessFLIR.WeightedBlendables.Array.Add(WeightedBlendable);
		}

		//GetWorld()->Exec(GetWorld(), TEXT("MyAwesomeConsoleCommand X Y Z"));
		break;

	case DISPLAY_TYPE::SAR:

		PostProcessFLIR.bOverride_ColorSaturation = true;
		PostProcessFLIR.ColorSaturation.X = 1;
		PostProcessFLIR.ColorSaturation.Y = 1;
		PostProcessFLIR.ColorSaturation.Z = 1;

		PostProcessFLIR.bOverride_WhiteTemp = true;
		PostProcessFLIR.WhiteTemp = 4500;

		PostProcessFLIR.bOverride_ColorSaturationShadows = true;
		PostProcessFLIR.ColorSaturationShadows.X = 1;
		PostProcessFLIR.ColorSaturationShadows.Y = 1;
		PostProcessFLIR.ColorSaturationShadows.Z = 1;


		PostProcessFLIR.bOverride_ColorContrastShadows = true;
		PostProcessFLIR.ColorContrastShadows.X = 0.5;

		PostProcessFLIR.bOverride_VignetteIntensity = true;
		PostProcessFLIR.bOverride_GrainJitter = true;
		PostProcessFLIR.bOverride_GrainIntensity = true;

		PostProcessFLIR.VignetteIntensity = 1;
		PostProcessFLIR.GrainJitter = 1;
		PostProcessFLIR.GrainIntensity = 1;

		if (SARPP)
		{
			CurrentMatInstanceDyn = UMaterialInstanceDynamic::Create(SARPP, this);

			FWeightedBlendable WeightedBlendable;
			WeightedBlendable.Object = Cast<UObject>(CurrentMatInstanceDyn);
			WeightedBlendable.Weight = 1;

			PostProcessFLIR.WeightedBlendables.Array.Empty();
			PostProcessFLIR.WeightedBlendables.Array.Add(WeightedBlendable);
		}


		break;
	}

	for (int i = 0; i < CachedLights.Num(); i++)
	{
		CachedLights[i]->SetCastShadows(false);
	}


	Camera->PostProcessSettings = PostProcessFLIR;

	SetAllThermalObject(1);
}

void UFLIRView::TurnOffFLIRVision()
{
	PostProcessFLIR.WeightedBlendables.Array.Empty();

	PostProcessFLIR.bOverride_VignetteIntensity = true;
	PostProcessFLIR.bOverride_GrainJitter = true;
	PostProcessFLIR.bOverride_GrainIntensity = true;

	PostProcessFLIR.VignetteIntensity = 0;
	PostProcessFLIR.GrainJitter = 0;
	PostProcessFLIR.GrainIntensity = 0;

	for (int i = 0; i < CachedLights.Num(); i++)
	{
		CachedLights[i]->SetCastShadows(true);
	}

	Camera->PostProcessSettings = DefaultPostProcessSetting;


	SetAllThermalObject(0);
}

void UFLIRView::SetAllThermalObject(int toggleType)
{

	// 1. we find all the actors in the world
	TArray<AActor*> ActorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsInWorld);

	// we go through all the actors in world, and get each component.
	TArray<UThermalObject*> ThermalObjectActors;
	TArray<UThermalObject*> CurrentThermalObjectActors;

	for (int i = 0; i < ActorsInWorld.Num(); i++)
	{

		AActor* CurrentActor = ActorsInWorld[i];

		if (CurrentActor == nullptr)
			continue;

		CurrentActor->GetComponents<UThermalObject>(CurrentThermalObjectActors, true);

		if (CurrentThermalObjectActors.Num() > 0)
		{
			ThermalObjectActors.Add(CurrentThermalObjectActors[0]);

			//UE_LOG(LogTemp, Warning, TEXT("actor name: %s"), *(CurrentActor->GetName()));

			CurrentThermalObjectActors[0]->SetMaterialVisualType(toggleType);
		}
	}





	
}

