#ifndef NYX_CORE_INCLUDED_RECORD_SET_H_
#define NYX_CORE_INCLUDED_RECORD_SET_H_
#include <vector>
#include "Utility/Type.h"
#include "Utility/Common.h"

namespace nyx
{
	namespace detail
	{
		class field
		{
		public:

			field()
				:fieldName_(""), fieldType_(""), fieldValue_("")
			{

			}
			field(const std::string& fieldName, const std::string& fieldType, const std::string& fieldValue)
				:fieldName_(fieldName), fieldType_(fieldType), fieldValue_(fieldValue)
			{

			}
			operator int() {
				return nyx::to_int(fieldValue_);
			}
		
			operator char() {
				return nyx::to_char(fieldValue_);
			}
			
			operator float() {
				return nyx::to_float(fieldValue_);
			}

			operator double() {
				return nyx::to_double(fieldValue_);
			}

			void set_name(char* fieldName) {
				fieldName_ = fieldName;
			}

			const char *get_name() {
				fieldName_.c_str();
			}
			const char *get_type() {
				return fieldType_.c_str();
			}
			
			const char *get_value() {
				return fieldValue_.c_str();
			}
		
			bool is_null() {
				return fieldValue_.c_str() == nullptr;
			}
		private:
			std::string fieldName_;
			std::string fieldType_;
			std::string fieldValue_;
		};

		typedef std::vector<detail::field>	record;
	}

	typedef std::vector<detail::record> record_set;
}
#endif