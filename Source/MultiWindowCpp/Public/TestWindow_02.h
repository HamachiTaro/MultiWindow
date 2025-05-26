// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TestWindow_02.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MULTIWINDOWCPP_API UTestWindow_02 : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "TestWindow")
	void CreateWindow(UTexture2D* Texture);

	UFUNCTION(BlueprintCallable, Category = "TestWindow")
	void CloseWindow();

private:
	TSharedPtr<SWindow> ExternalWindow;

	TSharedPtr<FSlateImageBrush> ImageBrush;
	
	TSharedPtr<SImage> ImageWidget;
};
