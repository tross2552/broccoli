#pragma once

//For use by Broccoli applications
#include "Broccoli/Application.h"
#include "Broccoli/Layer.h"

#include "Broccoli/Core/Log.h"

#include "Broccoli/ImGui/ImGuiLayer.h"

#include "Broccoli/Input.h"
#include "Broccoli/Events/MouseEvent.h"
#include "Broccoli/Events/ApplicationEvent.h"
#include "Broccoli/Events/KeyEvent.h"

#include "Broccoli/Math/Math.h"

#include "Broccoli/Scene/Scene.h"
#include "Broccoli/Scene/Components.h"
#include "Broccoli/Scene/Entity.h"
#include "Broccoli/Scene/ScriptableEntity.h"
#include "Broccoli/Scene/SceneSerializer.h"

//PHYSICS ------------------

#include "Broccoli/Physics/SimplePhysicsEngine2D.h"
#include "Broccoli/Physics/PhysicsWorld.h"
#include "Broccoli/Physics/Collision.h"

// RENDERER ----------------

#include "Broccoli/Renderer/Renderer.h"
#include "Broccoli/Renderer/Renderer2D.h"
#include "Broccoli/Renderer/RenderCommand.h"

#include "Broccoli/Renderer/Camera.h"

#include "Broccoli/Renderer/Buffer.h"
#include "Broccoli/Renderer/Shader.h"
#include "Broccoli/Renderer/Texture.h"
#include "Broccoli/Renderer/VertexArray.h"
#include "Broccoli/Renderer/Framebuffer.h"

//AUDIO ---------------

#include "Broccoli/Audio/AudioDevice.h"
#include "Broccoli/Audio/AudioSource.h"
#include "Broccoli/Audio/AudioClip.h"
