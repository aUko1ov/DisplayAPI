
#include "HttpSubsystem.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UHttpSubsystem::FetchDataFromServer(const TFunction<void(FString)>& OnSuccessCallback)
{
    SuccessCallback = OnSuccessCallback;
    
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UHttpSubsystem::OnResponseReceived);
    Request->SetURL("https://artpro.studio:3006/v1.0/projects/sot/ratings/");
    Request->SetVerb("GET");
    Request->ProcessRequest();
}

// Берем первый элемент. Извлекаем значения полей "namePlayer" и "rating"
void UHttpSubsystem::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            if (JsonObject->HasField("data"))
            {
                TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField("data");
                
                if (DataObject->HasField("ratings"))
                {
                    TArray<TSharedPtr<FJsonValue>> RatingsArray = DataObject->GetArrayField("ratings");
                    
                    if (RatingsArray.Num() > 0)
                    {
                        TSharedPtr<FJsonObject> FirstRatingObject = RatingsArray[0]->AsObject();
                        
                        FString PlayerName = FirstRatingObject->GetStringField("namePlayer");
                        float RatingValue = FirstRatingObject->GetNumberField("rating");
                        
                        FString Result = FString::Printf(TEXT("Player: %s, Rating: %.2f"), *PlayerName, RatingValue);
                        
                        if (SuccessCallback)
                        {
                            SuccessCallback(Result);
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (SuccessCallback)
        {
            SuccessCallback(TEXT("Error fetching data"));
        }
    }
}
