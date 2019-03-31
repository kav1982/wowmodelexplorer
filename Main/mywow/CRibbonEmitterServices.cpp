#include "stdafx.h"
#include "CRibbonEmitterServices.h"
#include "mywow.h"

CRibbonEmitterServices::CRibbonEmitterServices( uint32_t poolQuota, uint32_t bufferQuota )
	: PoolQuota(poolQuota), BufferQuota(bufferQuota)
{
	SegmentPool.allocateAll(PoolQuota);

	createBuffer();
}

CRibbonEmitterServices::~CRibbonEmitterServices()
{
	g_Engine->getHardwareBufferServices()->destroyHardwareBuffers(BufferParam);
	BufferParam.destroy();
}

void CRibbonEmitterServices::createBuffer()
{
	BufferParam.clear();
	BufferParam.vType = EVT_PCT;

	uint32_t vsize = BufferQuota * 2;							//ÿ��segment 2 ������

	//vertex buffer
	Vertices.resize(vsize);
	BufferParam.vbuffer0 = new CVertexBuffer(false);
	BufferParam.vbuffer0->set(Vertices.data(), EST_PCT, vsize, EMM_DYNAMIC);
	g_Engine->getHardwareBufferServices()->createHardwareBuffers(BufferParam);
}

void CRibbonEmitterServices::updateVertices( uint32_t numVertices )
{
	if (!numVertices)
		return;

	g_Engine->getHardwareBufferServices()->updateHardwareBuffer(BufferParam.vbuffer0, numVertices);
}

RibbonSegment* CRibbonEmitterServices::getSegment()
{
	return SegmentPool.get();
}

void CRibbonEmitterServices::putSegment( RibbonSegment* s )
{
	SegmentPool.put(s);
}
