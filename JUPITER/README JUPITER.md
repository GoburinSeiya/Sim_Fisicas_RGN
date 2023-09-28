# -Hola Júpiter

![imagen](simfisIMGS/jupiter.jpg)

Ahora hacemos el mismo ejercicio pero con el lugar de incidencia en Júpiter y el cubo deja de ser de un material ficticio, y ahora está elaborado de carburo de tungsteno.

Nuevamente, analizando paso a paso, el primero es la gravedad, la cual es mayor a la de la tierra, revisando wolfram podemos encontrar el valor, y este es de 24.79 m/s.

En cuanto a la densidad, ahora si estamos usando un material verdadero, por lo cual debemos actualizar los valores del material. El carburo de tungsteno tiene una densidad de 15.6 g/cm3, sin embargo, box2D trabaja con kg/m3, por lo que basta con una conversión ya sea con regla de 3 o con un análisis dimensional si queremos ser elegantes. El resultado es de 15600 kg/m3.

Finalmente nos encontramos con la fricción del aire, nuevamente este es un cálculo complejo, el encontrarlo es digno un enfoque único y una ardua investigación en si mismo, por lo cual solo lo supondremos, si usamos 0.3 como el valor de la tierra, usaremos 0.9f como el valor para Júpiter.

Tras esto, actualizamos nuevamente el código y llegamos al resultado.

## Código 

```cpp
#include <iostream>  
#include <Box2d/Box2d.h>  
  
int main() {  
    //Creacion del mundo y de la gravedad, pero en la luna  
    b2Vec2 gravity(0.0f, -24.79f); // La gravedad es mayor a la de la tierra  
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
    bodyDef.position.Set(0.0f, 15.0f);  
    b2Body* body = world.CreateBody(&bodyDef);  
  
    b2PolygonShape dynamicBox;  
    dynamicBox.SetAsBox(1.0f, 1.0f);  
  
    //Le damos propiedades a la caja dinámica  
  
    b2FixtureDef fixtureDef;  
    fixtureDef.shape = &dynamicBox;  
    fixtureDef.density = 15600.0f;  
    fixtureDef.friction = 0.9f; //La friccion es un calculo complejo, pero sabemmoso que al ser un gigante gaseosa la atmosfera de la tierra es mayor
  
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
```