#pragma once

#include <string>

//#include "Broccoli/Math/Math.h"

namespace brcl
{
	class Texture
	{
		
	public:

		virtual ~Texture() = default;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static std::unique_ptr<Texture2D> Create(uint32_t width, uint32_t height);
		static std::unique_ptr<Texture2D> Create(const std::string& path);

		virtual bool operator==(const Texture2D& other) const = 0;
	};

	/*
	class SubTexture2D //todo: implement
	{
	public:
		
		static SubTexture2D CreateFromTexture(std::unique_ptr<Texture2D> texture, Vector2 width, Vector2 height) {  return SubTexture2D(); }

	private:
		std::unique_ptr<Texture2D> m_Texture;
		Vector2 m_Position;
		Vector2 m_Size;
	};*/

}
