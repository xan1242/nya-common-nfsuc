class RacePreparationInfo;

class IRacer : public UCOM::IUnknown {
public:
	static inline uint32_t IHandle = 0x402230;

	virtual void PrepareForRace(const RacePreparationInfo*);
	virtual void StartRace(DriverStyle);
	virtual void QuitRace();
	virtual bool GaveHeadStart();
};