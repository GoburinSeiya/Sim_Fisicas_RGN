# - Hola Luna

El siguiente código es una simulación corta sobre un cubo cayendo en la luna. 
![imagen](simfisIMGS/moonfall.jpg)

Lo primero que debemos explicar es un poco la teoría detrás de este proyecto, en contraste con el código hola mundo, en donde dejamos caer un objeto en la tierra, en este se cambia el lugar de incidencia a la Luna. Pese a que esto puede sonar intimidante, si lo pensamos un poco podemos ver que dadas las condiciones que utilizamos no hay muchos cambios o factores que realmente debemos alterar. Empecemos analizando desde el primero.

El primer factor que establecemos es la gravedad, y claro que es diferente en la luna, es algo que todos sabemos y tenemos cierta noción visual gracias a el cine de Stanley Kubrick (o alguien menos famoso y relevante en la historia; Newton). Ignorando la complejidad de la definición energética de la gravedad que obtuvimos como resultado de Einstein, podemos tomar la definición de Newton, en donde mayor masa, mas gravedad, ya que a esta escala, es funcional. La luna tiene una masa menor a la tierra, bastante menor, y como resultado su fuerza gravitacional es 6 veces menor a la de la tierra, y por tanto sabemos que la gravedad de la luna tiene un valor aproximado de 1.63 m/s.

El siguiente factor que declaramos es la densidad, como en este ejemplo el cubo es de un material imaginario, y por tanto no tiene relevancia el valor que le otorguemos (fuera de en los resultados claro) se le dio el valor de 1. La densidad es la cantidad de masa por volumen de un cuerpo, o en cristiano, el peso relativo al espacio, si ocupo grandes cantidades de un material para que su peso tenga un valor alto, entonces es poco denso, si ocupo pocas cantidades de un material para un gran índice de peso, entonces, la pregunta es, ¿el lugar en el que vivimos afecta nuestra densidad? y aunque bueno, la respuesta es técnicamente sí, ya que nos componemos de los materiales que se encuentren en nuestro planeta, es principalmente el material el que determina esta respuesta, y como estamos utilizando el mismo material imaginario del ejercicio pasado, esta se mantiene invariante. 

Finalmente, quedamos con la fricción. Al caer, la principal resistencia con la que se encuentra un cuerpo es con la resistencia del aire. Esta se determina por muchos factores, y la resistencia del aire es un cálculo complejo, sin embargo, uno de los factores principales y de los que influyen en mayor medida es la densidad de la atmósfera de un planeta. En el caso de la luna, su densidad es tan baja que hace que la resistencia del aire sea un valor bastante bajo, tanto que se vuelve despreciable, y por ende podemos establecerlo como 0.

Una vez que tenemos claros los cambios, solo queda aplicarlos al código.
### Código

```cpp
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
```

## Operaciones
Box2D se encarga de los cálculos de caída libre y nos refleja la posición del objeto y el ángulo de caída, en donde si lo manejamos correctamente, siempre será 0 ya que es caída libre y no estamos aplicando fuerzas mas que en el eje y. La posición nos es mostrada 60 veces, en un lapso de 60 segundos, por ende cada actualización es cuanto se movió el cubo imaginario en dicha fracción de segundo.

### Notas
Los valores para las constantes fueron obtenidas de wolfram.