/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 15:11:21
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 15:23:04
*/

#ifndef CORE_SYSTEM_HPP
#define CORE_SYSTEM_HPP

namespace amaze{
	namespace core{
		class System{
		public:
			System();
			virtual ~System();

			bool init();
			bool destroy();

		protected:
			virtual bool v_init() = 0;
			virtual bool v_destroy() = 0;

		private:
			bool _system_initialized;
		};
	}
}

#endif // CORE_SYSTEM_HPP
