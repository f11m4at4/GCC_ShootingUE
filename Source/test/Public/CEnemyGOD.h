// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyGOD.generated.h"

UCLASS()
class TEST_API ACEnemyGOD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemyGOD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 필요속성 : 생성시간, 경과시간, 적공장
	UPROPERTY(EditAnywhere, Category="Settings")
	float CreateTime = 2.05f;
	float CurrentTime = 0;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<class ACEnemy> EnemyFactory;
};
