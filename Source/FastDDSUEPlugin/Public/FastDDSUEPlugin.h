// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
// #pragma warning(disable : 4668)
// #pragma warning(disable : 4582)
// #pragma warning(disable : 4265)

// #include "LocationRotationSubscriber.h"

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FFastDDSUEPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	// LocationRotationSubscriber mysub;
};
