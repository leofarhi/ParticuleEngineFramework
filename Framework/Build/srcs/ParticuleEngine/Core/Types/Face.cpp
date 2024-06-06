#include <ParticuleEngine/Core/Types/Mesh.hpp>
#include <ParticuleEngine/Core/Types/Face.hpp>
#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEngine/Core/Components/Camera.hpp>
#include <ParticuleEssential/Graphic/Draw/Line.hpp>
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Graphic/Draw/Pixel.hpp>
#include <ParticuleEssential/Texture/Texture.hpp>
#include <stdio.h>
#include <math.h>

namespace Particule::Core
{
    using namespace Particule::Essential::Image;
    using namespace Particule::Essential::Graphic::Draw;
    using namespace Particule::Essential::Graphic;
    using namespace Particule::Essential::Image;

    Face::Face(Vertex *p1, Vertex *p2, Vertex *p3,
                Vector2Int uv1, Vector2Int uv2, Vector2Int uv3,
                Texture *texture)
    {
        verticesCount = 3;
        vertices = (Vertex **)malloc(3 * sizeof(Vertex *));
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        uv = (Vector2Int *)malloc(3 * sizeof(Vector2Int));
        this->uv[0] = uv1;
        this->uv[1] = uv2;
        this->uv[2] = uv3;
        this->texture = texture;
        this->depth = 0;
        CalculateNormal();
    }

    Face::Face(Vertex *p1, Vertex *p2, Vertex *p3, Vertex *p4,
                Vector2Int uv1, Vector2Int uv2, Vector2Int uv3, Vector2Int uv4,
                Texture *texture)
    {
        verticesCount = 4;
        vertices = (Vertex **)malloc(4 * sizeof(Vertex *));
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        uv = (Vector2Int *)malloc(4 * sizeof(Vector2Int));
        this->uv[0] = uv1;
        this->uv[1] = uv2;
        this->uv[2] = uv3;
        this->uv[3] = uv4;
        this->texture = texture;
        this->depth = 0;
        CalculateNormal();
    }

    Face::~Face()
    {
        if (vertices)
            free(vertices);
        if (uv)
            free(uv);
        if (texture)
            delete texture;
    }

    void Face::CalculateNormal()
    {
        Vector3Int v1 = vertices[1]->position - vertices[0]->position;
        Vector3Int v2 = vertices[2]->position - vertices[0]->position;
        normal = v1.Cross(v2);
    }

    void Face::CalculateDepth()
    {
        depth = 0;
        for (int i = 0; i < verticesCount; i++)
            depth += vertices[i]->projected.z;
        depth /= verticesCount;
    }

    static int min_local(int a, int b, int c)
    {
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }

    static int max_local(int a, int b, int c)
    {
        return a > b ? (a > c ? a : c) : (b > c ? b : c);
    }

    static void draw_texture_trapezoid(Vector2Int src[3], Vector3Int dest[3], Texture *texture, bool doubleSided)
    {
        int src_x0 = src[0].x, src_y0 = src[0].y;
        int src_x1 = src[1].x, src_y1 = src[1].y;
        int src_x2 = src[2].x, src_y2 = src[2].y;
        int dest_x0 = dest[0].x, dest_y0 = dest[0].y, dest_z0 = dest[0].z;
        int dest_x1 = dest[1].x, dest_y1 = dest[1].y, dest_z1 = dest[1].z;
        int dest_x2 = dest[2].x, dest_y2 = dest[2].y, dest_z2 = dest[2].z;
        int tex_w = texture->Width();
        int tex_h = texture->Height();
        if (!doubleSided && (dest_x1 - dest_x0) * (dest_y2 - dest_y0) - (dest_y1 - dest_y0) * (dest_x2 - dest_x0) < 0)
            return;
        int area = (dest_x2 - dest_x1) * (dest_y0 - dest_y1) - (dest_x0 - dest_x1) * (dest_y2 - dest_y1);
        if (area == 0)
            return;
        int min_y = min_local(dest_y1, dest_y2, dest_y0);
        int min_x = min_local(dest_x1, dest_x2, dest_x0);
        int max_y = max_local(dest_y1, dest_y2, dest_y0);
        int max_x = max_local(dest_x1, dest_x2, dest_x0);
        for (int y = min_y; y < max_y; y++)
        {
            for (int x = min_x; x < max_x; x++)
            {
                float w0 = ((dest_x2 - dest_x1) * (y - dest_y1) - (dest_y2 - dest_y1) * (x - dest_x1)) / (float)area;
                float w1 = ((dest_x0 - dest_x2) * (y - dest_y2) - (dest_y0 - dest_y2) * (x - dest_x2)) / (float)area;
                float w2 = 1 - w0 - w1;
                if (0 <= w0 && w0 <= 1 && 0 <= w1 && w1 <= 1 && 0 <= w2 && w2 <= 1)
                {
                    float z = 1 / (w0 / dest_z0 + w1 / dest_z1 + w2 / dest_z2);
                    float u = z * (w0 * src_x0 / dest_z0 + w1 * src_x1 / dest_z1 + w2 * src_x2 / dest_z2);
                    float v = z * (w0 * src_y0 / dest_z0 + w1 * src_y1 / dest_z1 + w2 * src_y2 / dest_z2);
                    u = (int)u % tex_w;
                    v = (int)v % tex_h;
                    Color color = texture->ReadPixel(u, v);
                    DrawPixelUnsafe(x, y, color);
                }
            }
        }
    }
    void Face::DrawTextured()
    {
        if (texture)
        {
            Vector3Int dest[3] = {vertices[0]->projected, vertices[1]->projected, vertices[2]->projected};
            Vector2Int src[3] = {this->uv[0], this->uv[1], this->uv[2]};
            draw_texture_trapezoid(src, dest, texture, false);
            if (verticesCount == 4)
            {
                dest[0] = vertices[0]->projected;
                dest[1] = vertices[2]->projected;
                dest[2] = vertices[3]->projected;
                src[0] = this->uv[0];
                src[1] = this->uv[2];
                src[2] = this->uv[3];
                draw_texture_trapezoid(src, dest, texture, doubleSided);
            }
        }
    }

    void Face::DrawWireframe()
    {
        for (int i = 0; i < verticesCount; i++)
        {
            int j = (i + 1) % verticesCount;
            Vector3Int v1 = vertices[i]->projected;
            Vector3Int v2 = vertices[j]->projected;
            DrawLine(v1.x, v1.y, v2.x, v2.y, COLOR_WHITE);
        }
    }
}