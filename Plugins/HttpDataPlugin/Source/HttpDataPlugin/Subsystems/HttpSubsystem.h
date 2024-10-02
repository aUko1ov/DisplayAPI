
#pragma once

#include "CoreMinimal.h"
#include "HttpFwd.h"
#include "Subsystems/EngineSubsystem.h"
#include "HttpSubsystem.generated.h"


UCLASS()
class HTTPDATAPLUGIN_API UHttpSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	void FetchDataFromServer(const TFunction<void(FString)>& OnSuccessCallback);

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	TFunction<void(FString)> SuccessCallback;
};