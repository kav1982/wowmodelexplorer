#pragma once

#include "base.h"
#include "wow_particle.h"
#include "S3DVertex.h"
#include "VertexIndexBuffer.h"
#include <vector>

//������ϵͳ�ṩ���ӳغ�Ӳ������
class IParticleSystemServices
{
public:
	IParticleSystemServices() { BufferParam.clear(); BufferParam.vType = EVT_PCT; }
	virtual ~IParticleSystemServices() {}

public:
	virtual void adjustParticles() = 0;		//ÿ֡������������
	virtual void setParticleDensity(float density) = 0;		//���ӷ����ܶ�
	virtual float getParticleDensity() const = 0;

	virtual u32 getActiveParticlesCount() const = 0;

public:
	SBufferParam		BufferParam;
	std::vector<SVertex_PCT>		Vertices;
};