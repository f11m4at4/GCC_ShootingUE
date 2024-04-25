// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 필요한 컴포넌트 생성
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	// Root 컴포넌트로 설정
	RootComponent = BodyMesh;

	// Static Mesh Data 를 초기화 하고 싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// 성공적으로 로딩이 됐다면
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh 에 데이터를 할당하고 싶다.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// 재질 로딩
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	// 성공적으로 로딩이 됐다면
	if (TempMat.Succeeded())
	{
		// -> BodyMesh 에 데이터를 할당하고 싶다.
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

	// 위로 계속 이동하고 싶다.
	// p = p0 + vt
	FVector P = GetActorLocation() + GetActorRightVector() * Speed * DeltaTime;
	SetActorLocation(P);
}

