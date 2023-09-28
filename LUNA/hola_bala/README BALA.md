# -Hola bala

![imagen](simfisIMGS/val.png)

En este código simulamos una bala de cañon siendo disparada en la luna. Para no alargar algo que ya se ha explicado en otros readmes, el proceso inicial es el mismo al momento de crear el mundo y el cuerpo que experimentará la física. La principal diferencia es que usamos #ifndef para definir Pi como constante, usamos ese comando en particular para que la variable se ejecute o se defina antes de que se compile o ejecute nuestro programa. Las variables que alteramos fueron la de la gravedad para igualarla a la luna, junto con la fricción del aire y la densidad, ajustándola por la densidad del hierro fundido.

Otra diferencia viene en otras características que debemos de darle a la forma, estas siendo el ángulo y la velocidad. Estos valores podemos declararlos como constantes de tipo float,, en este caso el ángulo inicial de disparo es de 60 grados, que debemos convertir a radianes para box2D y la velocidad de disparo es de 900 m/s. Tras esto, debemos separar los componentes de la velocidad, esto lo logramos multiplicando la velocidad inicial por el seno del ángulo y el coseno para los ejes 'y' y 'x' respectivamente. tras esto finalmente le damos esta velocidad lineal a nuestro cuerpo usando SetLinearVelocity y procedemos a imprimir la información.

# Código
```cpp
#include <Box2D/Box2D.h>  
#include <cmath>  
#include <iostream>  
  
#ifndef M_PI  
#define M_PI 3.14159265358979323846  
#endif  
  
int main() {  
// Define the gravity vector  
    b2Vec2 gravity(0.0f, -1.6); //bullet is being fired on Earth  
  
// Construct a world object, which will hold and simulate the rigid bodies  
    b2World world(gravity);  
  
// Create a dynamic body for the bullet  
    b2BodyDef bodyDef;  
    bodyDef.type = b2_dynamicBody;  
    bodyDef.position.Set(0.0f, 0.0f);  
    b2Body* body = world.CreateBody(&bodyDef);  
  
// Define another box shape for the bullet  
    b2PolygonShape dynamicBox;  
    dynamicBox.SetAsBox(0.2f, 0.05f);  
  
// Define the dynamic body fixture  
    b2FixtureDef fixtureDef;  
    fixtureDef.shape = &dynamicBox;  
    fixtureDef.density = 7750.0f; //cast iron density  
    fixtureDef.friction = 0.0f;  
  
// Add the shape to the body  
    body->CreateFixture(&fixtureDef);  
  
// Set the initial velocity of the bullet  
    float angle = 60.0f; // Angle in degrees  
    float speed = 900.0f; // Speed in m/s  
    float vx = speed * std::cos(angle * M_PI / 180.0f); //transforming deg into rad  
    float vy = speed * std::sin(angle * M_PI / 180.0f);  
  
    body->SetLinearVelocity(b2Vec2(vx, vy));  
  
// Simulate the world  
    float timeStep = 1.0f / 60.0f;  
    int32 velocityIterations = 6;  
    int32 positionIterations = 2;  
  
    for (int i = 0; i < 60; ++i)  
    {  
        world.Step(timeStep, velocityIterations, positionIterations);  
        std::cout << body->GetPosition().x << " " << body->GetPosition().y << std::endl;  
  
    }  
  
// Remember to clean up  
    world.DestroyBody(body);  
  
    return 0;  
}
```