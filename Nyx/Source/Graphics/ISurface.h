#ifndef NYX_CORE_INCLUDED_ISURFACE_H_
#define NYX_CORE_INCLUDED_ISURFACE_H_

namespace Nyx {
	class ISurface {
	public:
		ISurface() {}
		~ISurface() {}

	private:
		int imagesize;
		void* surfacebuffer
	};
}
#endif