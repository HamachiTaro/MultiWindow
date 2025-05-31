// Fill out your copyright notice in the Description page of Project Settings.


#include "ExternalCameraWindowManager.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SWindow.h"
#include "Brushes/SlateImageBrush.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/Texture2D.h"

void UExternalCameraWindowManager::CreateExternalWindow(UTextureRenderTarget2D* RenderTarget, const FVector2D WindowSize)
{
	if (RenderTarget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RenderTarget is null"));
		return;
	}

	CurrentRenderTarget = RenderTarget;

	FName ResourceName(*FString::Printf(TEXT("ExternalWindow_%p"), this));
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

	// ExternalWindow->SetSizingRule(ESizingRule::FixedSize);
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

