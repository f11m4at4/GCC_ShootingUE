// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

UCLASS()
class TEST_API ACPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// StaticMeshComponent 추가
	UPROPERTY(VisibleAnywhere, Category="Component")
	class UStaticMeshComponent* BodyMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category="Component")
	class USceneComponent* FirePosition = nullptr;

	float h;
	float v;
	// 좌우입력처리함수
	void Horizontal(float value);
	void Vertical(float value);

	// 사용자가 발사버튼을 누르면 총알을 발사하고 싶다.
	void Fire();
	// 필요속성 : 총알공장
	UPROPERTY(EditAnywhere, Category=Settings)
	TSubclassOf<class ACBullet> BulletFactory;
};
