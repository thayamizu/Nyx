#ifndef NYX_CORE_INCLUDED_DIRECT_SHOW_DEFINITION_H_
#define NYX_CORE_INCLUDED_DIRECT_SHOW_DEFINITION_H_
#include <boost/intrusive_ptr.hpp>
#include <dshow.h>
#include <objbase.h>
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "strmiids.lib")

namespace nyx {
	///
	typedef boost::intrusive_ptr<IMediaControl> IMediaControlPtr;


	///
	typedef boost::intrusive_ptr<IMediaEventEx> IMediaEventExPtr;


	///
	typedef boost::intrusive_ptr<IGraphBuilder> IGraphBuilderPtr;


	///
	typedef boost::intrusive_ptr<IVideoWindow>  IVideoWindowPtr;


	///
	typedef boost::intrusive_ptr<IBaseFilter>  IBaseFilterPtr;


	///
	typedef boost::intrusive_ptr<IVMRWindowlessControl>  IVMRWindowlessControlPtr;


	///
	typedef boost::intrusive_ptr<ICaptureGraphBuilder2>  ICaptureGraphBuilder2Ptr;
}

#endif