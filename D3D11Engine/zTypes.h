#pragma once
#include "pch.h"

enum zTCam_ClipType {
	ZTCAM_CLIPTYPE_IN,
	ZTCAM_CLIPTYPE_OUT,
	ZTCAM_CLIPTYPE_CROSSING
};

enum zTCam_ClipFlags {
	CLIP_FLAGS_FULL = 63,
	CLIP_FLAGS_NO_FAR = 15
};

#pragma pack (push, 1)	
struct zTBBox3D {
	DirectX::XMFLOAT3	Min;
	DirectX::XMFLOAT3	Max;

	enum zTPlaneClass {
		zPLANE_INFRONT,
		zPLANE_BEHIND,
		zPLANE_ONPLANE,
		zPLANE_SPANNING
	};

	int ClassifyToPlane( float planeDist, int axis ) const {
		if ( planeDist >= ((float*)&Max)[axis] )
			return zPLANE_BEHIND;
		else if ( planeDist <= ((float*)&Max)[axis] )
			return zPLANE_INFRONT;
		else return zPLANE_SPANNING;
	}
};

struct zTPlane {
	float Distance;
	DirectX::XMFLOAT3 Normal;
};
#pragma pack (pop)

class zCWorld;
class zCVob;
class zCCamera;

struct zTRenderContext {
	int ClipFlags;
	zCVob* Vob;
	zCWorld* world;
	zCCamera* cam;
	float distVobToCam;

	// More not needed stuff here
};

struct zCRenderLight {
	int	LightType;
	DirectX::XMFLOAT3	ColorDiffuse;
	DirectX::XMFLOAT3	Position;
	DirectX::XMFLOAT3	Direction;
	float Range;
	float RangeInv;
	DirectX::XMFLOAT3 PositionLS;
	DirectX::XMFLOAT3 DirectionLS;
	float Dir_approxFalloff;
};

struct zCRenderLightContainer {
	zCRenderLight			LightList[8];
	int						NumLights;

private:
	int	DoPrelight;
	int	DoSmoothPrelit;
	float PreLightDist;
	DirectX::XMFLOAT4X4 MatObjToCam;
};

enum zTRnd_AlphaBlendFunc {
	zRND_ALPHA_FUNC_MAT_DEFAULT = 0,
	zRND_ALPHA_FUNC_NONE = 1,
	zRND_ALPHA_FUNC_BLEND = 2,
	zRND_ALPHA_FUNC_ADD = 3,
	zRND_ALPHA_FUNC_SUB = 4,
	zRND_ALPHA_FUNC_MUL = 5,
	zRND_ALPHA_FUNC_MUL2 = 6,
	zRND_ALPHA_FUNC_TEST = 7,
	zRND_ALPHA_FUNC_BLEND_TEST = 8
};

struct float4;
struct zColor {
	union {
		struct bgra {
			uint8_t b;
			uint8_t g;
			uint8_t r;
			uint8_t alpha;
		} bgra;
		DWORD dword;
	};
	zColor() {}
	zColor( uint8_t b, uint8_t g, uint8_t r, uint8_t a = 255 ) {
		bgra.b = b;
		bgra.g = g;
		bgra.r = r;
		bgra.alpha = a;
	}
	bool IsWhite() {
		return dword == 4294967295;
	}
	float4 ToFloat4() {
		return float4( (float)bgra.r / 255.f, (float)bgra.g / 255.f, (float)bgra.b / 255.f, (float)bgra.alpha / 255.f );
	}
};
static zColor zCOLOR_WHITE = zColor( 255, 255, 255, 255 );

struct zTRndSimpleVertex {
	float2 pos;
	float z;
	float2 uv;
	zColor color;
};

struct zVEC2 {
public:
	union {
		float2 pos;
		float v[2];
	};
};

template <class T>
class zCList {
public:
	T* data;
	zCList* next;
};

template <class T>
class zList {
public:
	int (*cmp)(T* ele1, T* ele2);
	int count;
	T* last;
	T* root;
};
