// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SqureConverter.generated.h"

USTRUCT()
struct FSqureConverterPoint
{
	GENERATED_USTRUCT_BODY()

public:

	FSqureConverterPoint() {};
	FSqureConverterPoint(const FSqureConverterPoint& Other);

	FSqureConverterPoint(
		double           InPointX,
		double           InPointY,
		const FVector2D& InPointLocationInGame);

	FSqureConverterPoint(
		const FString&   InPointStrX,
		const FString&   InPointStrY,
		const FVector2D& InPointLocationInGame);

	bool IsValid() const
	{
		return bIsValid;
	}
	
	bool GeneratePointRatio(double& RatioX, double& RatioY);


	FSqureConverterPoint operator-(const FSqureConverterPoint& Other);

	double XInMap;
	double YInMap;

	FVector2D VectorInWorld;

protected:

	bool bIsValid = false;

};


/**
 * 
 */
UCLASS(BlueprintType)
class COORDINATECONVERTER_API USqureConverter : public UObject
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable, Category = "CoordinateConverter|SqureConverter")
		bool Init(
			const FString&   TopLeftStrX,
			const FString&   TopLeftStrY,
			const FVector2D& TopLeftPoint,
			const FString&   BottomRightStrX,
			const FString&   BottomRightStrY,
			const FVector2D& BottomRightPoint);

	UFUNCTION(BlueprintCallable, Category = "CoordinateConverter|SqureConverter")
		bool ConvertPointToLocation(
			const FString& PointStrX, 
			const FString& PointStrY, 
			FVector2D&     OutLocation);

protected:

	FSqureConverterPoint TopLeft;
	FSqureConverterPoint BottomRight;
	FSqureConverterPoint Area;
	
};
