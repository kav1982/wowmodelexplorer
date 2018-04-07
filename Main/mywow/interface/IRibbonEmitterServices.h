#pragma once

#include "base.h"
#include "wow_particle.h"
#include "S3DVertex.h"
#include "VertexIndexBuffer.h"
#include <vector>

//��ribbon�ṩsegment�غ�Ӳ������
class IRibbonEmitterServices
{
public:
	IRibbonEmitterServices() { BufferParam.clear(); BufferParam.vType = EVT_PCT; }
	virtual ~IRibbonEmitterServices() {}

public:
	virtual u32 getActiveSegmentsCount() const = 0;
	
public:
	SBufferParam	BufferParam;
	std::vector<SVertex_PCT>		Vertices;
};