#include "framework/Core.h"
#include "gameplay/GameStage.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: mWorld{ world }, mStageFinished{ false }
	{

	}
	void GameStage::StartStage()
	{
		LOG("stage started");
	}
	void GameStage::TickStage(float deltatime)
	{
	}
	void GameStage::FinishStage()
	{
		onStageFinished.Broadcast();
		mStageFinished = true;
		StageFinished();
	}
	void GameStage::StageFinished()
	{
		LOG("stage finished");
	}
}