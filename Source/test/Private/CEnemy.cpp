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

	// BodyMesh의 충돌설정을 해주자
	BodyMesh->SetCollisionProfileName(TEXT("OverlapAll"));

	// 다른 물체와 부딪혔을 때 너도 죽고 나도 죽자
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
	// 이동하고 싶다.
	//MoveToTarget();
	// 일정시간에 한번씩 총알을 만들고 싶다.
	// 1. 시간이 흘렀으니까
	CurrentTime += DeltaTime;
	// 2. 일정시간이 지났으니까
	// 단, 6개만 -> 만약 현재 생성된 총알 갯수가 6보다 작다면
	if (CurrentBulletCount < BulletCount && CurrentTime > CreateTime)
	{
		// 3. 총알을 발사하고 싶다.
		Fire();
		CurrentTime = 0;
		// 현재 총알갯수 증가
		CurrentBulletCount++;
	}
}

void ACEnemy::FindTargetDirection()
{
	// 타겟방향을 구하고
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
	// 그 방향으로 계속 이동하고 싶다.
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
	// 총알 갯수만큼 만들고 싶다.
	// 총알이 배치될 위치를 구하고 싶다.
	FVector Location = GetActorLocation();
	// 1. Y, Z 값을 구하고 싶다.
	// 2. Y = R * Cos(theta)
	float theta = FMath::DegreesToRadians(thetaRange * CurrentBulletCount);
	Location.Y += Distance * FMath::Cos(theta);
	// 3. Z = R * Sin(Theta)
	Location.Z += Distance * FMath::Sin(theta);

	FRotator Rot;
	Rot.Roll = -thetaRange * CurrentBulletCount;
	// 4. Y, Z 를 위치에 적용시키고 싶다.

	// 총알을 발사하고 싶다.
	// 필요속성 : 총알공장
	// 1. 총앙공장에서 총알을 만들고 싶다.
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(BulletFactory, Location, Rot, param);
}