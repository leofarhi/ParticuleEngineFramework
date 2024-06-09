#ifndef PARTICULE_ESSENTIAL_HPP
#define PARTICULE_ESSENTIAL_HPP
#include <ParticuleEssential/Graphic/Window.hpp>

#include <ParticuleEssential/Basic/Basic.hpp>

#include <ParticuleEssential/Types/Dict.hpp>
#include <ParticuleEssential/Types/List.hpp>
#include <ParticuleEssential/Types/Vector2.hpp>
#include <ParticuleEssential/Types/Vector2Int.hpp>
#include <ParticuleEssential/Types/Vector3.hpp>
#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEssential/Types/Matrix.hpp>
#include <ParticuleEssential/Types/LambdaFunction.hpp>
#include <ParticuleEssential/Types/Rect.hpp>
#include <ParticuleEssential/Types/String.hpp>

#include <ParticuleEssential/Font/Font.hpp>

#include <ParticuleEssential/Texture/Texture.hpp>
#include <ParticuleEssential/Texture/Sprite.hpp>

#include <ParticuleEssential/Graphic/Color.hpp>

#include <ParticuleEssential/Graphic/Draw/Pixel.hpp>
#include <ParticuleEssential/Graphic/Draw/Line.hpp>
#include <ParticuleEssential/Graphic/Draw/Rect.hpp>

#include <ParticuleEssential/Input/Input.hpp>

#include <ParticuleEssential/System/VirtualFile.hpp>


namespace Particule::Essential
{
    void ParticuleEssentialInit();

    void ParticuleEssentialQuit();
}

#endif // PARTICULE_ESSENTIAL_HPP