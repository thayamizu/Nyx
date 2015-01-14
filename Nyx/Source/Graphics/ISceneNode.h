#ifndef NYX_CORE_INCLUDED_ISCENE_NODE_H_
#define NYX_CORE_INCLUDED_ISCENE_NODE_H_
#include "Primitive/Matrix44.h"

namespace nyx
{
	struct scene_node
	{
		virtual ~scene_node() {}
	
		matrix44 world_cordinate_system_;
	};

	struct group_node : public scene_node
	{
		void add_child(scene_node& scene);
	
		void remove_child(scene_node& scene);
	
		void render();
	};


}

#endif