#include "PCH/PCH.h"
#include "Debug/DebugOutput.h"
#include "Graphics/ResourceHandle.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/lexical_cast.hpp"

namespace Nyx  {

	ResourceHandle::ResourceHandle(size_t bufferSize, std::wstring guid, std::shared_ptr<void> resource)
		: bufferSize_(bufferSize), uuid_(L""), resource_(resource)
	{
		using namespace boost;
		using namespace boost::uuids;

		try {
			auto guid = random_generator()();
			uuid_ = lexical_cast<std::wstring>(guid);
		}
		catch (std::exception e) {
			DebugOutput::Trace("bad cast[%s:%s]", __FILE__, __LINE__);
			throw e;
		}
	}

}