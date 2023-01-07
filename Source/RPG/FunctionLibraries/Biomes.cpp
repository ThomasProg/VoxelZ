// Fill out your copyright notice in the Description page of Project Settings.

#include "Biomes.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"




float UBiomes::Humidity(FIntVector Coordonates)
{
	float Humidity = 10000.0f;
	Humidity -= float(abs(Coordonates.Y)) / 4000; //40 millions de blocs pour atteindre une humidité de 0	  / pour chaque bloc en plus en y, -1/4000 = -0.00025 d'humidité
	return Humidity;
}

float UBiomes::AverageTemperature(FIntVector Coordonates)
{
	float Celsus = 150.0f;
	Celsus -= Humidity(Coordonates)- 10000.0f;
	Celsus -= float(abs(Coordonates.Z)) / 200.0f;
	return Celsus;
}

int32 UBiomes::GetBiomeYAxis(int32 Y)
{
	//int32& Y = Coordonates.Y;
	Y = abs(Y);
	Y %= 270000*2;
	if (Y > 270000)
		Y = 270000 - (Y % 270000);
	//Y est entre 0 et 270 000
	Y /= 270000/9; //on divise; cela donne 9 grands biomes
	return Y;
}

int32 UBiomes::GetBiomeYZAxisAboveSurface(FIntVector Coordonates)
{
	int32 Y = 0;
	int32& Z = Coordonates.Y;

	if (Z < 0)
		return Y;	//Mer
	if (Z < 15000)
		Y++;;		//Troposphère
	if (Z < 15000)
		Y++;;		//Statosphère
	if (Z < 15000)
		Y ++;		//Hesosphère
	if (Z < 15000)
		Y++;		//Therhosphère
	if (Z < 15000)
		Y++;		//Hexosphère
	if (Z < 15000)
		Y++;		//Space

	Y *= 10;
	Y += GetBiomeYAxis(Coordonates.Y);
	return Y;
}

int32 UBiomes::GetBiomeYZAxisBelowSurface(FIntVector Coordonates, float Surface)
{
	int32 Chunk;
	int32 Z = Coordonates.Z;
	if (Z > -30000)
	{
		if (Surface > 0)
		{
			Chunk = 1;		// croute continentale
		}
		else
		{
			Chunk = 2;		// croute océanique
		}
	}
	if (Z < -30000 && Z > -100000)
	{
		Chunk = 3;			//manteau lithosphérique
	}
	if (Z < -100000 && Z > -700000)
	{
		Chunk = 4;			//Asthénosphère
	}
	if (Z < -700000 && Z > -2900000)
	{
		Chunk = 5;			//manteau inférieur
	}
	if (Z < -2900000 && Z > -5170000)
	{
		Chunk = 6;			//Noyau externe
	}
	if (Z < -5170000)
	{
		Chunk = 7;			//Noyau interne
	}

	return Chunk;
}

float UBiomes::TemperatureWithAltitude(int32 Zz)
{
	float Z = Zz;
	float Celsus = 0.0;
	if (Z < 10000.0)
	{
		Celsus = -80.0 * Z / 10000.0 + 20.0;	// Formula :	EcartTemperature * Z/EcartAltitude + TemperatureDeBase
	}
	if (Z >= 10000.0 && Z < 20000.0)
	{
		Celsus = -60.0;
	}
	if (Z >= 20000.0 && Z < 50000.0)
	{
		Celsus = 70.0 * (Z- 20000.0) / 30000.0 - 40.0;
	}
	if (Z >= 50000.0 && Z < 55000.0)
	{
		Celsus = -10.0;
	}
	if (Z >= 55000.0 && Z < 90000.0)
	{
		Celsus = -70.0 * (Z - 55000.0) / 35000.0 - 10.0;
	}
	if (Z >= 90000.0)
	{
		Celsus = 130.0 * (Z - 90000.0) / 20000.0 - 85.0;
	}

	return Celsus;
}

float UBiomes::AtmosphericPression(int32 Z, float Kelvin)		//imprecise
{
	return 1013.25 * FGenericPlatformMath::Pow((1 - (0.0065 * Z) / Kelvin),5.255);		  
}

float UBiomes::CelsiusToKelvin(float Celsius)
{
	return  Celsius + 273, 15;
}