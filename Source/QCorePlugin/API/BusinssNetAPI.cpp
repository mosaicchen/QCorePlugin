// L.Q 2019


#include "BusinssNetAPI.h"

#include "Runtime/Core/Public/Misc/FileHelper.h"

#include "IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "IImageWrapper.h"


static const FString api_UploadImage = TEXT("http://localhost:63664/api/Test/UploadImageFromCS?size=%d&filename=%s");

FHttpRequestPtr UBusinssNetAPI::UploadImage()
{
	TArray<uint8> binrary_data;
	TArray<FString> arr_path;

//#if UE_BUILD_DEVELOPMENT
	arr_path.Add(TEXT("d:/left.jpg"));
	arr_path.Add(TEXT("d:/top.jpg"));
	arr_path.Add(TEXT("d:/back.jpg"));
//#endif

	for (FString path : arr_path) 
	{
		FString left, right;

		path.Split(TEXT("/"), &left, &right, ESearchCase::IgnoreCase, ESearchDir::FromEnd);		
		
		FString fileName = FGenericPlatformHttp::UrlEncode( right );
		FFileHelper::LoadFileToArray(binrary_data, *path /* TEXT("d:/11.zip") */ );

		FString url = TEXT(""); // FString::Printf(*api_UploadImage, binrary_data.Num(), *fileName);
		TSharedRef<IHttpRequest> req = UNetAPI::createUploadImageRequest(url, binrary_data);

		req->OnProcessRequestComplete().BindLambda([=](	FHttpRequestPtr  Request	,
														FHttpResponsePtr Response	,
														bool bConnectedSuccessfully		)
		{
			UE_LOG(LogTemp, Log, TEXT("[UploadImage] : complated {%s}. is connect {%d}"),  *api_UploadImage, bConnectedSuccessfully);
		});

		if (req->ProcessRequest())
		{
			UE_LOG(LogTemp, Log, TEXT("[UploadImage] : starting......"));
		}
	}

	return nullptr;
}