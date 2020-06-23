// Fill out your copyright notice in the Description page of Project Settings.


#include "SqureConverter.h"

FSqureConverterPoint::FSqureConverterPoint(const FString& InPointStrX, const FString& InPointStrY, const FVector2D& InPointLocationInGame)
{
	if (!(InPointStrX.IsNumeric() && InPointStrX.IsNumeric()))
	{
		bIsValid = false;
	}
	else
	{
		XInMap              = FCString::Atod(*InPointStrX);
		YInMap              = FCString::Atod(*InPointStrY);
		VectorInWorld = InPointLocationInGame;
		bIsValid            = true;
	}
};


FSqureConverterPoint::FSqureConverterPoint(double InPointX, double InPointY, const FVector2D& InPointLocationInGame)
	: 
	XInMap(InPointX),
	YInMap(InPointY),
	VectorInWorld(InPointLocationInGame)
{
	bIsValid = true;
}

FSqureConverterPoint::FSqureConverterPoint(const FSqureConverterPoint& Other)
{
	if (!Other.IsValid())
	{
		this->bIsValid = false;
	}

	else
	{
		this->XInMap              = Other.XInMap;
		this->YInMap              = Other.YInMap;
		this->VectorInWorld = Other.VectorInWorld;
		this->bIsValid            = true;
	}
	
	
}

bool FSqureConverterPoint::GeneratePointRatio(double& RatioX, double& RatioY)
{
	if (!IsValid())
	{
		return false;
	}
	RatioX = (double)(this->VectorInWorld.X) / XInMap;
	RatioY = (double)(this->VectorInWorld.Y) / YInMap;

	return true;
}

FSqureConverterPoint FSqureConverterPoint::operator-(const FSqureConverterPoint& Other)
{
	return FSqureConverterPoint
	(
		this->XInMap              - Other.XInMap,
		this->YInMap              - Other.YInMap,
		this->VectorInWorld - Other.VectorInWorld
	);
}

bool USqureConverter::Init(const FString& TopLeftStrX, const FString& TopLeftStrY, const FVector2D& TopLeftPoint, const FString& BottomRightStrX, const FString& BottomRightStrY, const FVector2D& BottomRightPoint)
{
	TopLeft     = FSqureConverterPoint(TopLeftStrX,     TopLeftStrY,     TopLeftPoint);
	if (!TopLeft.IsValid())
	{
		return false;
	}

	BottomRight = FSqureConverterPoint(BottomRightStrX, BottomRightStrY, BottomRightPoint);
	if (!BottomRight.IsValid())
	{
		return false;
	}
	this->Area = BottomRight - TopLeft;

	return Area.IsValid();
	
}

bool USqureConverter::ConvertPointToLocation(const FString& PointStrX, const FString& PointStrY, FVector2D& OutLocation)
{
	
	if (!(PointStrX.IsNumeric() && PointStrY.IsNumeric()))
	{
		UE_LOG(LogTemp, Error, TEXT("ConvertPointToLocation() --- Str failed"));
		return false;
	}

	double XInMap = FCString::Atod(*PointStrX) - TopLeft.XInMap;
	double YInMap = FCString::Atod(*PointStrY) - TopLeft.YInMap;
	double Rx = XInMap / Area.XInMap;
	double Ry = YInMap / Area.YInMap;

	double X = Area.VectorInWorld.X * Rx + TopLeft.VectorInWorld.X;
	double Y = Area.VectorInWorld.Y * Ry + TopLeft.VectorInWorld.Y;
	OutLocation = FVector2D(X, Y);

	/*UE_LOG(LogTemp, Error, TEXT(" "));
	UE_LOG(LogTemp, Error, TEXT("--------------------------LogStart--------------------------"));
	UE_LOG(LogTemp, Error, TEXT("XInMap = FCString::Atod(*PointStrX) - TopLeft.XInMap"));
	UE_LOG(LogTemp, Error, TEXT("%.16f = %.16f - %.16f"), XInMap, FCString::Atod(*PointStrX), TopLeft.XInMap);
	UE_LOG(LogTemp, Error, TEXT(" "));

	UE_LOG(LogTemp, Error, TEXT("YInMap = FCString::Atod(*PointStrY) - TopLeft.YInMap"));
	UE_LOG(LogTemp, Error, TEXT("%.16f = %.16f - %.16f"), YInMap, FCString::Atod(*PointStrY), TopLeft.YInMap);
	UE_LOG(LogTemp, Error, TEXT(" "));

	UE_LOG(LogTemp, Error, TEXT("Rx = XInMap / Area.XInMap"));
	UE_LOG(LogTemp, Error, TEXT("%.16f = %.16f / %.16f"), Rx, XInMap, Area.XInMap);
	UE_LOG(LogTemp, Error, TEXT(" "));

	UE_LOG(LogTemp, Error, TEXT("Ry = YInMap / Area.YInMap"));
	UE_LOG(LogTemp, Error, TEXT("%.16f = %.16f / %.16f"), Ry, YInMap, Area.YInMap);
	UE_LOG(LogTemp, Error, TEXT(" "));

	UE_LOG(LogTemp, Error, TEXT("X = Area.VectorInWorld.X * Rx + TopLeft.VectorInWorld.X"));
	UE_LOG(LogTemp, Error, TEXT("%.16f = %.16f * %.16f + %.16f"), X, Area.VectorInWorld.X, Rx, TopLeft.VectorInWorld.X);
	UE_LOG(LogTemp, Error, TEXT(" "));

	UE_LOG(LogTemp, Error, TEXT("Y = Area.VectorInWorld.Y * Ry + TopLeft.VectorInWorld.Y"));
	UE_LOG(LogTemp, Error, TEXT("%.16f = %.16f * %.16f + %.16f"), Y, Area.VectorInWorld.Y, Ry, TopLeft.VectorInWorld.Y);
	UE_LOG(LogTemp, Error, TEXT(" "));

	UE_LOG(LogTemp, Error, TEXT("OutLocation = FVector2D(X, Y)"));
	UE_LOG(LogTemp, Error, TEXT("%s = FVector2D(%.16f, %.16f)"), *OutLocation.ToString(), X, Y);
	UE_LOG(LogTemp, Error, TEXT(" "));


	UE_LOG(LogTemp, Error, TEXT("--------------------------LogEnd----------------------------"));
	UE_LOG(LogTemp, Error, TEXT(" "));*/
	return true;
}
