// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interpreter.generated.h"

/**
 * 
 */

//
/////*template< typename T >*/ class arrayOfEveryType {
////private:
////	//TArray<bool> *int32Array;
////	//TArray<TChar> *int32Array;
////	//TArray<float> *int32Array;
////	//TArray<double> *int32Array;
////	//TArray<int32> *int32Array;
////	//TArray<FString> *int32Array;
////
////	TMap<FString, bool> *boolArray;
////	TMap<FString, char> *charArray;
////	TMap<FString, float> *floatArray;
////	TMap<FString, double> *doubleArray;
////	TMap<FString, int32> *int32Array;
////	TMap<FString, FString> *FStringArray;
////
////public:
////	// calss array member function to set element of myarray 
////	// with type T values
////	void Add(int32 name, FString name) { int32Array->Add(name); }
////};
//
//
//class C
//{
//public:
//	//TMap<FString, FString> Variables;  Variables
//	//TMap<FString, arrayOfEveryType> Variables;
//	/*arrayOfEveryType Variables;*/
//	/*TMap<FString, FString> Functions;*/
//	//TMap<FString, FString> Classes;
//	//TMap<FString, FString> instancesVariables;
//};
//
///*template< typename T >*/ class arrayOfEveryType {
//public:
//	//TArray<bool> *int32Array;
//	//TArray<TChar> *int32Array;
//	//TArray<float> *int32Array;
//	//TArray<double> *int32Array;
//	//TArray<int32> *int32Array;
//	//TArray<FString> *int32Array;
//
//	TMap<FString, bool> boolArray;
//	TMap<FString, char> charArray;
//	TMap<FString, float> floatArray;
//	TMap<FString, double> doubleArray;
//	TMap<FString, int32> int32Array;
//	TMap<FString, FString> FStringArray;
//	TMap<FString, C> CArray;
//
//public:
//	void Add(FString name, bool value) { boolArray.Emplace(name, value); }
//	void Add(FString name, char value) { charArray.Emplace(name, value); }
//	void Add(FString name, float value) { floatArray.Emplace(name, value); }
//	void Add(FString name, double value) { doubleArray.Emplace(name, value); }
//	void Add(FString name, int32 value) { int32Array.Emplace(name, value); }
//	void Add(FString name, FString value) { FStringArray.Emplace(name, value); }
//	void Add(FString name, C value) { CArray.Emplace(name, value); }
//
//	//void Get(FString name, bool& value, bool& isValid) { bool* x = boolArray->Find(name);  isValid = (x != nullptr); }
//	//void Get(FString name, char& value, bool& isValid) { char* x = charArray->Find(name); isValid = (x != nullptr); }
//	//void Get(FString name, float& value, bool& isValid) { float* x = floatArray->Find(name);  isValid = (x != nullptr); }
//	//void Get(FString name, double& value, bool& isValid) { double* x = doubleArray->Find(name);  isValid = (x != nullptr);}
//	//void Get(FString name, int32& value, bool& isValid) { int32* x = int32Array->Find(name);  isValid = (x != nullptr);}
//	//void Get(FString name, FString& value, bool& isValid) { FString* x = FStringArray->Find(name);  isValid = (x != nullptr);}
//	//void Get(FString name, CMD& value, bool& isValid) { CMD* x = CMDArray->Find(name);  isValid = (x != nullptr);}
//
//	void Get(FString name, bool& value) { bool* x = boolArray.Find(name); }
//	void Get(FString name, char& value) { char* x = charArray.Find(name); }
//	void Get(FString name, float& value) { float* x = floatArray.Find(name); }
//	void Get(FString name, double& value) { double* x = doubleArray.Find(name); }
//	void Get(FString name, int32& value) { int32* x = int32Array.Find(name); }
//	void Get(FString name, FString& value) { FString* x = FStringArray.Find(name); }
//	void Get(FString name, C& value) { C* x = CArray.Find(name); }
//
//	void isValid(FString name, bool& value, bool& isValid) { isValid = boolArray.Contains(name); }
//	void isValid(FString name, char& value, bool& isValid) { isValid = charArray.Contains(name); }
//	void isValid(FString name, float& value, bool& isValid) { isValid = floatArray.Contains(name); }
//	void isValid(FString name, double& value, bool& isValid) { isValid = doubleArray.Contains(name); }
//	void isValid(FString name, int32& value, bool& isValid) { isValid = int32Array.Contains(name); }
//	void isValid(FString name, C& value, bool& isValid) { isValid = CArray.Contains(name); }
//
//	arrayOfEveryType& operator=(const arrayOfEveryType& b)
//	{
//		this->boolArray = b.boolArray;
//		this->charArray = b.charArray;
//		this->floatArray = b.floatArray;
//		this->doubleArray = b.doubleArray;
//		this->int32Array = b.int32Array;
//		this->FStringArray = b.FStringArray;
//		this->CArray = b.CArray;
//		//this->instancesVariables = b->instancesVariables;
//		return *this;
//	}
//
//};
//
//template <typename typeOfVariable>
//class Variables
//{
//public:
//	FString name;
//	typeOfVariable type;
//	//TMap<FString, FString> Classes;
//	//TMap<FString, FString> instancesVariables;
//};
//
////template <TArray<typename typeOfVariable>>
//class Functions
//{
//public:
//	FString name;
//	arrayOfEveryType Arguments;
//	//TMap<FString, FString> Classes;
//	//TMap<FString, FString> instancesVariables;
//};
//
//class CMD : public C
//{
//public:
//	//TMap<FString, FString> Variables;
//	//TMap<FString, FString> Functions;
//	arrayOfEveryType Variables;
//	TMap<FString, FString> Functions;
//	TMap<FString, C> Classes;
//	//TMap<FString, C> instancesVariables;
//
//	void MakeClass(FString className);
//	void MakeInstance(C* parent, FString className);
//					 
//	CMD& operator=(const CMD& b)
//	{
//		this->Variables = b.Variables;
//		this->Functions = b.Functions;
//		this->Classes = b.Classes;
//		//this->instancesVariables = b->instancesVariables;
//		return *this;
//	}
//
//	void GetObjectParent(FString& variableStorage, CMD*& object);
//
//	void SetVariable(FString variableStorage, FString valuePath);
//};

UCLASS()
class RPG_API UInterpreter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/*CMD* c;*/

	//FString PlayerName;

	//UFUNCTION(BlueprintCallable)
	//static void Main(FString command, FString& line);

	//static void CommandToCode(FString command, FString& functionName, TArray<FString>& Parameters);

	//static void SetCMD(CMD* c, CMD* d);

};
