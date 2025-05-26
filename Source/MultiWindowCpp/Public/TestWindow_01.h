// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TestWindow_01.generated.h"

/**
 * UTestWindow_01 is a blueprintable class designed for managing external windows
 * in a multi-window application. It provides functionality to create and close
 * windows dynamically during runtime.
 */
UCLASS(Blueprintable)
class MULTIWINDOWCPP_API UTestWindow_01 : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "TestWindow")
	void CreateWindow();

	UFUNCTION(BlueprintCallable, Category = "TestWindow")
	void CloseWindow();

private:
	TSharedPtr<SWindow> ExternalWindow;
};
