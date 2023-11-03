![imagen](simfisIMGS/SFMLLogo.png)

# HOLA SFML

Ya logramos simular las físicas de elementos relativamente sencillos. Ahora toca empezar a simular eventos mas complejos, para esto es que existen las joints en Box2D. Estas nos permiten simular situaciones mas complejas ya que nos permiten generar cuerpos con mas variables, por ejemplo, ruedas, engranes. poleas, soldaduras, etc. que dependiendo de nuestra creatividad podemos usar para simular situaciones si bien no necesariamente realistas, como lo dice en su propia documentación, idealizadas. A esto se le agrega SFML, una herramienta que podemos utilizar para mostrar de manera gráfica (y a diferencia de RUBE, no es exactamente un motor gráfico con box 2D ya elaborado, sino que es uno que podemos usar para personalizar mas su uso).

Lo primero que haremos será declarar nuestros cuerpos en una clase, para poder generarlos de forma más rápida y sencilla. Generamos un cuerpo dinámico y uno estático para experimentar con ambos y ver sus efectos, el cuerpo estático se representa mediante un cubo, y el dinámico mediante una esfera, lo que al mismo tiempo nos permite practicar como crear diferentes formas en SFML.

Tras esto queda declarar las joints

## Distance joint

Esta joint nos permite mantener la distancia entre 2 cuerpos siempre iguales, para generarla necesitamos declarar los 2 cuerpos, y declaramos ambos como ancla (de esta forma se mantiene la distancia)

## Revolute Joint

Esta joint hace que un cuerpo gire alrededor de otro, por lo cual debemos declarar 2 cuerpos, en el cual uno debe forzosamente ser dinámico, y otro que funcionará como el ancla. Tras declararlos, revolute joint cuenta con varias funciones que nos permiten modificar su funcionamiento, entre ellas están *lowerAngle* y *upperAngle*, que nos permiten definir el ángulo máximo y el mínimo al que puede rotar (*enableLimit* nos deja decidir si lo usamos o no, útil para declarar por si queremos cambiarlo mas adelante accediendo a la joint) un torque máximo, especialmente porque en los juegos, usualmente multiplicamos el movimiento por deltaTime o el tiempo de frames, esto hace que escale y puede que lo haga hasta un punto en el que de problemas, por eso le ponemos un límite, al igual podemos desde aquí darle una velocidad de rotación, pero es mejor dejarla en 0 por si queremos después aumentarla o reducirla.

## Prismatic Joint

Esta joint nos permite limitar el movimiento de un cuerpo a un solo eje, ya sea x o y. Para usar esta joint necesitamos declarar 2 cuerpos, nuevamente un ancla y el cuerpo que realice el movimiento, que debe ser dinámico. Al igual que con la joint de rotación podemos poner un límte superior e inferior al movimiento, al igual que un limite de velocidad por las mismas razones.

## Pulley Joint
Es una joint que nos deja generar una polea, para funcionar necesitamos 2 cuerpos y 2 joints,, una de revolución y una prismatica para ser exactos,, también un ratio en el que se extiende la polea.

## Wheel Joint
Cuenta con una simulación de suspensión. Para usarla necesitamos agregar la librería *b2_wheel_joint.h*.  Para generarla necesitamos un cuerpo, uno que funcione como llanta y otro como el ancla o cuerpo, y el eje en el que rotará. Esta joint también cuenta con un motor y torque.

## Weld joint
Necesitamos *b2_weld_joint.h*. Nos permite unir a 2 cuerpos, se pueden doblar, mediante la experimentación pudimos notar que soldar un objeto dinámico con movimiento con uno estático hará que no se muevan. Necesitamos 2 cuerpos y un ancla.

Finalmente imprimimos con SFML, para esto necesitamos encontrar la posición del cuerpo,  borrarla, e imprimirla en un ciclo para que se vea el movimiento
## Código

```cpp
#include <SFML/Graphics.hpp>  
#include <Box2D/Box2D.h>  
#include <Box2D/b2_wheel_joint.h>  
#include <Box2D/b2_weld_joint.h>  
  
constexpr float SCALE = 30.0f;  
  
class Sphere{  
public:  
Sphere(b2World &world, float x, float y, float density){  
        b2BodyDef bodyDef;  
        bodyDef.type = b2_dynamicBody;  
        bodyDef.position.Set(x / SCALE, y / SCALE);  
        body = world.CreateBody(&bodyDef);  
  
        b2CircleShape circle;  
        circle.m_p.Set(10.0f/SCALE, 10.0f /SCALE);  
        circle.m_radius = 10.0f / SCALE;  
  
        b2FixtureDef fixtureDef;  
        fixtureDef.shape = &circle;  
        fixtureDef.density = density;  
        body->CreateFixture(&fixtureDef);  
  
        sphere.setRadius(10.f);  
        sphere.setFillColor(sf::Color::Red);  
        sphere.setOrigin(5.f, 5.f);  
    }  
  
    void update(){  
        sphere.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
        sphere.setRotation(body->GetAngle() *180 /b2_pi);  
    }  
  
    void draw(sf::RenderWindow &win) const  
    {  
        win.draw(sphere);  
    }  
  
    void resetPosition()  
    {  
        body->SetTransform(b2Vec2(0,0), body->GetAngle());  
    }  
  
    void stop()  
    {  
        body->SetLinearVelocity(b2Vec2(0, 0));  
    }  
  
    b2Body *getBody() {  
        return body;  
    }  
  
private:  
    sf::CircleShape sphere;  
    b2Body *body;  
};  
  
class StaticCube {  
public:  
    StaticCube(b2World &world, float x, float y) {  
        b2BodyDef bodydef;  
        bodydef.position.Set(x / SCALE, y / SCALE);  
        body = world.CreateBody(&bodydef);  
  
        b2PolygonShape shape;  
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);  
  
        b2FixtureDef fixturedef;  
        fixturedef.shape = &shape;  
        fixturedef.density = 1.0f;  
        body->CreateFixture(&fixturedef);  
  
        box.setSize(sf::Vector2f(10.f, 10.f));  
        box.setFillColor(sf::Color::Red);  
        box.setOrigin(5.f, 5.f);  
    }  
  
    void update() {  
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
        box.setRotation(body->GetAngle() * 180 / b2_pi);  
    }  
  
    void draw(sf::RenderWindow &win) const {  
        win.draw(box);  
    }  
  
    void resetPosition() {  
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());  
    }  
  
    void stop() {  
        body->SetLinearVelocity(b2Vec2(0, 0));  
    }  
  
    b2Body *getBody() {  
        return body;  
    }  
  
private:  
    sf::RectangleShape box;  
    b2Body *body;  
};  
  
int main() {  
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");  
  
    b2Vec2 gravity(0.0f, -0.0f);  
    b2World world(gravity);  
  
    // region Creamos los cuerpos necesarios  
    Sphere sphereBody(world, 400, 300, 1.0); //distance  
  
    StaticCube cube(world,620, 520); //revolute anchor  
  
    StaticCube cube2(world, 100, 700); //wheel anchor  
  
    StaticCube cube3(world, 500, 300); //prismatic anchor  
  
    StaticCube cube4(world, 880, 700); //cube anchor  
  
    Sphere sphere2(world, 500, 200, 1.0); //prismatic body  
  
    Sphere sphere3(world, 600, 500, 1.0); //Anchor body  
  
    Sphere sphere4(world, 450, 400, 2.0); //pulley anchor A  
  
    Sphere sphere5(world, 550, 400, 1.0); //pulley Anchor B  
  
    Sphere sphere6(world, 100, 710, 1.0); //wheel  
  
    Sphere sphere7(world, 900, 700, 1.0f); //weld body A  
  
    //endregion  
  
    //Creamos Distance Joint    
    b2DistanceJointDef jointDef;  
    jointDef.Initialize(sphereBody.getBody(), cube3.getBody(), sphereBody.getBody()->GetWorldCenter(), cube3.getBody()->GetWorldCenter());  
  
    float frequencyHz = 4.0f;  
    float dampingRatio = 0.5f;  
  
    b2LinearStiffness(jointDef.stiffness, jointDef.damping, frequencyHz, dampingRatio, jointDef.bodyA, jointDef.bodyB);  
  
    world.CreateJoint(&jointDef);  
  
    //Create a Revolute Joint  
    //region Code    
    b2RevoluteJointDef rjointDef;  
    rjointDef.Initialize(cube.getBody(), sphere3.getBody(), cube.getBody()->GetWorldCenter());  
    rjointDef.lowerAngle = -0.25f * b2_pi; //-90 deg multiply by 0.5  
    rjointDef.upperAngle = 0.25f * b2_pi; //45 deg m by 0.25  
    //rjointDef.enableLimit = true;    
    rjointDef.maxMotorTorque = 5.0f;  
    rjointDef.motorSpeed = 0.0f;  
    rjointDef.enableMotor = true;  
    b2RevoluteJoint* revoluteJoint = (b2RevoluteJoint*)world.CreateJoint(&rjointDef);  
    //endregion  
  
  
    //Create a Prismatic joint    //region Code    
    b2PrismaticJointDef pjointDef;  
    b2Vec2 worldAxis(0.0f, 1.0f);  
    pjointDef.Initialize(cube3.getBody(), sphere2.getBody(), cube3.getBody()->GetWorldCenter(), worldAxis);  
    pjointDef.lowerTranslation = -20.0f;  
    pjointDef.upperTranslation = 20.0f;  
    pjointDef.enableLimit = true;  
    pjointDef.maxMotorForce = 1.0f;  
    pjointDef.motorSpeed = 0.0f;  
    pjointDef.enableMotor = true;  
    b2PrismaticJoint* prismaticJoint = (b2PrismaticJoint*)world.CreateJoint(&pjointDef);  
    //endregion  
  
    //Create a pulley joint    
    //region Code    
    b2Vec2 anchor1 = sphere4.getBody()->GetWorldCenter();  
    b2Vec2 anchor2 = sphere5.getBody()->GetWorldCenter();  
  
    b2Vec2 groundAnchor1(450, 350 + 10.0f);  
    b2Vec2 groundAnchor2(550, 350 + 10.0f);  
  
  
    float ratio = 1.0f;  
  
    b2PulleyJointDef pulleyJointDef;  
    pulleyJointDef.Initialize(sphere4.getBody(), sphere5.getBody(), groundAnchor1, groundAnchor2, anchor1, anchor2, ratio);  
    world.CreateJoint(&pulleyJointDef);  
  
    sphere4.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.5f), true);  
    //endregion  
  
    //Create a Gear Joint    
    //region Code    
    b2GearJointDef gjointDef;  
    gjointDef.bodyA = sphere2.getBody();  
    gjointDef.bodyB = cube.getBody();  
    gjointDef.joint1 = revoluteJoint;  
    gjointDef.joint2 = prismaticJoint;  
    gjointDef.ratio = 2.0f * b2_pi / 10.0f;  
    //endregion  
  
    //region Create a wheel joint    
    b2WheelJointDef wjointDef;  
    wjointDef.Initialize(cube2.getBody(), sphere6.getBody(), cube2.getBody()->GetWorldCenter(), b2Vec2(0.0, 0.0));  
    wjointDef.motorSpeed = 0.0f;  
    wjointDef.maxMotorTorque = 0.0f;  
    wjointDef.enableMotor = true;  
    b2WheelJoint* wheelJoint = (b2WheelJoint*)world.CreateJoint(&wjointDef);  
  
    //endregion  
  
    //region Create a Weld Joint    
    b2WeldJointDef weldJointDef;  
    weldJointDef.Initialize(cube4.getBody(), sphere7.getBody(), cube4.getBody()->GetWorldCenter());  
    world.CreateJoint(&weldJointDef);  
    //endregion  
  
    while (window.isOpen()) {  
        sf::Event event;  
        while (window.pollEvent(event)) {  
            // The Z key event to close the window  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {  
                window.close();  
                return 0; // return from the main function, effectively ending the program  
            }  
        }  
        world.Step(1 / 60.f, 8, 3);  
        revoluteJoint->SetMotorSpeed(0.1f);  
        prismaticJoint->SetMotorSpeed(0.1f);  
        prismaticJoint->SetMaxMotorForce(0.1f);  
        wheelJoint->SetMotorSpeed(0.5f);  
        wheelJoint->SetMaxMotorTorque(0.5f);  
        sphere7.getBody()->ApplyForceToCenter(b2Vec2(-0.5f, 0.0f), true); //Sabemos que funciona porque incluso tras aplicar fuerza el cuerpo no se mueve, se testeo sin el weld y si se meueve sin el, al soldar cuerpo estatico con dinamico evitamos el movimiento (asumo por la densidad infinita)  
  
        //region Print to screen        sphereBody.update();  
        cube.update();  
        cube2.update();  
        cube3.update();  
        cube4.update();  
        sphere2.update();  
        sphere3.update();  
        sphere4.update();  
        sphere5.update();  
        sphere6.update();  
        sphere7.update();  
  
        window.clear();  
        sphereBody.draw(window);  
        cube.draw(window);  
        cube2.draw(window);  
        cube3.draw(window);  
        cube4.draw(window);  
  
        sphere2.draw(window);  
        sphere3.draw(window);  
        sphere4.draw(window);  
        sphere5.draw(window);  
        sphere6.draw(window);  
        sphere7.draw(window);  
        window.display();  
        //endregion  
  
    }  
    return 0;  
}
```

