// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "CBullet.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	FirePosition = CreateDefaultSubobject<USceneComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(BodyMesh);
	// ��ġ����
	// > �����ǥ�� ����
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
	// ���������� �̵��ϰ� �ʹ�.
	// 1. ������ �ʿ��ϴ�.
	FVector Direction(0, h, v);

	// 2. �̵��ϰ� �ʹ�.
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

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayer::Fire);
}

void ACPlayer::Horizontal(float value)
{
	h = value;
}

void ACPlayer::Vertical(float value)
{
	v = value;
}

// ����ڰ� �߻��ư�� ������ 
void ACPlayer::Fire()
{
	// �Ѿ��� �߻��ϰ� �ʹ�.
	// �ʿ�Ӽ� : �Ѿ˰���
	// 1. �ѾӰ��忡�� �Ѿ��� ����� �ʹ�.
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(BulletFactory, GetActorLocation(), FRotator::ZeroRotator, param);
}

