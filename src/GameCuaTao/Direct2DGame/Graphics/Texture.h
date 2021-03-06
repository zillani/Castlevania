#pragma once

#include <memory>
#include "../Direct3D9.h"

class Texture
{
public:
	Texture() noexcept;
	Texture(ITexture_ texture, ImageInfo info) noexcept;

	// This adds a "move constructor" and a "move assignment", which will move the content
	// from one Texture to another to make sure only one IDirect3DTexture9 instace exists at
	// a time. The compiler should detect these two, and stop generating the implicit copy
	// constructor and copy assignment, so the Texture can no longer be copied, which is
	// exactly what we wanted.
	// https://stackoverflow.com/questions/18449770/c-storing-resources-whose-copy-operation-is-unreasonable-or-impossible#18450030
	Texture(Texture &&rhs) noexcept;
	Texture &operator=(Texture &&rhs) noexcept;

	ITexture_ Get() const noexcept;
	
	int Width();
	int Height();

	ImageInfo &GetInfo();
	
	~Texture() noexcept;

private:
	ITexture_ texture;
	ImageInfo info;
};