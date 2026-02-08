#pragma once

UENUM(BlueprintType)
enum class EPunchDirection : uint8
{
	None = 0,
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4,
	Punch = 5,
	Start = 6
};
