#pragma once

#include "../Math/Point4.h"
#include <string>
#include <vector>

class WorldParser
{
public:
    static void LoadDataFromFile(const char* filename);

    struct Face
    {
        int indices[3];
    };

    static float   left;
    static float   right;
    static float   top;
    static float   bottom;
    static float   focal;
    static float   nearPlane;
    static float   farPlane;
    static float   distance;
    static float   height;
    static Point4  position;
    static Vector4 view;
    static Vector4 up;

    static std::vector<Point4> vertices;
    static std::vector<Face>   faces;
    static std::vector<Point4> colors;
    static std::vector<Point4> textureCoords;

    struct Transform
    {
        std::string mName;

        Point4  pos;
        Vector4 rot;
        Vector4 sca;

        std::string parent;
    };
    static std::vector<Transform> sceneobjects;
};