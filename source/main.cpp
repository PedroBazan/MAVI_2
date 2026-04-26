#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "Caja.h"
using namespace std;



struct PhysicsCircle
{
    b2Body* body;
    float radius;
    Color color;
};

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MAVI II - Bienvenida");
    SetTargetFPS(60);

    Color fondo = { 110, 100, 215, 255 };
    Color textoPrincipal = RAYWHITE;
    Color textoSecundario = DARKPURPLE;
    Color sueloColor = Fade(DARKGREEN, 0.7f);

    // Mundo físico
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // -----------------------------
    // Suelo estático
    // -----------------------------
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(screenWidth / 2.0f, screenHeight - 40.0f);
    b2Body* groundBody = world.CreateBody(&groundDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(screenWidth / 2.0f, 20.0f);
    groundBody->CreateFixture(&groundShape, 0.0f);

    vector<Caja> cajas;
    vector<PhysicsCircle> circles;

    // -----------------------------
    // Crear algunas cajas dinámicas
    // -----------------------------
    for (int i = 0; i < 4; i++)
    {
        cajas.emplace_back(world, 300 + i * 80, 80 + i * 20);
    }

    // -----------------------------
    // Crear algunos círculos dinámicos
    // -----------------------------
    for (int i = 0; i < 3; i++)
    {
        b2BodyDef circleDef;
        circleDef.type = b2_dynamicBody;
        circleDef.position.Set(650.0f + i * 60.0f, 60.0f + i * 30.0f);

        b2Body* circleBody = world.CreateBody(&circleDef);

        b2CircleShape circleShape;
        circleShape.m_radius = 20.0f;

        b2FixtureDef circleFixture;
        circleFixture.shape = &circleShape;
        circleFixture.density = 1.0f;
        circleFixture.friction = 0.3f;
        circleFixture.restitution = 0.6f;

        circleBody->CreateFixture(&circleFixture);

        circles.push_back({ circleBody, 20.0f, Fade(ORANGE, 0.95f) });
    }
    float anguloCreacion = 0.0f;

    while (!WindowShouldClose())
    {
        // Avanzar simulación
        world.Step(1.0f / 60.0f, 8, 3);

        BeginDrawing();
        ClearBackground(fondo);

        // Suelo visual
        DrawRectangle(0, screenHeight - 60, screenWidth, 40, sueloColor);


        //crear cajas con spacio
        if (IsKeyPressed(KEY_SPACE))
        {
            cajas.emplace_back(
                world,
                GetRandomValue(100, 900),
                20,
                50,
                50,
                anguloCreacion
            );
        }

        //mover angulo 
        if (IsKeyPressed(KEY_LEFT))
        {
            anguloCreacion -= 5 * DEG2RAD;
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            anguloCreacion += 5 * DEG2RAD;
        }
        //dibujar cajas

        for (auto& caja : cajas)
        {
            caja.Dibujar();
        }


        
        // Dibujar círculos
        for (const auto& circle : circles)
        {
            b2Vec2 pos = circle.body->GetPosition();
            DrawCircleV({ pos.x, pos.y }, circle.radius, circle.color);
            DrawCircleLines((int)pos.x, (int)pos.y, circle.radius, BROWN);
        }

        // Panel superior
        DrawRectangle(90, 70, 820, 90, Fade(BLACK, 0.18f));
        DrawText("MAVI 2, Mavix reincarnated", 120, 90, 28, textoPrincipal);
        DrawText(TextFormat("Angulo: %.0f", anguloCreacion * RAD2DEG), 20, 20, 20, WHITE);
        

        // Pie
        DrawText("Jugando con el box2d", 300, 540, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}