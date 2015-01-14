#ifndef NYX_CORE_INCLUDED_BOX_H_
#define NYX_CORE_INCLUDED_BOX_H_

namespace nyx {

	template<typename T = float>
	struct box {
		T minX_, maxX_;
		T minY_, minY_;
		T minZ_, maxZ_;
	};

	template<typename T>
	box<T> && make_box(T minX, T maxX, T minY, T maxY, T minZ, T maxZ) {
		return std::move(box { minX, maxX, minY, maxY, minZ, maxZ } );
	}

	template<typename T = float>
	struct corn {
		T			r_;
		T			height_;
		point3<T>	center_;
	};

	template<typename T>
	corn<T> && make_corn(T radius, T height, const point3<T>& center) {
		return std::move(corn{ radius, height, center});
	}


	template<typename T = float>
	struct cylinder {
		T			r_;
		T			height_;
		point3<T>	center_;
	};

	template<typename T>
	corn<T>&& make_cylinder(T radius, T height, const point3<T>& center) {
		return std::move(corn{ radius, height, center });
	}

	template<typename T = float>
	struct sphere{
		T			r_;
		point3<T>	center_;
	};

	template<typename T>
	sphere<T>&& make_sphere(T radius, const point3<T>& center) {
		return std::move(sphere{ radius, center });
	}
}
#endif