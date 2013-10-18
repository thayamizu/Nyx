#ifndef NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_
#define NYX_CORE_INCLUDED_GRAPHICS_DEVICE_H_

namespace Nyx {

	class GraphicsDevice
	{
	public:
		GraphicsDevice();
		GraphicsDevice(int);
		bool Initialize();
		bool Finalize();

		void SetWidownMode(bool isWindowed);
		void SetSamplerState();
		void GetSamplerState();
		void SetClientRect();
		void GetClientRect();
		void GetSurface();
		void invalidateState();
		void Reset();
		void Preset();
		void Clear();
	private:
		struct PImpl;
		std::shared_ptr<PImpl> pimpl_;
	};

}
#endif