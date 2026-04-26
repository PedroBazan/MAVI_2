#pragma once
#include "raylib.h"
#include <box2d.h>

class Caja
{
private:
    b2Body* body;
    float ancho;
    float alto;
    Color color;

public:
    Caja(b2World& world, float x, float y,
        float w = 50.0f, float h = 50.0f,
        float angulo = 0.0f);

    void Dibujar();
};