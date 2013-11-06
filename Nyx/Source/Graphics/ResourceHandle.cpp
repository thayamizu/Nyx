#include "PCH/PCH.h"
#include "Debug/DebugOutput.h"
#include "Graphics/ResourceHandle.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/lexical_cast.hpp"

namespace Nyx  {

	ResourceHandle::ResourceHandle(std::wstring uuid, const std::shared_ptr<void>& resource)
		: uuid_(uuid), resource_(resource)
	{
	}

}