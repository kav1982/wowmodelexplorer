#pragma once

#include "base.h"
#include "SMaterial.h"

class IPixelShader;

//���ݲ�ͬ��material���ò�ͬ����Ⱦ״̬
class IMaterialRenderer
{
public:
	IMaterialRenderer() : NumPass(1) {}
	virtual ~IMaterialRenderer() {}

public:
	virtual void OnSetMaterial( E_VERTEX_TYPE vType, const SMaterial& material, bool resetAllRenderStates) = 0;

	//for fp
	uint32_t getNumPasses() const { return NumPass; }

	virtual void OnRender(const SMaterial& material, uint32_t pass) {}

public:
	SRenderStateBlock		MaterialBlock;

protected:
	uint32_t		NumPass;
};

