// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ʿ��� ������Ʈ ����
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	// Root ������Ʈ�� ����
	RootComponent = BodyMesh;

	// Static Mesh Data �� �ʱ�ȭ �ϰ� �ʹ�.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// ���������� �ε��� �ƴٸ�
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh �� �����͸� �Ҵ��ϰ� �ʹ�.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// ���� �ε�
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	// ���������� �ε��� �ƴٸ�
	if (TempMat.Succeeded())
	{
		// -> BodyMesh �� �����͸� �Ҵ��ϰ� �ʹ�.
		BodyMesh->SetMaterial(0, TempMat.Object);
	}

	BodyMesh->SetRelativeScale3D(FVector(1, 0.25f, 0.5f));
}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ��� �̵��ϰ� �ʹ�.
	// p = p0 + vt
	FVector P = GetActorLocation() + GetActorRightVector() * Speed * DeltaTime;
	SetActorLocation(P);
}

