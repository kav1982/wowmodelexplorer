#pragma once

#include "core.h"

class ISceneNode;
class ICamera;
class ISceneRenderer;
struct SRenderUnit;

//�Ȱ��������������࣬�ٰ�material���ͷ���
class ISceneRenderServices
{
public:
	ISceneRenderServices() : SCENE_SCALE(3.0f), CurrentUnit(nullptr)
	{
		ClipDistance = 1000.0f;
		ModelLodBias = 0;
		TerrainLodBias = 0;
		ObjectVisibleDistance = 24;
		M2InvisibleTickDistance = 30;
		M2SlowTickStart = 0.5f;
		AdtLoadSize = EAL_3X3;
	}
	virtual ~ISceneRenderServices() 	{}

	//�����������ű����� ���Σ����������壬���
	const float SCENE_SCALE;

public:
	const SRenderUnit* getCurrentUnit() const { return CurrentUnit; }

	//scene
	void setModelLodBias(int32_t lodbias) { ModelLodBias = lodbias; }
	int32_t getModelLodBias() const { return ModelLodBias; }

	void setTerrainLodBias(int32_t lodbias) { TerrainLodBias = lodbias; }
	int32_t getTerrainLodBias() const { return TerrainLodBias; }

	//������С�����ɿɼ� -> alpha ->���ɼ�
	void setObjectVisibleDistance(float distance) { ObjectVisibleDistance = distance; }
	float getObjectVisibleDistance() const { return ObjectVisibleDistance; }
	float getObjectAlphaDistance() const { return ObjectVisibleDistance * 0.8f; }

	void setM2InvisibleTickDistance(float distance) { M2InvisibleTickDistance = distance; }
	float getM2InvisibleTickDistance() const { return M2InvisibleTickDistance; }
	float getM2SlowTickBegin() const { return M2SlowTickStart; }

	//�����clip����
	float getClipDistance() const { return ClipDistance; }
	void setClipDistance(float distance) { ClipDistance = distance; }

	E_ADT_LOAD getAdtLoadSize() const { return AdtLoadSize; }
	void setAdtLoadSize(E_ADT_LOAD adt);

	void registerAdtLoadSizeChanged(IAdtLoadSizeChangedCallback* callback);
	void removeAdtLoadSizeChanged(IAdtLoadSizeChangedCallback* callback);

protected:
	int32_t		ModelLodBias;
	int32_t		TerrainLodBias;
	float		ObjectVisibleDistance;		//����/�뾶������������ֵʱ���岻�ɼ�
	float		M2SlowTickStart;				//
	float		M2InvisibleTickDistance;		//����/�뾶����, ������ֵʱm2����tick
	float		ClipDistance;
	E_ADT_LOAD		AdtLoadSize;

	const SRenderUnit*			CurrentUnit;

	typedef std::list<IAdtLoadSizeChangedCallback*, qzone_allocator<IAdtLoadSizeChangedCallback*>  > T_AdtLoadSizeChangedList;
	T_AdtLoadSizeChangedList	AdtLoadSizeChangedList;

};

inline void ISceneRenderServices::setAdtLoadSize( E_ADT_LOAD adt )
{
	if (AdtLoadSize != adt)
	{
		AdtLoadSize = adt;
		for (T_AdtLoadSizeChangedList::const_iterator itr = AdtLoadSizeChangedList.begin(); itr != AdtLoadSizeChangedList.end(); ++itr)
		{
			(*itr)->OnAdtLoadSizeChanged(AdtLoadSize);
		}
	}
}

inline void ISceneRenderServices::registerAdtLoadSizeChanged( IAdtLoadSizeChangedCallback* callback )
{
	if (std::find(AdtLoadSizeChangedList.begin(), AdtLoadSizeChangedList.end(), callback) == AdtLoadSizeChangedList.end())
	{
		AdtLoadSizeChangedList.push_back(callback);
	}
}

inline void ISceneRenderServices::removeAdtLoadSizeChanged( IAdtLoadSizeChangedCallback* callback )
{
	AdtLoadSizeChangedList.remove(callback);
}

