
// �����ð��� �ѹ��� ���� ����� �ʹ�.
// �ʿ�Ӽ� : �����ð�, ����ð�, ������


#include "CEnemyGOD.h"
#include "CEnemy.h"

// Sets default values
ACEnemyGOD::ACEnemyGOD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyGOD::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACEnemyGOD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ð��� �ѹ��� ���� ����� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	// -> ����ð��� �����ȴ�.
	CurrentTime += DeltaTime;
	// 2. �����ð��� �����ϱ�
	if (CurrentTime > CreateTime)
	{
		// 3. ���� ����� �ʹ�.
		FActorSpawnParameters param;
		
		GetWorld()->SpawnActor<ACEnemy>(EnemyFactory, GetActorLocation(), FRotator(), param);
		// 4. ����ð��� �ʱ�ȭ �Ǿ�� �Ѵ�.
		CurrentTime = 0;
	}
}

