// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CBullet.h"

// Sets default values
ACEnemy::ACEnemy()
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

	// BodyMesh�� �浹������ ������
	BodyMesh->SetCollisionProfileName(TEXT("OverlapAll"));

	// �ٸ� ��ü�� �ε����� �� �ʵ� �װ� ���� ����
	BodyMesh->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindTargetDirection();
	// �̵��ϰ� �ʹ�.
	//MoveToTarget();
	// �����ð��� �ѹ��� �Ѿ��� ����� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	CurrentTime += DeltaTime;
	// 2. �����ð��� �������ϱ�
	// ��, 6���� -> ���� ���� ������ �Ѿ� ������ 6���� �۴ٸ�
	if (CurrentBulletCount < BulletCount && CurrentTime > CreateTime)
	{
		// 3. �Ѿ��� �߻��ϰ� �ʹ�.
		Fire();
		CurrentTime = 0;
		// ���� �Ѿ˰��� ����
		CurrentBulletCount++;
	}
}

void ACEnemy::FindTargetDirection()
{
	// Ÿ�ٹ����� ���ϰ�
	// dir = target - me
	AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());
	ACPlayer* Target = Cast<ACPlayer>(player);
	Direction = Target->GetActorLocation() - GetActorLocation();
	Direction.Normalize();

	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(GetActorForwardVector(), Direction);
	SetActorRotation(Rot);
}

void ACEnemy::MoveToTarget()
{
	// �� �������� ��� �̵��ϰ� �ʹ�.
	// P = P0 + vt
	//FVector Dir = GetActorTransform().TransformVector(FVector::UpVector);
	FVector P = GetActorLocation() + GetActorUpVector() * Speed * GetWorld()->DeltaTimeSeconds;

	SetActorLocation(P);
}

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
	Destroy();
}

void ACEnemy::Fire()
{
	float thetaRange = 360.0f / BulletCount;
	// �Ѿ� ������ŭ ����� �ʹ�.
	// �Ѿ��� ��ġ�� ��ġ�� ���ϰ� �ʹ�.
	FVector Location = GetActorLocation();
	// 1. Y, Z ���� ���ϰ� �ʹ�.
	// 2. Y = R * Cos(theta)
	float theta = FMath::DegreesToRadians(thetaRange * CurrentBulletCount);
	Location.Y += Distance * FMath::Cos(theta);
	// 3. Z = R * Sin(Theta)
	Location.Z += Distance * FMath::Sin(theta);

	FRotator Rot;
	Rot.Roll = -thetaRange * CurrentBulletCount;
	// 4. Y, Z �� ��ġ�� �����Ű�� �ʹ�.

	// �Ѿ��� �߻��ϰ� �ʹ�.
	// �ʿ�Ӽ� : �Ѿ˰���
	// 1. �ѾӰ��忡�� �Ѿ��� ����� �ʹ�.
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(BulletFactory, Location, Rot, param);
}