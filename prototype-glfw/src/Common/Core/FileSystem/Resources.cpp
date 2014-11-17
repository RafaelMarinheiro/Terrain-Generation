/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-14 18:04:07
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-14 18:06:47
*/

#include <Core/FileSystem/Resources.hpp>

namespace amaze{
	namespace core{

		std::string Resources::pathForResource(const std::string & resource){
			return "resources/" + resource;
		}
	}
}