// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.generated.h"

UCLASS()
class TEST_API ACEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemy();

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

	// 태어날때 타겟방향을 구하고 그방향으로 계속 이동하고 싶다.
	// 필요속성 : 타겟방향
	FVector Direction;

	UPROPERTY(EditAnywhere, Category="Settings")
	float Speed = 500;

	void FindTargetDirection();
	void MoveToTarget();

	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Fire();
	// 필요속성 : 총알공장
	UPROPERTY(EditAnywhere, Category=Settings)
	TSubclassOf<class ACBullet> BulletFactory;

	// 필요속성 : 총알 갯수, 거리
	UPROPERTY(EditAnywhere, Category="Bullet")
	int32 BulletCount = 6;
	UPROPERTY(EditAnywhere, Category="Bullet")
	float Distance = 100;

	// 필요속성 : 생성시간, 경과시간, 최대 몇개?, 현재 몇개?
	UPROPERTY(EditAnywhere, Category="Settings")
	float CreateTime = 0.205f;
	float CurrentTime = 0;
	// 현재 몇개?
	int32 CurrentBulletCount = 0;
};
