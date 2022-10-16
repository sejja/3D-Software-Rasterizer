#include "Parser.h"

float   WorldParser::left;
float   WorldParser::right;
float   WorldParser::top;
float   WorldParser::bottom;
float   WorldParser::focal;
float   WorldParser::nearPlane;
float   WorldParser::farPlane;
float   WorldParser::distance;
float   WorldParser::height;
Point4  WorldParser::position;
Vector4 WorldParser::view;
Vector4 WorldParser::up;

std::vector<Point4>            WorldParser::vertices;
std::vector<WorldParser::Face> WorldParser::faces;
std::vector<Point4>            WorldParser::colors;
std::vector<Point4>            WorldParser::textureCoords;

std::vector<WorldParser::Transform> WorldParser::sceneobjects;

void WorldParser::LoadDataFromFile(const char* filename)
{
    FILE* in;

    vertices.clear();
    faces.clear();
    colors.clear();
    textureCoords.clear();
    sceneobjects.clear();

    fopen_s(&in, filename, "r");
    if (!in)
    {
        printf("Could not open input file\n");
        exit(0);
    }


    fscanf_s(in, "camera\n{\n\tleft = %f\n\tright = %f\n\ttop = %f\n\tbottom = %f\n\tfocal = %f\n\tnear = %f\nfar = %f\ndistance = %f\nheight = %f\nposition = %f,%f,%f\nview = %f,%f,%f\nup = %f,%f,%f\n}\n",
        &left,
        &right,
        &top,
        &bottom,
        &focal,
        &nearPlane,
        &farPlane,
        &distance,
        &height,
        &position.x, &position.y, &position.z,
        &view.x, &view.y, &view.z,
        &up.x, &up.y, &up.z);

    unsigned i, count;

    //
    fscanf_s(in, "vertexes\n{\n\tcount = %d\n\t", &count);
    for (i = 0; i < count; ++i)
    {
        Point4 position;
        fscanf_s(in, "\t%f,%f,%f,%f\n", &position.x, &position.y, &position.z, &position.w);
        vertices.push_back(position);
    }
    fscanf_s(in, "}\n");
    //

    //
    fscanf_s(in, "faces\n{\n\tcount = %d\n\t", &count);
    unsigned faceNum = count;
    for (i = 0; i < faceNum; i++)
    {
        Face face;
        fscanf_s(in, "\t%i,%i,%i\n", &face.indices[0], &face.indices[1], &face.indices[2]);
        faces.push_back(face);
    }
    fscanf_s(in, "}\n");
    //

    //
    fscanf_s(in, "facecolor\n{\n\t");
    for (i = 0; i < count; i++)
    {
        Point4 color;
        fscanf_s(in, "\t%f,%f,%f\n", &color.x, &color.y, &color.z);
        colors.push_back(color);
    }
    fscanf_s(in, "}\n");
    //

    //
    fscanf_s(in, "texturecoordinates\n{\n\t");
    for (i = 0; i < faceNum * 3; i++)
    {
        Point4 textCoord;
        textCoord.z = 0.0f;
        textCoord.w = 0.0f;
        fscanf_s(in, "\t%f,%f\n", &textCoord.x, &textCoord.y);
        textureCoords.push_back(textCoord);
    }
    fscanf_s(in, "}\n");
    //

    //
    fscanf_s(in, "scene\n{\n\tcount = %d\n", &count);
    unsigned objCount = count;
    for (i = 0; i < objCount; i++)
    {
        Transform transform;
        char      mName[512] = { 0 };
        char      parent[512] = { 0 };
        fscanf_s(in, "\t%s = ",
            mName, 512);
        fscanf_s(in, "T(%f,%f,%f), ",
            &transform.pos.x, &transform.pos.y, &transform.pos.z);
        fscanf_s(in, "R(%f,%f,%f), ",
            &transform.rot.x, &transform.rot.y, &transform.rot.z);
        fscanf_s(in, "S(%f,%f,%f), ",
            &transform.sca.x, &transform.sca.y, &transform.sca.z);
        fscanf_s(in, "%s\n",
            parent, 512);
        transform.mName = mName;
        transform.parent = parent;

        sceneobjects.push_back(transform);
    }
    fscanf_s(in, "}\n");
    //

    fclose(in);
}