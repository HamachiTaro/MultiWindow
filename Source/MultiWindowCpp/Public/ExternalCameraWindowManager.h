// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExternalCameraWindowManager.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class MULTIWINDOWCPP_API UExternalCameraWindowManager : public UObject
{
	GENERATED_BODY()

public:
	/** Render Targetを別ウィンドウに表示 **/
	UFUNCTION(BlueprintCallable, Category = "External Window")
	void CreateExternalWindow(UTextureRenderTarget2D* RenderTarget, FVector2D WindowSize = FVector2D(1920, 1080));

	UFUNCTION(BlueprintCallable, Category = "External Window")
	void CloseExternalWindow();
	
private:
	// 表示用のウィンドウ
	TSharedPtr<SWindow> ExternalWindow;
	
	/** RenderTarget を表示するための Image Brush */
	TSharedPtr<FSlateDynamicImageBrush> ImageBrush;

	/** ウィジェット（画像表示） */
	TSharedPtr<SImage> ImageWidget;

	/** RenderTarget のキャッシュ参照 */
	UPROPERTY()
	UTextureRenderTarget2D* CurrentRenderTarget = nullptr;

	/** 定期更新用タイマー */
	FTSTicker::FDelegateHandle TickHandle;

	bool Tick(float DeltaTime);

	
};
