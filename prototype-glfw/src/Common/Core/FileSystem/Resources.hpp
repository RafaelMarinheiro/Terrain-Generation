/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 17:58:46
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 18:06:25
*/

#ifndef CORE_RESOURCES_HPP
#define CORE_RESOURCES_HPP

#include <Core/System/System.hpp>

#include <string>

namespace amaze{
	namespace core{
		class Resources{
		public:
			static std::string pathForResource(const std::string & resource);
		};
	}
}


#endif // CORE_RESOURCES_HPP
