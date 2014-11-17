/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:35:06
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 16:17:32
*/

#include <Core/System/SystemManager.hpp>

namespace amaze{
	namespace core{
		bool SystemManager::initSystem(const std::string & systemName, System * system){
			_loaded_systems[systemName] = system;
			return system->init();
		}

		bool SystemManager::destroySystem(const std::string & systemName){
			System * system = _loaded_systems[systemName];

			bool ret = system->destroy();

			_loaded_systems.erase(systemName);
			delete system;

			return ret;
		}
	
		System * SystemManager::getSystem(const std::string & systemName){
			return _loaded_systems[systemName];
		}

		SystemManager & SystemManager::instance(){
			static SystemManager * singleton = new SystemManager();

			return *singleton;
		}
	}
}