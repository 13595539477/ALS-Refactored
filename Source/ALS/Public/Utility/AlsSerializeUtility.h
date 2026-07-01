// Copyright Hac. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/MovementBaseInterface.h"


inline FArchive& operator<<(FArchive& Archive, FMovementBaseInterfaceData& InterfaceData)
{
	Archive << InterfaceData.PhysicsObjectOwner;
	if (Archive.IsLoading())
	{
		if (UObject* BaseObject = InterfaceData.PhysicsObjectOwner.Get())
		{
			InterfaceData.Set(BaseObject);
		}
		else
		{
			InterfaceData.Clear();
		}
	}
	return Archive;
}
