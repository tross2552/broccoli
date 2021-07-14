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

		virtual uint32_t GetColorAttachmentID() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;

		virtual void Invalidate() = 0;

		static std::unique_ptr<Framebuffer> Create(const FrameBufferSpec& spec);
		
	};

}