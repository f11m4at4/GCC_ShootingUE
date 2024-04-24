// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

UCLASS()
class TEST_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// StaticMeshComponent 추가
	UPROPERTY(VisibleAnywhere, Category="Component")
	class UStaticMeshComponent* BodyMesh = nullptr;

	// 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float Speed = 1000;
};
