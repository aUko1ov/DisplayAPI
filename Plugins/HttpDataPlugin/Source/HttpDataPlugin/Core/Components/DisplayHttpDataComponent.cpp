
#include "DisplayHttpDataComponent.h"

#include "Components/TextRenderComponent.h"
#include "HttpDataPlugin/Subsystems/HttpSubsystem.h"


void UDisplayHttpDataComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (UHttpSubsystem* HttpSubsystem = GEngine->GetEngineSubsystem<UHttpSubsystem>())
	{
		HttpSubsystem->FetchDataFromServer([this](const FString& Result)
		{
			UpdateText(Result); 
		});
	}
}


void UDisplayHttpDataComponent::UpdateText(const FString& NewText)
{
	if (TextComponent)
	{
		FText DisplayText = FText::FromString(NewText);
		TextComponent->SetText(DisplayText);
	}
}