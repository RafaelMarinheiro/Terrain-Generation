/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:14:28
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 16:15:11
*/

#ifndef CORE_SYSTEM_MANAGER_HPP
#define CORE_SYSTEM_MANAGER_HPP

#include <Core/System/System.hpp>
#include <map>
#include <string>

namespace amaze{
	namespace core{
		class SystemManager{
		public:
			bool initSystem(const std::string & systemName, System * system);
			bool destroySystem(const std::string & systemName);
		
			System * getSystem(const std::string & systemName);

			static SystemManager & instance();

		private:
			std::map<std::string, System* > _loaded_systems; 
		};
	}
}

#endif // CORE_SYSTEM_MANAGER_HPP
