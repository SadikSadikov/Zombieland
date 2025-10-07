#pragma once

UENUM(Blueprintable, BlueprintType)
enum class ECombatState : uint8
{
	ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECS_Attacking UMETA(DisplayName = "Attacking"),
	ECS_Recharging UMETA(DisplayName = "Recharging"),
	ECS_SwappingWeapons UMETA(DisplayName = "SwappingWeapons"),

	ECS_MAX UMETA(DisplayName = "MaxDefault")
};