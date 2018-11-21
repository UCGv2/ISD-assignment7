/** Name: Christopher Glenn
 *  vunetid: glennca1
 *  email: christopher.a.glenn@vanderbilt.edu
 *  Honor code: I have neither given nor received unauthorized aid on this assignment.
 *  file: ObjectFactory.cpp
 */
#include "ObjectFactory.h"
#include "Object.h"
#include "Universe.h"
#include <memory>

/**
 *  Creates an object with the provided parameters. Default values of zero
 *  will be assigned to everything except for name.  Also adds the object to
 * the singleton Universe
 */
Object* ObjectFactory::makeObject(
    std::string name, double mass, const vector2& pos, const vector2& vel)
{
    Universe* uniFactory = Universe::instance();
    return uniFactory->addObject(new Object(name, mass, pos, vel));
}