
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DisplayHttpDataComponent.generated.h"


class UTextRenderComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HTTPDATAPLUGIN_API UDisplayHttpDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UTextRenderComponent* TextComponent;

	virtual void BeginPlay() override;
	
	void UpdateText(const FString& NewText);
};
