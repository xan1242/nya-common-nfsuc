namespace Sim { class IEntity; }
namespace EventSequencer { class IEngine; }

enum SimableType {
	SIMABLE_INVALID = 0,
	SIMABLE_VEHICLE = 1,
	SIMABLE_SMACKABLE = 2,
	SIMABLE_EXPLOSION = 3,
	SIMABLE_HUMAN = 4,
	SIMABLE_WEAPON = 5,
	SIMABLE_NEWTON = 6,
	SIMABLE_SENTRY = 7,
	SIMABLE_FRAGMENT = 8,
};

class IPlayer;
class IRigidBody;
class IModel;
class WWorldPos;
class ISimable : public UCOM::IUnknown {
public:
	static inline uint32_t IHandle = 0x4018C0;

	virtual SimableType GetSimableType(){return SIMABLE_INVALID;}
	virtual void Kill(){}
	virtual bool Attach(UCOM::IUnknown *){return false;}
	virtual bool Detach(UCOM::IUnknown *){return false;}
	virtual const IAttachable::List *GetAttachments(){ return nullptr;}
	virtual void AttachEntity(Sim::IEntity *){}
	virtual void DetachEntity(){}
	virtual IPlayer *GetPlayer(){return nullptr;}
	virtual bool IsPlayer(){return false;}
	virtual bool IsOwnedByPlayer(){return false;}
	virtual Sim::IEntity *GetEntity(){return nullptr;}
	virtual void DebugObject(){}
	virtual HSIMABLE__ *GetOwnerHandle(){return nullptr;}
	virtual ISimable *GetOwner(){return nullptr;}
	virtual bool IsOwnedBy(ISimable *){return false;}
	virtual void SetOwnerObject(ISimable *){}
	virtual const Attrib::Instance *GetAttributes(){return nullptr;}
	virtual const IRigidBody *_GetRigidBody(){return nullptr;}
	virtual IRigidBody *GetRigidBody(){return nullptr;}
	virtual bool IsRigidBodySimple(){return false;}
	virtual bool IsRigidBodyComplex(){return false;}
	virtual const UMath::Vector3 *GetPosition(){return nullptr;}
	virtual void GetTransform(UMath::Matrix4 *){}
	virtual void GetLinearVelocity(UMath::Vector3 *){}
	virtual void GetAngularVelocity(UMath::Vector3 *){}
	virtual unsigned int GetWorldID(){return 0;}
	virtual EventSequencer::IEngine *GetEventSequencer(){return nullptr;}
	virtual void ProcessStimulus(unsigned int){}
	virtual const IModel *_GetModel(){return nullptr;}
	virtual IModel *GetModel(){return nullptr;}
	virtual void SetCausality(HCAUSE__ *, float){}
	virtual HCAUSE__ *GetCausality(){return nullptr;}
	virtual float GetCausalityTime(){return 0.0f;}
};