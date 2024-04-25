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
	// StaticMeshComponent �߰�
	UPROPERTY(VisibleAnywhere, Category="Component")
	class UStaticMeshComponent* BodyMesh = nullptr;

	// �¾�� Ÿ�ٹ����� ���ϰ� �׹������� ��� �̵��ϰ� �ʹ�.
	// �ʿ�Ӽ� : Ÿ�ٹ���
	FVector Direction;

	UPROPERTY(EditAnywhere, Category="Settings")
	float Speed = 500;

	void FindTargetDirection();
	void MoveToTarget();

	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Fire();
	// �ʿ�Ӽ� : �Ѿ˰���
	UPROPERTY(EditAnywhere, Category=Settings)
	TSubclassOf<class ACBullet> BulletFactory;

	// �ʿ�Ӽ� : �Ѿ� ����, �Ÿ�
	UPROPERTY(EditAnywhere, Category="Bullet")
	int32 BulletCount = 6;
	UPROPERTY(EditAnywhere, Category="Bullet")
	float Distance = 100;

	// �ʿ�Ӽ� : �����ð�, ����ð�, �ִ� �?, ���� �?
	UPROPERTY(EditAnywhere, Category="Settings")
	float CreateTime = 0.205f;
	float CurrentTime = 0;
	// ���� �?
	int32 CurrentBulletCount = 0;
};
