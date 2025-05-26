// Fill out your copyright notice in the Description page of Project Settings.


#include "ExternalCameraWindowManager.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SWindow.h"
#include "Brushes/SlateImageBrush.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/Texture2D.h"

void UExternalCameraWindowManager::CreateExternalWindow(UTextureRenderTarget2D* RenderTarget)
{
	if (RenderTarget == nullptr)
	{
		return;
	}

	CurrentRenderTarget = RenderTarget;

	const FName ResourceName("ExternalWindow");
	const FVector2D WindowSize(1920, 1080);
	
	ImageBrush = MakeShareable(new FSlateDynamicImageBrush(ResourceName, WindowSize));

	ImageWidget = SNew(SImage).Image(ImageBrush.Get());

	// ウィンドウ作成
	ExternalWindow = SNew(SWindow)
		.Title(FText::FromString("External Camera View"))
		.ClientSize(WindowSize)
		.SupportsMaximize(true)
		.SupportsMinimize(true);

	ExternalWindow->SetContent(ImageWidget.ToSharedRef());

	// slateにウィンドウを登録
	FSlateApplication::Get().AddWindow(ExternalWindow.ToSharedRef());

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &UExternalCameraWindowManager::Tick),
		0.016f // 60fps
	);
	
}

void UExternalCameraWindowManager::CloseExternalWindow()
{
	if (ExternalWindow.IsValid())
	{
		FSlateApplication::Get().RequestDestroyWindow(ExternalWindow.ToSharedRef());
		ExternalWindow.Reset();
	}

	ImageWidget.Reset();
	ImageBrush.Reset();
	CurrentRenderTarget = nullptr;
}

bool UExternalCameraWindowManager::Tick(float DeltaTime)
{
	if (CurrentRenderTarget == nullptr)
	{
		return false;
	}

	ImageBrush->SetResourceObject(CurrentRenderTarget);
	if (ImageWidget.IsValid())
	{
		ImageWidget->Invalidate(EInvalidateWidgetReason::LayoutAndVolatility);
	}
	return true;
}
