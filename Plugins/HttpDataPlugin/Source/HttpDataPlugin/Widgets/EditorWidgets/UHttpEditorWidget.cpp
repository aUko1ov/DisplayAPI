
#include "UHttpEditorWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HttpDataPlugin/Core/Components/DisplayHttpDataComponent.h"
#include "HttpDataPlugin/Subsystems/HttpSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UHttpEditorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (FetchDataButton)
	{
		FetchDataButton->OnClicked.AddDynamic(this, &UHttpEditorWidget::OnFetchDataClicked);
	}
}

void UHttpEditorWidget::OnFetchDataClicked()
{
	FetchDataInEditor();
}

void UHttpEditorWidget::FetchDataInEditor()
{
	if (UHttpSubsystem* HttpSubsystem = GEngine->GetEngineSubsystem<UHttpSubsystem>())
	{
		HttpSubsystem->FetchDataFromServer([this](const FString& Result)
		{
			if (OutputTextBlock)
			{
				OutputTextBlock->SetText(FText::FromString(Result));
			}
		});
	}
	
}

