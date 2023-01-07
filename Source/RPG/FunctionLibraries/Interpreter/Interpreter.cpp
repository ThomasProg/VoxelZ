// Fill out your copyright notice in the Description page of Project Settings.

#include "Interpreter.h"
#include "Engine.h"

//void CMD::MakeClass(FString className)
//{
//	CMD a;
//	this->Classes.Add(className, a);
//
//}
//
//
//void CMD::MakeInstance(C* parent, FString instanceName)
//{
//	//CMD* a = static_cast<CMD*>(parent);
//	//this->instancesVariables.Add(instanceName, *a);
//	CMD b = *this;
//	this->Variables.Add(instanceName,b);
//
//}
//
//
//void UInterpreter::Main(FString command, FString& line)
//{
//	//CMD c;				//classe de base
//	//CMD* cmd = &c;		//classe de base
//	CMD cmd;
//
//	cmd.MakeClass(TEXT("Player"));				   //créer la classe "joueur"
//	CMD*x = static_cast<CMD*>(cmd.Classes.Find(TEXT("Player")));
//	cmd.MakeInstance(x, TEXT("Meltwin"));							   //créer une instance de la classe "Player" nommée "Meltwin"
//	cmd.MakeInstance(x, TEXT("lepiegeur"));						   //créer une instance de la classe "Player" nommée "lepiegeur"
//
//	//cmd->instancesVariables.Find("Meltwin")->Variables.Add("gamemode", "Je suis un cookie ! Hihihi !");	   //dans l'instance "Meltwin", donne la valeur "Je suis un cookie ! Hihihi !" à la variable "gamemode"
//	CMD temp;
//	cmd.Variables.Get(TEXT("Meltwin"), temp);
//	if (&temp != nullptr)
//	{
//		FString aaa = "gamemode";
//		temp.Variables.Add(aaa, TEXT("Je suis un cookie ! Hihihi !"));
//	}
//	//delete &temp;
//
//	FString function;
//	TArray<FString> Parameters;
//	//FString command = "gamemode Meltwin lepiegeur";
//	CommandToCode(command,function,Parameters);				   //transforme la commande en code
//
//	
//	cmd.SetVariable(Parameters[0], Parameters[1]);			   //set les variable
//
//	//line = *cmd->Variables.Get();//instancesVariables.Find("lepiegeur")->Variables.Get("gamemode");		 
//	CMD temp3;
//	cmd.Variables.Get(TEXT("lepiegeur"), temp3);
//	if (&temp != nullptr)
//	{
//		FString temp2;
//		temp3.Variables.Get(TEXT("gamemode"), temp2);
//		if (&temp2 != nullptr)
//		{
//			line = temp2;
//		}
//	}
//
//	//Functions<> testing;	Variables<FString> testing2;  Variables<int32> testing3;
//	//testing.Arguments.Add(testing2);   testing.Arguments.Add(testing3);
//}
//
//void UInterpreter::CommandToCode(FString command, FString& functionName, TArray<FString>& Parameters)
//{
//	command.ParseIntoArray(Parameters, TEXT(" "), true);
//	functionName = Parameters[0];
//	Parameters.RemoveAt(0);
//
//	bool bNotTreated = true;
//
//	if (functionName == TEXT(""))
//	{
//		bNotTreated = false;
//	}
//
//	if (bNotTreated)
//	{
//		if (Parameters.Num() == 1)
//		{
//			Parameters[0].Append(TEXT(".") + functionName);
//		}
//		if (Parameters.Num() == 2)
//		{
//			Parameters.Insert(/*PlayerName*/TEXT("lepiegeur.") + functionName,0);
//		}
//
//		Parameters[1].Append(TEXT(".") + functionName);
//	}
//
//}
//
//void CMD::GetObjectParent(FString& variableStorage, CMD*& object)
//{
//	FString Left;
//	FString Right;
//	if (variableStorage.Split(TEXT("."), &Left, &Right))
//	{
//		//CMD* str = this->instancesVariables.Find(Left);
//		variableStorage = Right;
//
//		C* temp = x;
//		//object->Variables.Get(valuePath, &temp);
//		//if (&temp != nullptr)
//		//{
//		//	toStoreIn->Variables.Add(variableStoragePath, temp);
//		//}
//		//static_cast<CMD*>(this->Variables.Get(Left))->GetObjectParent(variableStorage, object);
//		this->Variables.Get(Left, *temp);
//		if (&temp != nullptr)
//			static_cast<CMD*>(temp)->GetObjectParent(variableStorage, object);
//	}
//	else
//	{
//		object = this;
//		//UInterpreter::SetCMD(object, this);
//		//object = this;
//		//object.Variables = Variables;
//
//	//	object->Variables.boolArray = this->Variables.boolArray;
//	//	object->Variables.charArray = this->Variables.charArray;
//	//	object->Variables.floatArray = this->Variables.floatArray;
//	//	object->Variables.doubleArray = this->Variables.doubleArray;
//	//	object->Variables.int32Array = this->Variables.int32Array;
//	//	object->Variables.FStringArray = this->Variables.FStringArray;
//	//	object->Variables.CArray = this->Variables.CArray;
//
//	//	object->Functions = this->Functions;
//	//	object->Classes = this->Classes;
//	}
//}
//
//void CMD::SetVariable(FString variableStoragePath, FString valuePath)
//{
//	CMD* toStoreIn;
//	CMD* toGive;
//	this->GetObjectParent(variableStoragePath, toStoreIn);
//	this->GetObjectParent(valuePath, toGive);
//
//	//toStoreIn->Variables.Add(variableStorage,*toGive->Variables.Find(value));
//
//	FString temp;
////	bool b;
//	//if (&toStoreIn == nullptr)
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, valuePath);
////	toGive->Variables.isValid(valuePath, temp, b);	//valuePath
//	if (toGive->Variables.FStringArray.Contains(TEXT("Meltwin")))
//	//if (b)
//	{
//		toGive->Variables.Get(valuePath, temp);
//		if (&temp != nullptr)
//		{
//			toStoreIn->Variables.Add(variableStoragePath, temp);
//		}
//	}
//	
//}
//
//
//void UInterpreter::SetCMD(CMD* c, CMD* d)
//{
//	c = d;
//	//arrayOfEveryType& a = c->Variables; 
//	//const arrayOfEveryType& b = d->Variables;
//	//a.boolArray = b.boolArray;
//	//a.charArray = b.charArray;
//	//a.floatArray = b.floatArray;
//	//a.doubleArray = b.doubleArray;
//	//a.int32Array = b.int32Array;
//	//a.FStringArray = b.FStringArray;
//	//a.CArray = b.CArray;
//}