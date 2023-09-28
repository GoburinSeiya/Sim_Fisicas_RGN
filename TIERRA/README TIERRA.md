# -Hola Mundo

Un título bastante acorde y poético, ya que lo que haremos en este código no solo es nuestro hola mundo para el Box2D, sino que también es el hola al mundo virtual que generaremos para simular diferentes fenómenos físicos, el primero de ellos, simular la caída de un cubo de un material ficticio en la Tierra.

![imagen](simfisIMGS/earth.jpg)

Como dios dijo, lo primero que creamos es el mundo, y seguido de esto, que se haga la gravedad. Esto lo logramos usando un Vector2 llamado gravity, el cual tiene en los siguientes valores (0, -9.81). Esto dado a que la gravedad en esta simulación no generará fuerzas en el eje x, solo será fuerza de atracción hacia al suelo, cuya dirección es abajo, y por ende lo denotamos con un signo menos (-). Tras esto le damos esa cualidad al mundo usando b2World, y le damos un nombre creativo al mundo.

Ahora ya tenemos el mundo, pero este está vacío, para completar la simulación debemos agregar un cuerpo o elemento, junto con sus características. Empezaremos por definir el suelo, para ello primero debemos definir un cuerpo con b2BodyDef y siguiendo nuestras pautas de nombramiento lo llamamos groundBodyDef. Tras esto debemos darle sus características, diremos simplemente que su posición es -10m. Tras esto lo iniciamos en el mundo y le damos forma, en este caso la de un polígono. Dicho polígono será una caja, para eso usamos b2PlygonShape y luego SetAsBox, finalmente usamos Fixture para pegar la forma al cuerpo (similar a como poner un collider en un mesh).

Ahora necesitamos el objeto que va a caer, iniciamos de la misma forma, sin embargo, ahora usamos .type para declararlo como cuerpo dinámico ya que este cuerpo se va a encontrar en movimiento usando b2_dynamicBody.  Inicializamos su posición, indicando en que altura empezará a caer, como en este ejemplo son 15 metros, usamos 15.0f en y. Tras esto, con la intención de mejorar la calidad de nuestra simulación, debemos agregarles ciertas condiciones al cuerpo, y esto lo logramos con b2FixtureDef. Esto porque la forma de un objeto interacciona diferente con las condiciones físicas del ambiente, una caja no reacciona igual a la fricción que una bola.  Las condiciones que debemos de agregar son la forma, densidad y coeficiente de fricción, que en este caso son 1 y 0.3 respectivamente.

Finalmente, las condiciones de nuestra simulación están completas, ahora solo necesitamos definir el tiempo y reflejar la información. Lo primero que hacemos es un timeStep, esto para indicar en que lapso de tiempo elaboraremos una medida, o en otras palabras los footogramas que analizaremos. Se eligieron 60 fps, o 1/60, es decir que cada fracción de segundo tomamos una medida. Para concluir agregamos un ciclo for, este para que obtenga y muestre la información que necesitamos de la simulación en el lapso de tiempo que establecimos.
## Código

```cpp
#include <iostream>  
#include <Box2d/Box2d.h>  
  
int main() {  
    //Creacion del mundo y de la gravedad  
    b2Vec2 gravity(0.0f, -9.81f);  
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
    fixtureDef.density = 1.0f; //densidad del carburo de tungsteno  
    fixtureDef.friction = 0.3f; //La atmosfera es  
  
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