#ifndef PARTICULE_ENGINE_HPP
#define PARTICULE_ENGINE_HPP

#include <ParticuleEngine/Core/Component.hpp>
#include <ParticuleEngine/Core/GameObject.hpp>
#include <ParticuleEngine/Core/Object.hpp>
#include <ParticuleEngine/Core/Transform.hpp>

#include <ParticuleEngine/Enum/Layer.hpp>
#include <ParticuleEngine/Enum/Tag.hpp>

#include <ParticuleEngine/Scene/Scene.hpp>
#include <ParticuleEngine/Scene/SceneManager.hpp>

#include <ParticuleEngine/Components/Components.hpp>

namespace Particule::Engine
{
    void ParticuleEngineInit();

    void ParticuleEngineQuit();
}

#endif // PARTICULE_ENGINE_HPP