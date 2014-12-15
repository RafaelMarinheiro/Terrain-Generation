/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 06:23:05
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 01:06:48
*/

#ifndef GL_G_BUFFER_HPP
#define GL_G_BUFFER_HPP

#include <Core/GL/OpenGL.hpp>

namespace amaze{
	namespace gl{
		class GBuffer{
		public:
			enum GBufferTextureType{
				GBUFFER_TEXTURE_TYPE_POSITION,
				GBUFFER_TEXTURE_TYPE_NORMAL,
				GBUFFER_TEXTURE_TYPE_ALBEDO,
				GBUFFER_TEXTURE_TYPE_MATERIAL,
				GBUFFER_NUM_TEXTURES
			};

			void init(unsigned int windowWidth, unsigned int windowHeight);
			void bindForWriting();
			void bindForSkyMapRendering();
			void bindForReading();
			void setReadBuffer(GBufferTextureType type);
		private:

			GLuint m_fbo;
			GLuint m_textures[GBUFFER_NUM_TEXTURES];
			GLuint m_depthTexture;
			GLuint m_skyFbo;
			GLuint m_skyTexture;
			GLuint m_finalTexture;
		};
	}
}

#endif // GL_G_BUFFER_HPP
