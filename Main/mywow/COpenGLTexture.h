#pragma once

#include "compileconfig.h"

#ifdef MW_COMPILE_WITH_OPENGL

#include "ITexture.h"

class ITextureWriter;
class IBLPImage;
class IImage;

//������̬������̬render target
class COpenGLTexture : public ITexture
{
public:
	explicit COpenGLTexture( bool mipmap );			//from blp
	~COpenGLTexture();

public:
	//ITexture
	bool createEmptyTexture( const dimension2du& size, ECOLOR_FORMAT format );
	bool createFromImage(const dimension2du& size, IImage* image);
	bool createFromBlpImage(IBLPImage* blpImage);
	bool createRTTexture( const dimension2du& size, ECOLOR_FORMAT format, int nSamples );

	virtual bool isValid() const { return GLTexture != 0; }

	GLuint getGLTexture() const { return GLTexture; }

protected:
	virtual bool buildVideoResources();
	virtual void releaseVideoResources();
	virtual bool hasVideoBuilt() const { return VideoBuilt; }

private:
	bool createTexture( const dimension2du& size, ECOLOR_FORMAT format, bool mipmap = true );

	//blp
	void copyTexture( ITextureWriter* writer, IBLPImage* blpimage );
	bool copyBlpMipMaps( ITextureWriter* writer, IBLPImage* blpimage, uint32_t level = 1);

	//image
	void copyTexture( ITextureWriter* writer, IImage* image );
	bool createMipMaps( ITextureWriter* writer, uint32_t level = 1 );		

private:
	GLuint		GLTexture;
};


#endif