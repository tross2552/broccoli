#pragma once
#include "Scene.h"

namespace brcl
{
	
	class SceneSerializer
	{

		//we probably want reflection before implementing broader serialization.
		//for now, we just have a class to handle saving and loading scenes for the editor
		
	public:
		SceneSerializer(std::shared_ptr<Scene> scene) :
		m_Scene(scene) {}

		void Serialize(const std::string& path);

		bool Deserialize(const std::string& path);

	private:
		
		std::shared_ptr<Scene> m_Scene;
	};
}
