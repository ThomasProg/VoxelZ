// Fill out your copyright notice in the Description page of Project Settings.

#include "Structures.h"


FS_Stats UStructures::FS_Stats_add(FS_Stats a, FS_Stats b)
{
	FS_Stats c;
	c.life = a.life + b.life;
	c.lifeRegen = a.lifeRegen + b.lifeRegen;
	c.mana = a.mana + b.mana;
	c.manaRegen = a.manaRegen + b.manaRegen;
	c.stamina = a.stamina + b.stamina;
	c.strength = a.strength + b.strength;
	c.magicPower = a.magicPower + b.magicPower;
	c.armor = a.armor + b.armor;
	c.magicArmor = a.magicArmor + b.magicArmor;
	c.Speed = a.Speed + b.Speed;
	return c;
}


FS_Stats UStructures::FS_Stats_substract(FS_Stats a, FS_Stats b)
{
	FS_Stats c;
	c.life = a.life - b.life;
	c.lifeRegen = a.lifeRegen - b.lifeRegen;
	c.mana = a.mana - b.mana;
	c.manaRegen = a.manaRegen - b.manaRegen;
	c.stamina = a.stamina - b.stamina;
	c.strength = a.strength - b.strength;
	c.magicPower = a.magicPower - b.magicPower;
	c.armor = a.armor - b.armor;
	c.magicArmor = a.magicArmor - b.magicArmor;
	c.Speed = a.Speed - b.Speed;
	return c;
}


int32 UStructures::getFblockProperties(FblockProperties block)
{
	if (0 < block.Objects.Num())
		return block.Objects[0].blockType;
	else
		return 0;
}