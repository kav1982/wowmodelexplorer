#pragma once

#include "core.h"
#include "IFileWDT.h"
#include <unordered_map>
#include <map>

class CWDTSceneNode;
class CMapChunk;
class CFileWDT;

//wdt�ĳ�������
class wow_wdtScene
{
public:
	explicit wow_wdtScene(CWDTSceneNode* wdtNode);
	~wow_wdtScene();

public:
	void update();
	void setCameraChunk(CMapChunk* chunk) { CamChunk = chunk; }
	const CMapChunk* getCameraChunk() const { return CamChunk; }

	int32_t getRow() const { return Row; }
	int32_t getCol() const { return Col; }

	void setAdtLoadSize(E_ADT_LOAD size);

	void setCurrentTile(int32_t row, int32_t col);
	void startLoadADT(STile* tile);
	bool processADT();
	bool updateBlocksByCamera();
	void unloadOutBlocks();

	void updateTileTransform(STile* tile);
	bool isTileNeeded(STile* tile) const;		//�Ƿ�����Ҫ���صķ�Χ��

	bool isLoading(STile* tile) const;
	void recalculateTilesNeeded(int32_t row, int32_t col);
	uint32_t getNumBlocks() const;

private:
#ifdef USE_QALLOCATOR
	typedef std::map<STile*, bool, std::less<STile*>, qzone_allocator<std::pair<STile*, bool>>>		T_TileMap;
#else
	typedef std::unordered_map<STile*, bool>		T_TileMap;
#endif

private:
	CWDTSceneNode* WdtSceneNode;
	CFileWDT*	FileWDT;

	//�Ѽ��غͼ����е�tile, falseΪ�����У�trueΪ�Ѽ���
	T_TileMap		TilesMap;

	CMapChunk*			CamChunk;
	CMapChunk*			LastCamChunk;

	int32_t	Row;			//��������row
	int32_t	Col;				//��������col;

	vector2di		Coords[25];
	
	//flags
	uint32_t TileChangeTick;
	bool TileChanging;
	
	E_ADT_LOAD		AdtLoadSize;
};
