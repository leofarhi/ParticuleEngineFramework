#include <ParticuleEngine/Core/Types/Mesh.hpp>
#include <ParticuleEngine/Core/Types/Face.hpp>
#include <ParticuleEssential/Types/Vector3Int.hpp>
#include <ParticuleEssential/Basic/Basic.hpp>
#include <ParticuleEngine/Core/Components/Camera.hpp>
#include <ParticuleEssential/Graphic/Draw/Line.hpp>
#include <ParticuleEssential/Graphic/Color.hpp>
#include <ParticuleEssential/Graphic/Window.hpp>
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

    inline static int min_local(int a, int b, int c)
    {
        int min_ab = a < b ? a : b;
        return min_ab < c ? min_ab : c;
    }

    inline static int max_local(int a, int b, int c)
    {
        int max_ab = a > b ? a : b;
        return max_ab > c ? max_ab : c;
    }

    static void draw_texture_trapezoid(Vector2Int src[3], Vector3Int dest[3], Texture *texture, bool doubleSided)
    {
        if (!doubleSided && (dest[1].x - dest[0].x) * (dest[2].y - dest[0].y) - (dest[1].y - dest[0].y) * (dest[2].x - dest[0].x) < 0)
            return;

        const float area = (dest[2].x - dest[1].x) * (dest[0].y - dest[1].y) - (dest[0].x - dest[1].x) * (dest[2].y - dest[1].y);
        if (area == 0)
            return;
        const float src_x0 = src[0].x, src_y0 = src[0].y;
        const float src_x1 = src[1].x, src_y1 = src[1].y;
        const float src_x2 = src[2].x, src_y2 = src[2].y;
        const float dest_x0 = dest[0].x, dest_y0 = dest[0].y, dest_z0 = dest[0].z;
        const float dest_x1 = dest[1].x, dest_y1 = dest[1].y, dest_z1 = dest[1].z;
        const float dest_x2 = dest[2].x, dest_y2 = dest[2].y, dest_z2 = dest[2].z;
        const int tex_w = texture->Width();
        const int tex_h = texture->Height();

        const int min_y = min_local(dest_y1, dest_y2, dest_y0);
        const int min_x = min_local(dest_x1, dest_x2, dest_x0);
        const int max_y = max_local(dest_y1, dest_y2, dest_y0);
        const int max_x = max_local(dest_x1, dest_x2, dest_x0);

        const float w0_1 = (dest_x2 - dest_x1);
        const float w0_2 = (dest_y2 - dest_y1);
        const float w1_1 = (dest_x0 - dest_x2);
        const float w1_2 = (dest_y0 - dest_y2);

        for (int y = min_y; y < max_y; ++y)
        {
            float w0__1 = w0_1 * (y - dest_y1);
            float w1__1 = w1_1 * (y - dest_y2);
            for (int x = min_x; x < max_x; ++x)
            {
                // Change float to fixed point
                const float w0 = (w0__1 - w0_2 * (x - dest_x1)) / area;
                const float w1 = (w1__1 - w1_2 * (x - dest_x2)) / area;
                const float w2 = 1 - w0 - w1;
                if ((w0 >= 0) && (w1 >= 0) && (w2 >= 0))
                {
                    const float z = 1 / (w0 / dest_z0 + w1 / dest_z1 + w2 / dest_z2);
                    int u = (z * (w0 * src_x0 / dest_z0 + w1 * src_x1 / dest_z1 + w2 * src_x2 / dest_z2));
                    int v = (z * (w0 * src_y0 / dest_z0 + w1 * src_y1 / dest_z1 + w2 * src_y2 / dest_z2));
                    u = (int)u % tex_w;
                    v = (int)v % tex_h;
                    Color color = texture->ReadPixel(u, v);
                    DrawPixelUnsafe(x, y, color);
                }
            }
        }
    }

    /*static void swap(Vector3Int &a, Vector3Int &b)
    {
        Vector3Int tmp = a;
        a = b;
        b = tmp;
    }

    static void swap_int(int &a, int &b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    static void swap_vec2int(Vector2Int &a, Vector2Int &b)
    {
        Vector2Int tmp = a;
        a = b;
        b = tmp;
    }

    // Fonction pour interpoler les valeurs
    static int interpolate(int v0, int y0, int v1, int y1, int y)
    {
        if (y0 == y1)
            return v0;
        return v0 + (v1 - v0) * (y - y0) / (y1 - y0);
    }

    static float finterpolate(float v0, float y0, float v1, float y1, float y)
    {
        if (y0 == y1)
            return v0;
        return v0 + (v1 - v0) * (y - y0) / (y1 - y0);
    }

    static void draw_texture_trapezoid(Vector2Int src[3], Vector3Int dest[3], Texture *texture, bool doubleSided)
    {
        if (!doubleSided && (dest[1].x - dest[0].x) * (dest[2].y - dest[0].y) - (dest[1].y - dest[0].y) * (dest[2].x - dest[0].x) < 0)
            return;

        const int area = (dest[2].x - dest[1].x) * (dest[0].y - dest[1].y) - (dest[0].x - dest[1].x) * (dest[2].y - dest[1].y);
        if (area == 0)
            return;

        // Trier les sommets du triangle par coordonnée y
        if (dest[1].y < dest[0].y) { swap(dest[0], dest[1]); swap_vec2int(src[0], src[1]); }
        if (dest[2].y < dest[0].y) { swap(dest[0], dest[2]); swap_vec2int(src[0], src[2]); }
        if (dest[2].y < dest[1].y) { swap(dest[1], dest[2]); swap_vec2int(src[1], src[2]); }

        // Déclare les sommets après triage
        Vector3Int v0 = dest[0];Vector3Int v1 = dest[1];Vector3Int v2 = dest[2];
        Vector2Int uv0 = src[0];Vector2Int uv1 = src[1];Vector2Int uv2 = src[2];

        int width = window->GetWidth();
        int height = window->GetHeight();

        // Dessiner la partie inférieure du triangle
        for (int y = v0.y; y <= v1.y; y++)
        {
            if (y < 0 || y >= height) continue;

            int x_start = interpolate(v0.x, v0.y, v1.x, v1.y, y);int x_end = interpolate(v0.x, v0.y, v2.x, v2.y, y);
            int u_start = interpolate(uv0.x, v0.y, uv1.x, v1.y, y);int u_end = interpolate(uv0.x, v0.y, uv2.x, v2.y, y);
            int v_start = interpolate(uv0.y, v0.y, uv1.y, v1.y, y);int v_end = interpolate(uv0.y, v0.y, uv2.y, v2.y, y);
            int z_start = interpolate(v0.z, v0.y, v1.z, v1.y, y);int z_end = interpolate(v0.z, v0.y, v2.z, v2.y, y);

            if (x_start > x_end) {
                swap_int(x_start, x_end);
                swap_int(u_start, u_end);
                swap_int(v_start, v_end);
                swap_int(z_start, z_end);
            }

            for (int x = x_start; x <= x_end; x++)
            {
                if (x < 0 || x >= width) continue;
                float z = interpolate(z_start, x_start, z_end, x_end, x);
                float u = finterpolate((float)u_start/(float)z_start, x_start, (float)u_end/(float)z_end, x_end, x)*z;
                float v = finterpolate((float)v_start/(float)z_start, x_start, (float)v_end/(float)z_end, x_end, x)*z;
                u = (int)u % texture->Width();
                v = (int)v % texture->Height();
                Color color = texture->ReadPixel(u, v);
                DrawPixelUnsafe(x, y, color);
            }
        }

        // Dessiner la partie supérieure du triangle
        for (int y = v1.y; y <= v2.y; y++)
        {
            if (y < 0 || y >= height) continue;

            int x_start = interpolate(v1.x, v1.y, v2.x, v2.y, y);int x_end = interpolate(v0.x, v0.y, v2.x, v2.y, y);
            int u_start = interpolate(uv1.x, v1.y, uv2.x, v2.y, y);int u_end = interpolate(uv0.x, v0.y, uv2.x, v2.y, y);
            int v_start = interpolate(uv1.y, v1.y, uv2.y, v2.y, y);int v_end = interpolate(uv0.y, v0.y, uv2.y, v2.y, y);
            int z_start = interpolate(v1.z, v1.y, v2.z, v2.y, y);int z_end = interpolate(v0.z, v0.y, v2.z, v2.y, y);

            if (x_start > x_end) {
                swap_int(x_start, x_end);
                swap_int(u_start, u_end);
                swap_int(v_start, v_end);
                swap_int(z_start, z_end);
            }

            for (int x = x_start; x <= x_end; x++)
            {
                if (x < 0 || x >= width) continue;
                float z = interpolate(z_start, x_start, z_end, x_end, x);
                float u = finterpolate((float)u_start/(float)z_start, x_start, (float)u_end/(float)z_end, x_end, x)*z;
                float v = finterpolate((float)v_start/(float)z_start, x_start, (float)v_end/(float)z_end, x_end, x)*z;
                u = (int)u % texture->Width();
                v = (int)v % texture->Height();
                Color color = texture->ReadPixel(u, v);
                DrawPixelUnsafe(x, y, color);
            }
        }
    }*/


   /*static void swap(Vector3Int &a, Vector3Int &b)
{
    Vector3Int tmp = a;
    a = b;
    b = tmp;
}

static void swap_int(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

static void swap_float(float &a, float &b)
{
    float tmp = a;
    a = b;
    b = tmp;
}

static void swap_vec2int(Vector2Int &a, Vector2Int &b)
{
    Vector2Int tmp = a;
    a = b;
    b = tmp;
}

// Fonction pour interpoler les valeurs
static int interpolate(int v0, int y0, int v1, int y1, int y)
{
    if (y0 == y1)
        return v0;
    return v0 + (v1 - v0) * (y - y0) / (y1 - y0);
}

static float finterpolate(float v0, float y0, float v1, float y1, float y)
{
    if (y0 == y1)
        return v0;
    return v0 + (v1 - v0) * (y - y0) / (y1 - y0);
}

static void draw_texture_trapezoid(Vector2Int src[3], Vector3Int dest[3], Texture *texture, bool doubleSided)
{
    if (!doubleSided && (dest[1].x - dest[0].x) * (dest[2].y - dest[0].y) - (dest[1].y - dest[0].y) * (dest[2].x - dest[0].x) < 0)
        return;

    const int area = (dest[2].x - dest[1].x) * (dest[0].y - dest[1].y) - (dest[0].x - dest[1].x) * (dest[2].y - dest[1].y);
    if (area == 0)
        return;

    // Trier les sommets du triangle par coordonnée y
    if (dest[1].y < dest[0].y) { swap(dest[0], dest[1]); swap_vec2int(src[0], src[1]); }
    if (dest[2].y < dest[0].y) { swap(dest[0], dest[2]); swap_vec2int(src[0], src[2]); }
    if (dest[2].y < dest[1].y) { swap(dest[1], dest[2]); swap_vec2int(src[1], src[2]); }

    // Déclare les sommets après triage
    Vector3Int v0 = dest[0], v1 = dest[1], v2 = dest[2];
    Vector2Int uv0 = src[0], uv1 = src[1], uv2 = src[2];

    int width = window->GetWidth();
    int height = window->GetHeight();

    // Dessiner la partie inférieure du triangle
    for (int y = v0.y; y <= v1.y; y++)
    {
        if (y < 0 || y >= height) continue;

        int x_start = finterpolate(v0.x, v0.y, v1.x, v1.y, y);
        int x_end = finterpolate(v0.x, v0.y, v2.x, v2.y, y);
        float z_start = 1.0f / finterpolate(1.0f / v0.z, v0.y, 1.0f / v1.z, v1.y, y);
        float z_end = 1.0f / finterpolate(1.0f / v0.z, v0.y, 1.0f / v2.z, v2.y, y);
        float u_start = finterpolate(uv0.x / (float)v0.z, v0.y, uv1.x / (float)v1.z, v1.y, y) * z_start;
        float u_end = finterpolate(uv0.x / (float)v0.z, v0.y, uv2.x / (float)v2.z, v2.y, y) * z_end;
        float v_start = finterpolate(uv0.y / (float)v0.z, v0.y, uv1.y / (float)v1.z, v1.y, y) * z_start;
        float v_end = finterpolate(uv0.y / (float)v0.z, v0.y, uv2.y / (float)v2.z, v2.y, y) * z_end;

        if (x_start > x_end) {
            swap_int(x_start, x_end);
            swap_float(u_start, u_end);
            swap_float(v_start, v_end);
            swap_float(z_start, z_end);
        }

        for (int x = x_start; x <= x_end; x++)
        {
            if (x < 0 || x >= width) continue;
            float z = finterpolate(z_start, x_start, z_end, x_end, x);
            float u = finterpolate(u_start / z_start, x_start, u_end / z_end, x_end, x) * z;
            float v = finterpolate(v_start / z_start, x_start, v_end / z_end, x_end, x) * z;
            u = (int)u % texture->Width();
            v = (int)v % texture->Height();
            Color color = texture->ReadPixel(u, v);
            DrawPixelUnsafe(x, y, color);
        }
    }

    // Dessiner la partie supérieure du triangle
    for (int y = v1.y; y <= v2.y; y++)
    {
        if (y < 0 || y >= height) continue;

        int x_start = finterpolate(v1.x, v1.y, v2.x, v2.y, y);
        int x_end = finterpolate(v0.x, v0.y, v2.x, v2.y, y);
        float z_start = 1.0f / finterpolate(1.0f / v1.z, v1.y, 1.0f / v2.z, v2.y, y);
        float z_end = 1.0f / finterpolate(1.0f / v0.z, v0.y, 1.0f / v2.z, v2.y, y);
        float u_start = finterpolate(uv1.x / (float)v1.z, v1.y, uv2.x / (float)v2.z, v2.y, y) * z_start;
        float u_end = finterpolate(uv0.x / (float)v0.z, v0.y, uv2.x / (float)v2.z, v2.y, y) * z_end;
        float v_start = finterpolate(uv1.y / (float)v1.z, v1.y, uv2.y / (float)v2.z, v2.y, y) * z_start;
        float v_end = finterpolate(uv0.y / (float)v0.z, v0.y, uv2.y / (float)v2.z, v2.y, y) * z_end;

        if (x_start > x_end) {
            swap_int(x_start, x_end);
            swap_float(u_start, u_end);
            swap_float(v_start, v_end);
            swap_float(z_start, z_end);
        }

        for (int x = x_start; x <= x_end; x++)
        {
            if (x < 0 || x >= width) continue;
            float z = finterpolate(z_start, x_start, z_end, x_end, x);
            float u = finterpolate(u_start / z_start, x_start, u_end / z_end, x_end, x) * z;
            float v = finterpolate(v_start / z_start, x_start, v_end / z_end, x_end, x) * z;
            u = (int)u % texture->Width();
            v = (int)v % texture->Height();
            Color color = texture->ReadPixel(u, v);
            DrawPixelUnsafe(x, y, color);
        }
    }
}*/




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