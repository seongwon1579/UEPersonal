#pragma once

namespace Debug
{
	static void Print(const FString& Msg, const FColor& Color = FColor::Blue, int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, Msg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}
	
	static void Print(float number, const FColor& Color = FColor::Blue, int32 InKey = -1)
	{
		if (GEngine)
		{
			FString FinalMsg = FString::Printf(TEXT("%f"), number);
            
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, FinalMsg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
	static void Print(int32 number, const FColor& Color = FColor::Blue, int32 InKey = -1)
	{
		if (GEngine)
		{
			FString FinalMsg = FString::Printf(TEXT("%d"), number);
            
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, FinalMsg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
	static void Print(const FString& Msg, float number, const FColor& Color = FColor::Blue, int32 InKey = -1)
	{
		if (GEngine)
		{
			FString FinalMsg = FString::Printf(TEXT("%s : %f"), *Msg, number);
            
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, FinalMsg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
	static void Print(const FString& Msg, int32 number, const FColor& Color = FColor::Blue, int32 InKey = -1)
	{
		if (GEngine)
		{
			FString FinalMsg = FString::Printf(TEXT("%s : %d"), *Msg, number);

			// 합쳐진 FinalMsg를 출력
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, FinalMsg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}
	}
    
}
