#include <iostream>
#include <Box2d/Box2d.h>

int main() {
    //Creacion del mundo y de la gravedad, pero en la luna
    b2Vec2 gravity(0.0f, -1.63f); // La gravedad es 1/6 veces menos que en la tierra
    b2World world(gravity);

    //Creacion de  un cuerpo o elemento del mundo y sus caracteristicas
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    //Creamos la forma del cuerpo
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 1.0f);

    groundBody ->CreateFixture(&groundBox, 0.0f);

    //Definimos el nuevo cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; //definimos el cuerpo como dinamico ya que el estandar es estatico
    bodyDef.position.Set(0.0f, 20.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    //Le damos propiedades a la caja dinámica

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f; //La atmosfera es tan poco densa que la fricción del aire se vuelve despreciable

    body ->CreateFixture(&fixtureDef);

    float timeStep = 1.0f/60.0f; //la simulacion ocurre 60 veces por segundo

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f \n", position.x, position.y, angle);
    }
}
