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
};
