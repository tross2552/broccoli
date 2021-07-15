#pragma once
namespace brcl
{
	struct FrameBufferSpec
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
	};
	
	class Framebuffer
	{
	public:
		
		virtual ~Framebuffer() = default;

		virtual const FrameBufferSpec& GetSpecification() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual uint32_t GetColorAttachmentID() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		static std::unique_ptr<Framebuffer> Create(const FrameBufferSpec& spec);
		
	};

}