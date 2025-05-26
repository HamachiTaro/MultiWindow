// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWindow_01.h"

void UTestWindow_01::CreateWindow()
{
	ExternalWindow = SNew(SWindow)
		.Title(FText::FromString("Test Window"))
		.ClientSize(FVector2D(960, 540));

	// Slateにウィンドウを登録
	FSlateApplication::Get().AddWindow(ExternalWindow.ToSharedRef());
}

void UTestWindow_01::CloseWindow()
{
	if (ExternalWindow.IsValid())
	{
		FSlateApplication::Get().RequestDestroyWindow(ExternalWindow.ToSharedRef());
		ExternalWindow.Reset();
	}
}
