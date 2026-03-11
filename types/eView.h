enum CameraMoverTypes {
	CM_NONE_TYPE = 0x0,
	CM_DRIVE_CUBIC = 0x1,
	CM_DEBUG_WORLD = 0x2,
	CM_ROAD_EDITOR = 0x3,
	CM_ORBIT_CAR = 0x4,
	CM_REAR_VIEW_MIRROR = 0x5,
	CM_TRACK_CAR = 0x6,
	CM_TRACK_COP = 0x7,
	CM_MAX = 0x8,
	CM_SELECT_CAR = 0x9,
	CM_STILL = 0xA,
	CM_RACE_START = 0xB,
	CM_ZONE_FREEZE = 0xC,
	CM_ZONE_PREVIEW = 0xD,
	CM_AUTO_PILOT = 0xE,
	CM_ICE = 0xF,
	CM_ANIMATION_CONTROLLER = 0x10,
	CM_COP_VIEW = 0x11,
	CM_ANIMATION_ENTITY = 0x12,
	CM_SHOWCASE = 0x13,
	CM_PIP = 0x14,
	CM_CAR_FRAMERATE_MOVER = 0x15,
	CM_LAST_MOVER_TYPE = 0x14,
};

class eViewPlatInfo;
class eViewPlatInterface {
public:
	eViewPlatInfo *PlatInfo;
	int ID;

	static inline auto GetScreenPosition = (void(__thiscall*)(eViewPlatInterface*, bVector3* screen_position, const bVector3* world_position))0x744A50;
};

namespace DC {
	template<typename T>
	class cDampedVar {
		float mSmoothTime;
		T mVel;
		T mValue;
	};
}

namespace CARP {
	struct CollisionSurface
	{
		uint8_t fSurface;
		uint8_t fFlags;
	};
}

class WSurface : public CARP::CollisionSurface {};

class WWorldPos {
public:
	enum FailStrategy {
		kFail_KeepValid = 0,
		kFail_Invalidate = 1,
	};

	UMath::Vector3 fPt0;
	float fYOffset;
	UMath::Vector3 fPt1;
	const Attrib::Collection *pSurface;
	UMath::Vector3 fPt2;
	float fHeight;
	UMath::Vector3 fNormal;
	WSurface fSurface;
	unsigned int fFaceValid;
	bool mCacheable;

	WWorldPos() {
		memset(this,0,sizeof(*this));
		fYOffset = 0.025;
	}

	void SetTolerance(float liftAmount) {
		fYOffset = liftAmount;
	}

	static inline auto Update = (bool(__thiscall*)(WWorldPos*, UMath::Vector3* pos, UMath::Vector4* dest, bool usecache, const WCollider* collider, FailStrategy failStrategy))0x8969B0;
};
static_assert(offsetof(WWorldPos, fHeight) == 0x2C);

class WaveData3 {
public:
	bVector3 frequency;
	bVector3 amplitude;
};

class CameraParams {
public:
	bMatrix4 Matrix;
	bVector3 Position;
	bVector3 Direction;
	bVector3 Target;
	WaveData3 PosNoise[4];
	WaveData3 RotNoise[4];
	bVector3 PosNoise2Value;
	bVector3 RotNoise2Value;
	float FocalDistance;
	float DepthOfField;
	float DOFFalloff;
	float DOFMaxIntensity;
	float NearZ;
	float FarZ;
	float LB_height;
	float SimTimeMultiplier;
	bVector4 FadeColor;
	float TargetDistance;
	uint16_t FieldOfView;
	uint16_t PaddingAngle;
	bVector2 PaddingVector2;
};

class CameraBlender {
public:
	CameraParams mBlendKey;
	bool mBlendingActive;
	bool mSpringBlend;
	DC::cDampedVar<float> mBlend;
	bVector3 mPosition;
	bVector3 mTarget;
	bVector3 mVelocity;
	bVector3 mTargetVelocity;
	float mFOV;
	DC::cDampedVar<float> mSmoothTime;
	DC::cDampedVar<bVector3> mSPosition;
	DC::cDampedVar<bVector3> mSTarget;
	DC::cDampedVar<float> mSFOV;
};

class Camera {
public:
	CameraParams CurrentKey;
	CameraParams PreviousKey;
	CameraParams VelocityKey;
	bool bClearVelocity;
	float ElapsedTime;
	int LastUpdateTime;
	int LastDisparateTime;
	int RenderDash;
	float NoiseIntensity;
	CameraBlender mCameraBlender;
	bool mEnableBlender;

	static inline auto SetCameraMatrix = (void(__thiscall*)(Camera*, const bMatrix4* m, float fTime))0x4DCB70;
};
static_assert(offsetof(Camera, CurrentKey.FarZ) == 0x1A4);

class WCollider;
class Camera;
class View;
class eView;
class CameraAnchor;
class CameraMover : public bTNode<CameraMover> {
public:
	uint8_t _0[0xC];
	CameraMoverTypes Type;
	int ViewID;
	int Enabled;
	View *pView;
	Camera *pCamera;
	int RenderDash;
	WCollider *mCollider;
	WWorldPos mWPos;
	float fAccumulatedClearance;
	float fAccumulatedAdjust;
	float fSavedAdjust;
	DC::cDampedVar<float> mHeightAdjust;
	bVector3 vSavedForward;
	float mZoom;
	bVector2 mCameraRotation;

	virtual void _dtor();
	virtual void Update(float);
	virtual void Render(eView *);
	virtual const CameraAnchor *GetAnchor();
	virtual void SetLookBack(bool);
	virtual void SetLookbackSpeed(float);
	virtual void SetPovType(int);
	virtual int16_t GetPOVType();
	virtual bool IsHoodPOV();
	virtual bool IsOutsidePOV();
	virtual bool IsRenderCarPOV();
	virtual bool IsLookBackPOV();
	virtual float MinDistToWall();
	virtual void SetDamperScale(float);
	virtual void SetPOVScale(float);
	virtual void SetCameraShakeScale(float);
	virtual void SetCameraProximityShakeVolume(float);
	virtual void SetCameraShakeAdd(float);
	virtual void SetFixedCam(bool);
	virtual void ResetState();
	virtual void Enable();
	virtual void Disable();
	virtual const bVector3 *GetTarget();
};
static_assert(offsetof(CameraMover, pView) == 0x24);
static_assert(offsetof(CameraMover, pCamera) == 0x28);

class eDynamicLightContext;
class eView : public eViewPlatInterface {
public:
	char *Name;
	char Active;
	char LetterBox;
	char pad0;
	char pad1;
	float H;
	float NearZ;
	float FarZ;
	float FovBias;
	float FovDegrees;
	uint16_t FovbAngle;
	int BlackAndWhiteMode;
	int PixelMinSize;
	bVector3 ViewDirection;
	Camera* pCamera;
	uint8_t _[0x3C];
	//bTList<CameraMover> CameraMoverList;
	//eDynamicLightContext *WorldLightContext;
};
static_assert(sizeof(eView) == 0x80);

inline auto eViews = (eView*)0x12751E0;