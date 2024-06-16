#pragma once
#include "framework/Delegate.h"
#include "framework/Object.h"

namespace ly
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }

		Delegate<> onStageFinished;

		virtual void StartStage();
		virtual void TickStage(float deltatime);
		void FinishStage();
		bool IsStageFinished() const { return mStageFinished; };
	private:
		World* mWorld;
		bool mStageFinished;
		virtual void StageFinished();

	};
}