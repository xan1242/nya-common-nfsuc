namespace Sim {
	enum State {
		STATE_NONE = 0,
		STATE_INITIALIZING = 1,
		STATE_ACTIVE = 3,
		STATE_IDLE = 4,
	};

	inline auto Exists = (bool(*)())0x7B6050;
	inline auto GetTime = (float(*)())0x7B61A0;
	inline auto GetTimeMicroseconds = (uint64_t(*)())0x7B61B0;
	inline auto GetState = (State(*)())0x7B6060;
}

class SimSystem;

namespace Sim {
	namespace Internal {
		inline auto& mSystem = *(SimSystem**)0x1278FFC;
	}
}