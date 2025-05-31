// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWindow_02.h"

void UTestWindow_02::CreateWindow(UTexture2D* Texture)
{
	if (Texture == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Texture is null"));
		return;
	}
	
	const FVector2D WindowSize(Texture->GetSizeX(), Texture->GetSizeY());

	// ウィンドウを作成
	ExternalWindow = SNew(SWindow)
		.Title(FText::FromString("Test Window"))
		.ClientSize(WindowSize);

	// ImageBrushを作成。これは画像データを保持する
	const FName ResourceName("Tex");
	ImageBrush = MakeShareable(new FSlateImageBrush(ResourceName, WindowSize));
	// ImageBrush = MakeShareable(new FSlateImageBrush());
	ImageBrush->SetResourceObject(Texture);
	
	// Imageウィジェット(UIパーツ)を作成
	ImageWidget = SNew(SImage).Image(ImageBrush.Get());

	// ウィンドウにImageウィジェットをセット
	ExternalWindow->SetContent(ImageWidget.ToSharedRef());
	
	// 実際にウィンドウを表示する
	FSlateApplication::Get().AddWindow(ExternalWindow.ToSharedRef());
}

void UTestWindow_02::CloseWindow()
{
	if (ExternalWindow.IsValid())
	{
		FSlateApplication::Get().RequestDestroyWindow(ExternalWindow.ToSharedRef());
		ExternalWindow.Reset();
	}

	if (ImageWidget.IsValid())
	{
		ImageWidget.Reset();
	}

	if (ImageBrush.IsValid())
	{
		ImageBrush.Reset();
	}
}
