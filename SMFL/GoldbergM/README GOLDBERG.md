![imagen](simfisIMGS/goldberg.png)
## Elaboración

La idea rea relativamente simple, una pelota cae desde el cielo sobre una rampa, tira una caja, dicha caja y pelota caen en la canasta, lo que levanta la otra canasta, activando un sensor, el cual activaría en rotor que golpearía un cuerpo sobre el cual reposa una pelota, esta saldría volando, golpearía a un ariete, el cual cargaría en contra de unos desarmados dominos. Los dominos harían cosas de dominos, tirando una ultima pelota sobre un cuerpo que simula una máquina de caminar. 

Para conseguir esto necesitamos el joint de polea, pues para la polea que activaría el sensor, Una de revolución para golpear con fuerza el objeto que golpeará al ariete, y para que este se mueva y golpee a los dominós exactamente donde queremos usamos una joint prismática, limitando su movimiento. Los dominós usan una joint de soldadura, esto aprovechando las debilidades de Box2D. En la documentación dice que es tentador usar Weld para hacer cuerpos destructibles, pero esto tiende a fallar ya que los cuerpos siguen siendo flexibles incluso soldados. Aunado a esto, si solo usamos rectángulos, por como box2D maneja las colisiones el cuerpo realmente solo es empujado, y no cae como necesitamos, incluso aplicando la fuerza en el eje superior. Esto debido a que pese a que en el mundo real, si se aplican fuerzas por secciones, en box2D (y en la mayoría de simuladores de física) es por cuerpo. Para simular esto, cada domino está compuesto de 2 caras, una menos densa por la mitad, siendo esta la inferior, así podemos balancear los dominos, y haremos que si lo impactamos en la cara superior, entonces caigan como un domino lo haría al desequilibrarse, gracias a la menor densidad no requerirá tanta fuerza, así cada domino, tirará en cadena al siguiente, con un poco de ayuda de la gravedad.

Lamentablemente, no pude hacer la joint de polea funcionar correctamente, entonces el sensor se descartó y tuve que hardcodear la rotación de la joint de revolución para mostrar el funcionamiento planeado. De igual manera no se usó una joint de engranaje, mi idea era hacer que la pelota cayera sobre dos engranajes sosteniendo una cadena, simulando una cinta que gira o una rueda de tanque, este girara y la pelota caerá a la nada, y de ser posible hacer loop de este ciclo para dar la ilusión de que la pelota regresa y es una máquina de energía infinita, pero lamentablemente, el fallo e intento de reparar la polea me llevo demasiado tiempo y no logré enfocarme en lograr esto último.
## Código

```cpp
#include <SFML/Graphics.hpp>  
#include <Box2D/Box2D.h>  
#include <Box2D/b2_wheel_joint.h>  
#include <Box2D/b2_weld_joint.h>  
  
constexpr float SCALE = 30.0f;  
  
class Sphere{  
public:  
    Sphere(b2World &world, float x, float y, float density,float  scale){  
        b2BodyDef bodyDef;  
        bodyDef.type = b2_dynamicBody;  
        bodyDef.position.Set(x / SCALE, y / SCALE);  
        body = world.CreateBody(&bodyDef);  
  
        b2CircleShape circle;  
        circle.m_p.Set(scale /SCALE, scale /SCALE);  
        circle.m_radius = scale  / SCALE;  
  
        b2FixtureDef fixtureDef;  
        fixtureDef.shape = &circle;  
        fixtureDef.density = density;  
        body->CreateFixture(&fixtureDef);  
  
        sphere.setRadius(scale);  
        sphere.setFillColor(sf::Color::Red);  
        sphere.setOrigin(0.f, 0.f);  
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
  
class Cube {  
public:  
    Cube(b2World &world, float x, float y, float hx, float hy, bool isDynamic) {  
        b2BodyDef bodydef;  
        bodydef.position.Set(x / SCALE, y / SCALE);  
        if(isDynamic)  
            bodydef.type = b2_dynamicBody;  
        body = world.CreateBody(&bodydef);  
  
        b2PolygonShape shape;  
        shape.SetAsBox((hx / 4) / SCALE, hy / SCALE);  
  
        b2FixtureDef fixturedef;  
        fixturedef.shape = &shape;  
        fixturedef.density = 0.25f;  
        body->CreateFixture(&fixturedef);  
  
        box.setSize(sf::Vector2f(hx, hy));  
        box.setFillColor(sf::Color::Red);  
        box.setOrigin(0.f, 0.f);  
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
  
class StaticTriangle{  
public:  
    StaticTriangle(b2World &world, float x, float y){  
        b2BodyDef bodyDef;  
        bodyDef.position.Set(x / SCALE, y / SCALE);  
        body = world.CreateBody(&bodyDef);  
  
        b2Vec2 triangleVertices[3];  
        triangleVertices[0].Set(0.0f, 0.0f);  
        triangleVertices[1].Set(100.0f * 1.45 /SCALE, 0.0f);  
        triangleVertices[2].Set(0.0f, -100.0f * 1.45 / SCALE); // triangulo  
        b2PolygonShape triangle;  
        triangle.Set(triangleVertices, 3);;  
  
  
        b2FixtureDef fixtureDef;  
        fixtureDef.shape = &triangle;  
        fixtureDef.friction = 0.5f;  
        body->CreateFixture(&fixtureDef);  
  
        triangleShape.setPointCount(3.f);  
        triangleShape.setPoint(0, sf::Vector2f(0,0));  
        triangleShape.setPoint(1, sf::Vector2f(100,0));  
        triangleShape.setPoint(2, sf::Vector2f(0,-100));  
        triangleShape.setFillColor(sf::Color::Blue);  
        triangleShape.setOrigin(0.f, 0.f);  
    }  
  
    void update(){  
        triangleShape.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
        triangleShape.setRotation(body->GetAngle() *180 /b2_pi);  
    }  
  
    void draw(sf::RenderWindow &win) const  
    {  
        win.draw(triangleShape);  
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
    sf::ConvexShape triangleShape;  
    b2Body *body;  
};  
  
class Rectangle{  
public:  
    Rectangle(b2World &world, float x, float y, float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y, float density, bool SD){  
        b2BodyDef bodyDef;  
        bodyDef.position.Set(x / SCALE, y / SCALE);  
  
        if(SD)  
            bodyDef.type = b2_dynamicBody;  
  
        body = world.CreateBody(&bodyDef);  
  
        b2Vec2 rectangleVertices[4];  
        rectangleVertices[0].Set(p1x / SCALE, p1y /SCALE);  
        rectangleVertices[1].Set(p2x / SCALE, p2y /SCALE);  
        rectangleVertices[2].Set(p3x / SCALE, p3y /SCALE);  
        rectangleVertices[3].Set(p4x / SCALE, p4y /SCALE);  
        b2PolygonShape rectangle;  
        rectangle.Set(rectangleVertices, 4);;  
  
  
        b2FixtureDef fixtureDef;  
        fixtureDef.shape = &rectangle;  
        fixtureDef.density = density;  
        fixtureDef.friction = 0.5;  
        body->CreateFixture(&fixtureDef);  
  
        rectangleShape.setPointCount(4.f);  
        rectangleShape.setPoint(0, sf::Vector2f(p1x,p1y));  
        rectangleShape.setPoint(1, sf::Vector2f(p2x,p2y));  
        rectangleShape.setPoint(2, sf::Vector2f(p3x,p3y));  
        rectangleShape.setPoint(3, sf::Vector2f(p4x,p4y));  
        rectangleShape.setFillColor(sf::Color::Green);  
        rectangleShape.setOrigin(0.f, 0.f);  
    }  
  
    void update(){  
        rectangleShape.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
        rectangleShape.setRotation(body->GetAngle() *180 /b2_pi);  
    }  
  
    void draw(sf::RenderWindow &win) const  
    {  
        win.draw(rectangleShape);  
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
    sf::ConvexShape rectangleShape;  
    b2Body *body;  
};  
  
class Domino{  
public:  
    Domino(b2World &world, float x, float y, bool isUpperPart){  
        b2BodyDef bodyDef;  
        bodyDef.position.Set(x / SCALE, y / SCALE);  
        bodyDef.type = b2_dynamicBody;  
        body = world.CreateBody(&bodyDef);  
  
        b2Vec2 rectangleVertices[4];  
        rectangleVertices[0].Set( 0.0f /SCALE,  0.0f /SCALE);  
        rectangleVertices[1].Set(10.0f /SCALE,  0.0f /SCALE);  
        rectangleVertices[2].Set(10.0f /SCALE, 12.5f /SCALE);  
        rectangleVertices[3].Set(0.0 /SCALE, 12.5f /SCALE);  
        b2PolygonShape rectangle;  
        rectangle.Set(rectangleVertices, 4);;  
  
  
        b2FixtureDef fixtureDef;  
        fixtureDef.shape = &rectangle;  
        if(isUpperPart)  
            fixtureDef.density = 0.5f;  
        else  
            fixtureDef.density = 1.0f;  
        body->CreateFixture(&fixtureDef);  
  
        rectangleShape.setPointCount(4.f);  
        rectangleShape.setPoint(0, sf::Vector2f(0, 0));  
        rectangleShape.setPoint(1, sf::Vector2f(10, 0));  
        rectangleShape.setPoint(2, sf::Vector2f(10, 12.5));  
        rectangleShape.setPoint(3, sf::Vector2f(0 ,12.5));  
        rectangleShape.setFillColor(sf::Color::White);  
        rectangleShape.setOrigin(0.f, 0.f);  
}  
  
    void update(){  
        rectangleShape.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
        rectangleShape.setRotation(body->GetAngle() *180 /b2_pi);  
    }  
  
    void draw(sf::RenderWindow &win) const  
    {  
        win.draw(rectangleShape);  
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
sf::ConvexShape rectangleShape;  
b2Body *body;  
};  
  
int main() {  
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");  
  
    b2Vec2 gravity(0.0f, 0.02);  
    b2World world(gravity);  
  
    Sphere ball(world, 10, 10, 0.25f, 12);  
    StaticTriangle ramp(world, -10.0f, 300);  
    Rectangle road(world,90,300, 0.0f, -0.0f, 600.0f, -0.0f, 600.0f, -10.0f, 0.0f, -10.0f, 1.0f, false);  
    Cube box(world, 600,200,20,20, true);  
  
    Rectangle pulleyBase(world, 800, 600, 0, 0, 100, 0, 100, 10, 0, 10, 1.0f, true);  
    Rectangle pulleyLateralAL(world, 790,540,0,0,0,70,10,70,10,0, 1.0f, true);  
    Rectangle pulleyLateralAR(world, 900, 540, 0, 0, 0, 70, 10, 70, 10, 0, 1.0f, true);  
    Rectangle pulleyBase2(world, 500, 800, 0, 0, 100, 0, 100, 10, 0, 10, 1.0f,true);  
    Rectangle pulleyLateralBL(world, 490,740,0,0,0,70,10,70,10,0, 1.0f,true);  
    Rectangle pulleyLateralBR(world, 600,740,0,0,0,70,10,70,10,0, 1.0f, true);  
  
    Cube pulleyAnchor(world, 850, 100, 10, 10, false);  
    Cube pulleyAnchor2(world, 550, 100, 10, 10, false);  
  
  
    Rectangle road2(world,50,600, 0.0f, -0.0f, 500.0f, -0.0f, 500.0f, -10.0f, 0.0f, -10.0f, 1.0f, false);  
    Rectangle ramp2(world,490,590, 0.0f, -0.0f, 100.0f, -0.0f, 100.0f, -10.0f, 0.0f, -10.0f, 1.0f, true);  
    Sphere pushBall(world, 500, 540, 1.0f, 12);  
  
    //Sphere ball2(world, 535, 750, 1.0f);  
    //Sphere balanceBall(world, 835,550, 1.0f);    Cube ramAnchor(world, 50, 560, 10.0f, 10.0f, false);  
    Rectangle ram(world, 240, 560, 0.0f, 0.0f, 60.0f, 0.0f, 60.0f, 8.0f, 0.0f, 8.0f, 1.0f, true);  
  
    Domino domino1Upper(world, 140, 565, true);  
    Domino domino1Lower(world, 140, 577.5, false);  
    Domino domino2Upper(world, 120, 565, true);  
    Domino domino2Lower(world, 120, 577.5, false);  
    Domino domino3Upper(world, 100, 565, true);  
    Domino domino3Lower(world, 100, 577.5, false);  
    Domino domino4Upper(world, 80, 565, true);  
    Domino domino4Lower(world, 80, 577.5, false);  
  
    Cube revoluteAnchor(world, 630, 580, 10, 10, false);  
    Cube revolutePiece(world, 680, 580, 15, 15, true);  
  
    Sphere FinalBall(world, 45, 550, 0.5f, 9);  
  
    //region revolute Joint  
    b2RevoluteJointDef rjointDef;  
    rjointDef.Initialize(revoluteAnchor.getBody(), revolutePiece.getBody(), revoluteAnchor.getBody()->GetWorldCenter());  
    rjointDef.lowerAngle = -0.25f * b2_pi; //-90 deg multiply by 0.5  
    rjointDef.upperAngle = 0.25f * b2_pi; //45 deg m by 0.25  
    //rjointDef.enableLimit = true;    rjointDef.maxMotorTorque = 5.0f;  
    rjointDef.motorSpeed = 0.0f;  
    rjointDef.enableMotor = true;  
    b2RevoluteJoint* revoluteJoint = (b2RevoluteJoint*)world.CreateJoint(&rjointDef);  
    //endregion  
  
    //region Pulley Joint    b2WeldJointDef weldPulleyAL;  
    weldPulleyAL.Initialize(pulleyBase.getBody(), pulleyLateralAL.getBody(), pulleyBase.getBody()->GetWorldCenter());  
    world.CreateJoint(&weldPulleyAL);  
  
  
    b2WeldJointDef weldPulleyAR;  
    weldPulleyAR.Initialize(pulleyBase.getBody(), pulleyLateralAR.getBody(), pulleyBase.getBody()->GetWorldCenter());  
    world.CreateJoint(&weldPulleyAR);  
  
    b2WeldJointDef weldPulleyBL;  
    weldPulleyBL.Initialize(pulleyBase2.getBody(), pulleyLateralBL.getBody(), pulleyBase.getBody()->GetWorldCenter());  
    world.CreateJoint(&weldPulleyBL);  
  
    b2WeldJointDef weldPulleyBR;  
    weldPulleyBR.Initialize(pulleyBase2.getBody(), pulleyLateralBR.getBody(), pulleyBase.getBody()->GetWorldCenter());  
    world.CreateJoint(&weldPulleyBR);  
  
    b2Vec2 anchor1 = pulleyBase.getBody()->GetWorldCenter();  
    b2Vec2 anchor2 = pulleyBase2.getBody()->GetWorldCenter();  
  
    b2Vec2 groundAnchor1 = pulleyAnchor.getBody()->GetWorldCenter();  
    b2Vec2 groundAnchor2 = pulleyAnchor2.getBody()->GetWorldCenter();  
  
  
    float ratio = 0.1f;  
  
    b2PulleyJointDef pulleyJointDef;  
    pulleyJointDef.Initialize(pulleyBase.getBody(), pulleyBase2.getBody(), groundAnchor1, groundAnchor2, anchor1, anchor2, ratio);  
    world.CreateJoint(&pulleyJointDef);  
    //endregion  
  
    //region Ram Limiter    b2PrismaticJointDef ramMovementRange;  
    b2Vec2 ramMovementAxis(1.0f, 0.0f);  
    ramMovementRange.Initialize(ramAnchor.getBody(), ram.getBody(), ramAnchor.getBody()->GetWorldCenter(), ramMovementAxis);  
    ramMovementRange.enableLimit = false;  
    ramMovementRange.lowerTranslation = -50.0f;  
    ramMovementRange.upperTranslation = 50.0f;  
    ramMovementRange.enableMotor = true;  
    ramMovementRange.motorSpeed = 0.0f;  
    b2PrismaticJoint* prismaticJoint = (b2PrismaticJoint*)world.CreateJoint(&ramMovementRange);  
    //endregion  
  
    //region Weld Dominoes    b2WeldJointDef domino1Weld;  
    domino1Weld.Initialize(domino1Upper.getBody(), domino1Lower.getBody(), domino1Lower.getBody()->GetWorldCenter());  
    world.CreateJoint(&domino1Weld);  
  
    b2WeldJointDef domino2Weld;  
    domino2Weld.Initialize(domino2Upper.getBody(), domino2Lower.getBody(), domino2Lower.getBody()->GetWorldCenter());  
    world.CreateJoint(&domino2Weld);  
    //endregion  
  
    b2WeldJointDef domino3Weld;  
    domino3Weld.Initialize(domino3Upper.getBody(), domino3Lower.getBody(), domino3Lower.getBody()->GetWorldCenter());  
    world.CreateJoint(&domino3Weld);  
  
    b2WeldJointDef domino4Weld;  
    domino4Weld.Initialize(domino4Upper.getBody(), domino4Lower.getBody(), domino4Lower.getBody()->GetWorldCenter());  
    world.CreateJoint(&domino4Weld);  
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
        world.Step(1 / 60.f, 8, 10);  
        revoluteJoint->SetMaxMotorTorque(2.0f);  
        revoluteJoint->SetMotorSpeed(2.0f);  
  
        ball.update();  
        ramp.update();  
        road.update();  
        box.update();  
        pulleyBase.update();  
        pulleyLateralAL.update();  
        pulleyLateralAR.update();  
        pulleyAnchor.update();  
        pulleyAnchor2.update();  
        pulleyBase2.update();  
        pulleyLateralBL.update();  
        pulleyLateralBR.update();  
        road2.update();  
        ramp2.update();  
        pushBall.update();  
        //ball2.update();  
        //balanceBall.update();        //ramAnchor.update();        ram.update();  
        domino1Upper.update();  
        domino1Lower.update();  
        domino2Upper.update();  
        domino2Lower.update();  
        domino3Upper.update();  
        domino3Lower.update();  
        domino4Upper.update();  
        domino4Lower.update();  
        revoluteAnchor.update();  
        revolutePiece.update();  
        FinalBall.update();  
  
  
        window.clear();  
        ball.draw(window);  
        ramp.draw(window);  
        road.draw(window);  
        box.draw(window);  
        pulleyBase.draw(window);  
        pulleyLateralAL.draw(window);  
        pulleyLateralAR.draw(window);  
        pulleyAnchor.draw(window);  
        pulleyAnchor2.draw(window);  
        pulleyBase2.draw(window);  
        pulleyLateralBL.draw(window);  
        pulleyLateralBR.draw(window);  
        road2.draw(window);  
        ramp2.draw(window);  
        pushBall.draw(window);  
        //ball2.draw(window);  
        //balanceBall.draw(window);        //ramAnchor.draw(window);        ram.draw(window);  
        domino1Upper.draw(window);  
        domino1Lower.draw(window);  
        domino2Upper.draw(window);  
        domino2Lower.draw(window);  
        domino3Upper.draw(window);  
        domino3Lower.draw(window);  
        domino4Upper.draw(window);  
        domino4Lower.draw(window);  
        FinalBall.draw(window);  
        revoluteAnchor.draw(window);  
        revolutePiece.draw(window);  
        window.display();  
    }  
    return 0;  
}
```