#pragma once

#include "ISceneNode.h"

//����map�е���գ����գ���Ȼ�������
class ISkySceneNode : public ISceneNode
{
public:
	ISkySceneNode() : ISceneNode(nullptr){ Type = EST_SKY; }

	virtual ~ISkySceneNode() { }

public:

};