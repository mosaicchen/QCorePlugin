// 宝吉网络-1234567890


#include "ComponentBPLibrary.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"

#include "SceneManagement.h"
#include "Components/ChildActorComponent.h"
#include "Engine/Texture2DDynamic.h"

UChildActorComponent * UComponentBPLibrary::AddDynamicActorChildComponent(UObject * WorldContextObject,
																	 USceneComponent * parentCOM, 
																	 TSubclassOf< AActor> ActorClass, 
																	 const FTransform & tran)
{
	UChildActorComponent* childActorCOM = NewObject<UChildActorComponent>(parentCOM->GetAttachmentRootActor());
	
	childActorCOM->RegisterComponent();
	childActorCOM->SetChildActorClass(ActorClass);
	//childActorCOM->Register
	childActorCOM->AttachToComponent(parentCOM, FAttachmentTransformRules::KeepRelativeTransform);
	
	return childActorCOM;
}

void UComponentBPLibrary::RestoreDecalSize(UObject * WorldContextObject, UDecalComponent * decal, FVector extend)
{
	decal->DecalSize = extend;
	decal->SceneProxy->SetTransformIncludingDecalSize(decal->GetTransformIncludingDecalSize());
}
