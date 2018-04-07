#pragma once

#include "core.h"
#include "IResourceCache.h"
#include "wow_adt_structs.h"

#define TILENUM		64

class IMemFile;
class IFileADT;
class CMapEnvironment;

struct STile	
{
	STile() : fileAdt(nullptr){ row = col = 0 ; }
	u8  row;
	u8  col;
	IFileADT*	fileAdt;
};

//WDT����һ���ͼ�Ļ�����Ϣ��WDT�������Tile, ÿ��Tile���ܰ���ADT�ļ���
//������ADT�ļ���Tile���ǲ�ʹ��Ҳ���ɼ�
//ADT�ļ��������Tile�ľ�����Ϣ: ģ��,����,����...
//WDL�ļ�����һ���ͷֱ��ʵĵ���ģ�ͣ�������������Զ���ĵ�������
class IFileWDT : public IReferenceCounted<IFileWDT>
{
protected:
	virtual ~IFileWDT() { }

public:
	IFileWDT() 
	{
		WmoFileNameIndices = nullptr;
		WmoFileNameBlock = nullptr;
		WmoInstances = nullptr;
		TileOffsets = nullptr;

		::memset(GlobalWmoFileName, 0, QMAX_PATH);
		::memset(&GlobalWmoInstance, 0, sizeof(SWmoInstance));

		TextureInfos = nullptr;
		TextureFileNameBlock = nullptr;

		NumTextures = NumWmoFileNames = NumWmoInstance = 0;
	}
	
public:
	struct SWmoInstance
	{
		u32 wmoIndex;
		s32 id;
		vector3df pos;
		vector3df dir;
		matrix4		mat;
		aabbox3df		box;
		f32		scale;
	};

public:
	virtual bool loadFile(IMemFile* file, s32 mapid) = 0;
	virtual bool loadFileSimple(IMemFile* file, s32 mapid) = 0;		//only tiles

	virtual CMapEnvironment*	 getMapEnvironment() const  = 0;
	virtual STile* getTile(u8 row, u8 col) = 0;

public:
	//wmo
	u32		NumWmoFileNames;
	u32		NumWmoInstance;
	u32		NumTextures;

	u32*		WmoFileNameIndices;
	c8*		WmoFileNameBlock;
	
	SWmoInstance*		WmoInstances;
	s32*		TileOffsets;
	 
	//tex
	ADT::TXBT*	TextureInfos;
	c8* TextureFileNameBlock;

	c8		GlobalWmoFileName[QMAX_PATH];
	SWmoInstance		GlobalWmoInstance;

	std::vector<STile>	Tiles;
};
