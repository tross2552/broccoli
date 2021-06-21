#pragma once

namespace brcl
{

	//buffer data types will likely change, for now data is generally stored in 4 byte values
	constexpr uint32_t shader_type_size = 4;

	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(const ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:    return 1;
	
		case ShaderDataType::Float:   return shader_type_size;
		case ShaderDataType::Float2:  return shader_type_size * 2;
		case ShaderDataType::Float3:  return shader_type_size * 3;
		case ShaderDataType::Float4:  return shader_type_size * 4;
			
		case ShaderDataType::Int:     return shader_type_size;
		case ShaderDataType::Int2:    return shader_type_size * 2;
		case ShaderDataType::Int3:    return shader_type_size * 3;
		case ShaderDataType::Int4:    return shader_type_size * 4;
			
		case ShaderDataType::Mat3:    return shader_type_size * 3 * 3;
		case ShaderDataType::Mat4:    return shader_type_size * 4 * 4;
			
		}

		BRCL_CORE_ASSERT(false, "Buffer Layout Error: Unknown ShaderDataType!");
		return 0;
		
	}

	static uint32_t ShaderDataTypeCount(const ShaderDataType type)
	{
		switch (type)
		{
			
		case ShaderDataType::Bool:
		case ShaderDataType::Float:   
		case ShaderDataType::Int:     return 1;
			
		case ShaderDataType::Float2:
		case ShaderDataType::Int2:    return 2;
		
		case ShaderDataType::Float3:
		case ShaderDataType::Int3:    return 3;
			
		case ShaderDataType::Float4:
		case ShaderDataType::Int4:    return 4;

		case ShaderDataType::Mat3:    return 3 * 3;
		case ShaderDataType::Mat4:    return 4 * 4;

		}

		BRCL_CORE_ASSERT(false, "Buffer Layout Error: Unknown ShaderDataType!");
		return 0;

	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;

		BufferElement() = default;

		BufferElement(const ShaderDataType type, const std::string& name) :
			Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0) {}
	};

	class BufferLayout
	{

	public:

		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement> elements) :
			m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}
		
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

	private:

		inline void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
			}

			m_Stride = offset;
		}
	
	private:

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
		
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
		
	};

	class IndexBuffer
	{
	public:
		
		IndexBuffer() = default;
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual  uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
	
}