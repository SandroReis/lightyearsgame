#include "Enemy/Boss.h"
#include "Enemy/BossStage.h"
#include "framework/SoundSystem.h"
#include "framework/World.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	BossStage::BossStage(World* world)
		: GameStage{ world }
	{

	}
	void BossStage::StartStage()
	{
		SoundSystem::Get().PlayMusic("SpaceShooterRedux/sounds/music/Space-Music2_1.ogg");
		weak<Boss> boss = GetWorld()->SpawnActor<Boss>();
		auto windowSize = GetWorld()->GetWindowSize();
		boss.lock()->SetActorLocation({ windowSize.x / 2.f, 200.f });
		boss.lock()->onActorDestroy.BindAction(GetWeakRef(), &BossStage::BossDestroyed);
	}
	void BossStage::BossDestroyed(Actor* bossActor)
	{
		FinishStage();
	}
}