#include <Box2D/Box2D.h>
#include <cmath>
#include <iostream>

int main() {
// Define the gravity vector
    b2Vec2 gravity(0.0f, -9.81); //gravedad

// Construct a world object, which will hold and simulate the rigid bodies
    b2World world(gravity);

//Declaramos los vertices de las figuras (a la proxima recuerda que debe ser a favor de las manecillas del reloj, no como en unity)
    b2Vec2 triangleVertices[3];
    triangleVertices[0].Set(1.0f, 0.0f);
    triangleVertices[1].Set(0.0f, 1.0f);
    triangleVertices[2].Set(-1.0f, 0.0f); // triangulo

    b2Vec2 rectangleVertices[4];
    rectangleVertices[0].Set(2.0f, 0.0f);
    rectangleVertices[1].Set(2.0f, 1.0f);
    rectangleVertices[2].Set(-2.0f, 1.0f);
    rectangleVertices[3].Set(-2.0f, 0.0f); //rectangulo

    b2Vec2 squareVertices[4];
    squareVertices[0].Set(1.0f, 0.0f);
    squareVertices[1].Set(1.0f, 1.0f);
    squareVertices[2].Set(-1.0f, -1.0f);
    squareVertices[3].Set(-1.0f, 0.0f); // cuadrado

    b2Vec2 pentagonVertices[5];
    pentagonVertices[0].Set(1.0, 0.0f);
    pentagonVertices[1].Set(2.0, 2.0f);
    pentagonVertices[2].Set(0.0, 3.5f);
    pentagonVertices[3].Set(-2.0, 2.0f);
    pentagonVertices[4].Set(-1.0, 0.0f); //pentagono

    b2Vec2 hexagonVertices[6];
    hexagonVertices[0].Set(1.0f,0.0f);
    hexagonVertices[1].Set(2.0f,2.0f);
    hexagonVertices[2].Set(1.0f,4.0f);
    hexagonVertices[3].Set(-1.0f,4.0f);
    hexagonVertices[4].Set(-2.0f,2.0f);
    hexagonVertices[5].Set(-1.0f,0.0f); // hexagono

    b2Vec2 octagonVertices[8];
    octagonVertices[0].Set(1.0f, 0.0f);
    octagonVertices[1].Set(2.0f, 1.0f);
    octagonVertices[2].Set(2.0f, 2.0f);
    octagonVertices[3].Set(1.0f, 3.0f);
    octagonVertices[4].Set(-1.0f, 3.0f);
    octagonVertices[5].Set(-2.0f, 2.0f);
    octagonVertices[6].Set(-2.0f, 1.0f);
    octagonVertices[7].Set(-1.0f, 0.0f); //octagono

// Creamos los cuerpos para la forma
// Triangulo
    b2BodyDef triangleBodyDef;
    triangleBodyDef.position.Set(0.0f, 0.0f);
    b2Body* triangBody = world.CreateBody(&triangleBodyDef);

//rectangulo
    b2BodyDef rectangleBodyDef;
    rectangleBodyDef.position.SetZero();
    b2Body* rectBody = world.CreateBody(&rectangleBodyDef);

//cuadrado
    b2BodyDef squareBodyDef;
    squareBodyDef.position.SetZero();
    b2Body* squareBody = world.CreateBody(&rectangleBodyDef);

//Pentagono
    b2BodyDef pentagonBodyDef;
    pentagonBodyDef.position.SetZero();
    b2Body* pentagonBody = world.CreateBody(&rectangleBodyDef);

//Hexagono
    b2BodyDef hexagonBodyDef;
    hexagonBodyDef.position.SetZero();
    b2Body* hexagonBody = world.CreateBody(&rectangleBodyDef);

//Octagono
    b2BodyDef octagonBodyDef;
    octagonBodyDef.position.SetZero();
    b2Body* octagonBody = world.CreateBody(&rectangleBodyDef);

// Definimos las formas solicitadas
//Triangulo
    b2PolygonShape triangleShape;
    triangleShape.Set(triangleVertices, 3);

    //Rectangulo
    b2PolygonShape rectangleShape;
    rectangleShape.Set(rectangleVertices, 4);

    //cuadrado
    b2PolygonShape squareShape;
    squareShape.Set(squareVertices, 4);

    //pentagono
    b2PolygonShape pentagonShape;
    pentagonShape.Set(pentagonVertices, 5);

    //hexagono
    b2PolygonShape hexagonShape;
    hexagonShape.Set(hexagonVertices, 6);

    //octagono
    b2PolygonShape octagonShape;
    octagonShape.Set(octagonVertices, 8);


    return 0;
}
