#pragma once

#include "core.h"
#include "wow_m2action.h"
#include "wow_m2State.h"

class IM2SceneNode;

struct SDynAction
{
	SDynAction() 
		: action(nullptr),  currentIndex(0), currentAnimLoop(0), playedTime(0), finished(true)
	{
	}
	wow_m2Action* action;

	uint32_t currentIndex;			//current anim in action	
	uint32_t currentAnimLoop;
	int32_t playedTime;		//���Ŵ���
	bool finished;
};

class wow_m2FSM
{
public:
	explicit wow_m2FSM(IM2SceneNode* node);
	~wow_m2FSM();

public:
	void onAnimationEnd();

	bool playAction(wow_m2Action* action, uint32_t blendtime = 200);

	const SDynAction& getDynAction() const { return DynAction; }
	SDynAction& getDynAction() { return DynAction; }

	bool isPlaying(wow_m2Action* action) const;

	//state management
	void tick(uint32_t timeSinceStart, uint32_t timeSinceLastFrame);

	//states
	void resetState();
	bool changeState(E_M2_STATES state, bool restart = true);
	E_M2_STATES  getCurrentState() const;
	void revertToPreviousState();
	void clearStates();
	bool setState(E_M2_STATES state, wow_m2State<IM2SceneNode>* m2state);
	wow_m2State<IM2SceneNode>* getState(E_M2_STATES state) const;

	IM2SceneNode* getM2SceneNode() const { return M2SceneNode; }

	void finishAction();
	bool advanceAnimation();
	int16_t getCurrentAnimationIndex() const;

private:
	bool changeState(wow_m2State<IM2SceneNode>* newstate, bool restart = true);

	bool playActionSequence(wow_m2Action* action, uint32_t blendtime = 200);
	bool playActionRandom(wow_m2Action* action, uint32_t blendtime = 200);

	void onAnimationEndSequence();
	void onAnimationEndRandom();
	void onAnimationEndCustom();

private:
	IM2SceneNode*			M2SceneNode;

	wow_m2State<IM2SceneNode>*	States[EMS_COUNT];	
//
	wow_m2State<IM2SceneNode>*	CurrentState;
	wow_m2State<IM2SceneNode>*	PreviousState;
	wow_m2State<IM2SceneNode>*	GlobalState;

	SDynAction		DynAction;
};