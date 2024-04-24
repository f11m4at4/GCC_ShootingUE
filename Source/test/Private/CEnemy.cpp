// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"

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
	
	// �¾�� Ÿ�� ������ ���ϰ� �ʹ�.
	FindTargetDirection();
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �̵��ϰ� �ʹ�.
	MoveToTarget();
}

void ACEnemy::FindTargetDirection()
{
	// Ÿ�ٹ����� ���ϰ�
	// dir = target - me
	AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());
	ACPlayer* Target = Cast<ACPlayer>(player);
	Direction = Target->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
}

void ACEnemy::MoveToTarget()
{
	// �� �������� ��� �̵��ϰ� �ʹ�.
	// P = P0 + vt
	FVector P = GetActorLocation() + Direction * Speed * GetWorld()->DeltaTimeSeconds;

	SetActorLocation(P);
}

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
	Destroy();
}

