/** Name: Christopher Glenn
 *  vunetid: glennca1
 *  email: christopher.a.glenn@vanderbilt.edu
 *  Honor code: I have neither given nor received unauthorized aid on this assignment.
 *  file: Object.cpp
 */
#include "Object.h"
#include "Visitor.h"
#include "Universe.h"
/**
 *  Initializes an object with the provided properties - really only called by
 * the ObjectFactory
 */
Object::Object(const std::string& name, double mass, const vector2& pos, const vector2& vel)
    : name(name)
    , mass(mass)
    , position(pos)
    , velocity(vel)
{
}
/**
     *  An entry point for a visitor.
     */
void Object::accept(Visitor& visitor) {
    visitor.visit(*this);
}
/**
 *  Implementation of the prototype. Returns a dynamically allocated deep
 *  copy of this object.
 */
Object* Object::clone() const
{
    return new Object(name, mass, position, velocity);
}

/**
 *  Returns the mass.
 */
double Object::getMass() const noexcept
{
    return mass;
}
/**
 *  Returns the name.
 */
std::string Object::getName() const noexcept
{
    return name;
}

/**
 *  Returns the position vector.
 */
vector2 Object::getPosition() const noexcept
{
    return position;
}

/**
 *  Returns the velocity vector.
 */
vector2 Object::getVelocity() const noexcept
{
    return velocity;
}

/**
 *  Calculates the force vector between lhs and rhs. The direction of the
 *  result is as experienced by lhs. Negate the result to obtain force
 *  experienced by rhs.
 */
vector2 Object::getForce(const Object& rhs) const noexcept
{
    vector2 distance = position-rhs.position;

    double force = Universe::G * (mass*rhs.mass)/(distance.normSq());

    return distance.normalize().scale(force);

}

/**
 *  Sets the position vector.
 */
void Object::setPosition(const vector2& pos)
{
    position = pos;
}

/**
 *  Sets the velocity vector.
 */
void Object::setVelocity(const vector2& vel)
{
    velocity = vel;
}

/**
 *  Returns true if this object is member-wise equal to rhs.
 */
bool Object::operator==(const Object& rhs) const
{

    return name == rhs.name && mass == rhs.mass && position == rhs.position
        && velocity == rhs.velocity;
}

/**
 *  Returns !(*this == rhs).
 */
bool Object::operator!=(const Object& rhs) const
{
    return !(*this == rhs);
}