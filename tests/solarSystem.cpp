// @author G. Hemingway, copyright 2017
//

#include "./testHelper.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "Parser.h"
#include "Universe.h"
#include "Visitor.h"
#include <gtest/gtest.h>
#include <memory>

// The fixture for testing the Solar System math.
class SolarSystemTest : public ::testing::Test {
};

TEST_F(SolarSystemTest, PrimaryTest)
{
    std::unique_ptr<Universe> univ(Universe::instance());

    EXPECT_NO_THROW({
        // Create a sun with zero mass, stationary at origin
        ObjectFactory::makeObject("Sun", 0.0);
        // Add all of the planets
        ObjectFactory::makePlanet(ObjectFactory::Planet::Mercury);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Venus);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Earth);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Mars);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Jupiter);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Saturn);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Uranus);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Neptune);
        ObjectFactory::makePlanet(ObjectFactory::Planet::Pluto);
    });

    // Run the simulation for 1M seconds ~ 11.574days
    const uint32_t step = 1;
    const uint32_t steps = 1000000;
    for (uint32_t time = 0; time < steps; time += step) {
        univ->stepSimulation(step);
    }

    /*
        Sun
        0:0
        0:0
        Mercury
        5.79002e+10:4.74e+10
        0.437455:47400
        Venus
        1.082e+11:3.5e+10
        0.529591:35000
        Earth
        1.496e+11:2.98e+10
        0.160443:29800
        Mars
        2.279e+11:2.41e+10
        0.356739:24100
        Jupiter
        7.786e+11:1.31e+10
        0.0882898:13100
        Saturn
        1.4335e+12:9.7e+09
        -0.292299:9700
        Uranus
        2.8725e+12:6.8e+09
        -0.0447195:6800
        Neptune
        4.4951e+12:5.4e+09
        -0.0154571:5400
        Pluto
        5.9064e+12:4.7e+09
        -0.0107835:4700
   */
    // Compare where planets are:
    for (auto planet : *univ) {
        const std::string name = planet->getName();
        const vector2 position = planet->getPosition();
        const vector2 velocity = planet->getVelocity();

        std::cout << name << std::endl;
        std::cout << position[0] << ":" << position[1] << std::endl;
        std::cout << velocity[0] << ":" << velocity[1] << std::endl;
    }
}

Object* ObjectFactory::makePlanet(const Planet& p)
{
    const std::string names[] = { "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn",
        "Uranus", "Neptune", "Pluto" };
    const double masses[]
        = { 0.330e24, 4.87e24, 5.97e24, 0.642e24, 1898e24, 568e24, 86.8e24, 102e24, 0.0146e24 };
    const double positions[]
        = { 57.9e9, 108.2e9, 149.6e9, 227.9e9, 778.6e9, 1433.5e9, 2872.5e9, 4495.1e9, 5906.4e9 };
    const double velocities[]
        = { 47.4e3, 35.0e3, 29.8e3, 24.1e3, 13.1e3, 9.7e3, 6.8e3, 5.4e3, 4.7e3 };

    int index;
    switch (p) {
    case Planet::Mercury:
        index = 0;
        break;
    case Planet::Venus:
        index = 1;
        break;
    case Planet::Earth:
        index = 2;
        break;
    case Planet::Mars:
        index = 3;
        break;
    case Planet::Jupiter:
        index = 4;
        break;
    case Planet::Saturn:
        index = 5;
        break;
    case Planet::Uranus:
        index = 6;
        break;
    case Planet::Neptune:
        index = 7;
        break;
    case Planet::Pluto:
        index = 8;
        break;
    }

    std::string name = names[index];
    double mass = masses[index];
    vector2 pos;
    pos[0] = positions[index];
    vector2 vel;
    vel[1] = velocities[index];
    auto planet = new Object(name, mass, pos, vel);
    Universe::instance()->addObject(planet);
    return planet;
}

// @author G. Hemingway, copyright 2017
//
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include "Vector.h"

// Forward declaration.
class Object;

/**
 *  A factory class used to make Object creation easier.
 */
class ObjectFactory {
public:
    /**
     * Enumeration of planets - used when we ask to create a planet via makePlanet
     */
    enum class Planet { Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto };

    /**
     *  Creates an object with the provided parameters. Default values of zero
     *  will be assigned to everything except for name.  Also adds the object to
     * the singleton Universe
     */
    static Object* makeObject(std::string name, double mass = 0, const vector2& pos = vector2(),
        const vector2& vel = vector2());

    //                  Merc.   Venus   Earth   Mars    Saturn  Jup.    Uran.   Nep.    Pluto
    // Mass: 10^24kg -- 0.330	4.87	5.97	0.642	1898	568	    86.8	102
    // 0.0146 Pos: 10^6 km  --  57.9	108.2	149.6	227.9	778.6	1433.5	2872.5	4495.1
    // 5906.4 Vel: km/s     --  47.4	35.0	29.8	24.1	13.1	9.7	    6.8	    5.4
    // 4.7
    static Object* makePlanet(const Planet&);

private:
    /*
     * Deny access to the default constructor - must be used as static factory
     */
    ObjectFactory();
};

#endif // OBJECT_FACTORY_H
