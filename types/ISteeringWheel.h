class ISteeringWheel : public UCOM::IUnknown {
public:
	enum STEERING_WHEEL_TYPE {
		LOGITECH_WHEEL_DRIVING_FORCE_PRO = 0,
		LOGITECH_WHEEL_DRIVING_FORCE = 1,
		LOGITECH_WHEEL_GT_FORCE = 2,
		LOGITECH_WHEEL_G25 = 3,
		MS_STEERING_WHEEL = 4,
		NO_STEERING_WHEEL = 5,
	};

	enum SteeringType {
		kGamePad = 0,
		kWheelSpeedSensitive = 1,
		kWheelSpeedInsensitive = 2,
	};

	static inline uint32_t IHandle = 0x666E20;

	virtual void UpdateForces(IPlayer*);
	virtual void ReadInput(float*);
	virtual bool IsConnected();
	virtual STEERING_WHEEL_TYPE GetWheelType();
	virtual SteeringType GetSteeringType();
	virtual bool HasGatedShifter();
	virtual bool IsGatedShifterActive();
	virtual bool HasClutch();
};