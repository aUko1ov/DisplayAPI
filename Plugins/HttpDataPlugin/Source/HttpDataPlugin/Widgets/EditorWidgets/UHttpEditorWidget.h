
#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "UHttpEditorWidget.generated.h"

class UDisplayHttpDataComponent;

UCLASS()
class HTTPDATAPLUGIN_API UHttpEditorWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void FetchDataInEditor();

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnFetchDataClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* FetchDataButton;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OutputTextBlock;
};