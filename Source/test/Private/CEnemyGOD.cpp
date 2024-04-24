
// 일정시간에 한번씩 적을 만들고 싶다.
// 필요속성 : 생성시간, 경과시간, 적공장


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

	// 일정시간에 한번씩 적을 만들고 싶다.
	// 1. 시간이 흘렀으니까
	// -> 경과시간이 누적된다.
	CurrentTime += DeltaTime;
	// 2. 생성시간이 됐으니까
	if (CurrentTime > CreateTime)
	{
		// 3. 적을 만들고 싶다.
		FActorSpawnParameters param;
		
		GetWorld()->SpawnActor<ACEnemy>(EnemyFactory, GetActorLocation(), FRotator(), param);
		// 4. 경과시간이 초기화 되어야 한다.
		CurrentTime = 0;
	}
}

