/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:21:58
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 15:34:04
*/

#include <Core/System/System.hpp>

namespace amaze{
	namespace core{
		System::System(){
			_system_initialized = false;
		}

		System::~System(){
			if(_system_initialized){
				destroy();
			}
		}

		bool System::init(){
			if(!_system_initialized){
				_system_initialized = v_init();
			}

			return _system_initialized;
		}

		bool System::destroy(){
			if(_system_initialized){
				_system_initialized = !v_destroy();
			}

			return !_system_initialized;
		}
	}
}