#include "Caja.h"

Caja::Caja(b2World& world, float x, float y, float w, float h, float angulo)
{
    ancho = w;
    alto = h;
    color = Fade(SKYBLUE, 0.95f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    // ángulo inicial en radianes
    bodyDef.angle = angulo;

    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(ancho / 2.0f, alto / 2.0f);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.4f;
    fixture.restitution = 0.2f;

    body->CreateFixture(&fixture);
}

void Caja::Dibujar()
{
    b2Vec2 pos = body->GetPosition();
    float angle = body->GetAngle() * RAD2DEG;

    Rectangle rect =
    {
        pos.x,
        pos.y,
        ancho,
        alto
    };

    Vector2 origin = { ancho / 2.0f, alto / 2.0f };

    // borde azul (más grande)
    Rectangle borde =
    {
        pos.x,
        pos.y,
        ancho + 4,
        alto + 4
    };

    DrawRectanglePro(borde, origin, angle, DARKBLUE);

    // caja principal
    DrawRectanglePro(rect, origin, angle, color);
}