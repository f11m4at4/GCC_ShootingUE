// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	FirePosition = CreateDefaultSubobject<USceneComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(BodyMesh);
	// 위치지정
	// > 상대좌표로 지정
	FirePosition->SetRelativeLocation(FVector(0.000000, 0.000000, 80.000000));
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 오른쪽으로 이동하고 싶다.
	// 1. 방향이 필요하다.
	FVector Direction = FVector::RightVector;
	// 2. 이동하고 싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = Direction * 500 * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

