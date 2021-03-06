#ifndef _CWORLD_H
#define _CWORLD_H
#include <vector>
#include "../common/FileStream.h"

class CWorld///Handler for RSW files
{
	public:
		struct QuadTreeNode
		{
			float fMax[3];
			float fMin[3];
			float fHalf[3];//HalfSize
			float fCenter[3];
			int32_t lChildIndex[4];
		};

		enum ObjType
		{
			OBJECT_MODEL = 1,
			OBJECT_LIGHT,
			OBJECT_SOUND,
			OBJECT_EFFECT
		};

		struct ObjModel
		{
			char sName[40];
			int32_t lAnimType;
			float fAnimSpeed;
			int32_t lBlockType;
			char sModel[80];//RSM filename
			char sNode[80];
			float fPos[3];
			float fRot[3];
			float fScale[3];
		};

		struct ObjLight
		{
			char sName[80];
			float fPos[3];
			int32_t lRGBA[3];
			float fRange;
		};

		struct ObjSound
		{
			char sName[80];
			char sWavName[80];//what
			float fPos[3];
			float fVol;
			int32_t lWidth;
			int32_t lHeight;
			float fRange;
			float fCycle;
		};

		struct ObjEffect
		{
			char sName[80];
			float fPos[3];
			int32_t lType;
			float fEmitSpeed;
			float fParam[4];
		};

		struct Object
		{
			ObjType type;//indicates which type of Object it is
			union
			{
				ObjModel  model;
				ObjLight  light;
				ObjSound  sound;
				ObjEffect effect;
			};
		};

		CWorld(sf::String sFile);
		CWorld(FileStream &flstream);
		virtual ~CWorld();

		const bool IsValid() const;
		const char* GetIniName() const;
		const char* GetGndName() const;
		const char* GetGatName() const;
		const char* GetScrName() const;

		const Object& GetObject(uint32_t dwIndex) const;
		const QuadTreeNode* GetNode(uint32_t dwIndex) const;

		const uint32_t GetObjectCount() const;

	private:
		bool bValid;
		uint16_t wVersion;
		char sIni[40];//??
		char sGnd[40];
		char sGat[40];
		char sScr[40];//??

		struct _water
		{
			float fLevel;
			int32_t lType;
			float fWaveHeight;
			float fWaveSpeed;
			float fWavePitch;
			int32_t lAnimSpeed;
		} water;

		struct _light
		{
			int32_t lLongitude;
			int32_t lLatitude;
			float fDiffuseColor[3];
			float fAmbientColor[3];
		} light;

		struct _ground
		{
			int32_t lTop;
			int32_t lBottom;
			int32_t lLeft;
			int32_t lRight;
		} ground;
		std::vector<Object> vObjects;
		QuadTreeNode* pQuadTree;//Array because the number of elements needed is constant

		void construct(FileStream &flstream);
		void fetchQuadTree(FileStream &flstream, uint32_t dwLevel, uint32_t &i);

};

#endif//_CWORLD_H
