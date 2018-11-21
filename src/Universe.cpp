/** Name: Christopher Glenn
 *  vunetid: glennca1
 *  email: christopher.a.glenn@vanderbilt.edu
 *  Honor code: I have neither given nor received unauthorized aid on this assignment.
 *  file: Universe.cpp
 */
#include "Universe.h"
#include "Object.h"

/**
 *  Returns the only instance of the Universe
 */
Universe* Universe::instance()
{
    if (inst == nullptr) {
        inst = new Universe;
    }
    return inst;
}

/**
 *  Releases all the dynamic objects still registered with the Universe.
 */
Universe::~Universe()
{
    release(objects);
    inst = nullptr;
}

/**
 *  Returns the begin iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
Universe::iterator Universe::begin()
{
    return objects.begin();
}

/**
 *  Returns the begin iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
Universe::const_iterator Universe::begin() const
{
    return objects.begin();
}

/**
 *  Returns the end iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
Universe::iterator Universe::end()
{
    return objects.end();
}

/**
 *  Returns the end iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
Universe::const_iterator Universe::end() const
{
    return objects.end();
}

/**
 *  Returns a container of copies of all the Objects registered with the
 *  Universe. This should be used as the source of data for computing the
 *  next step in the simulation
 */
std::vector<Object*> Universe::getSnapshot() const
{
    std::vector<Object*> snap;
    snap = objects;
    return snap;
}

/**
 *  Advances the simulation by the provided time step. For this assignment,
 *  you must assume that the first registered object is a "sun" and its
 *  position should not be affected by any of the other objects.
 */
void Universe::stepSimulation(const double& timeSec)
{
    std::vector<Object*> copy = getSnapshot();
    vector2 outForce;
    vector2 newPos;
    for (uint32_t i = 1; i < copy.size(); ++i) {
        for (uint32_t j = 0; j < copy.size(); ++j) {
            if (i < j) {
                outForce += copy[i]->getForce(*copy[j]);
            } else if (i > j) {
                outForce -= (copy[i]->getForce(*copy[j]));
            }
        }
        vector2 accel = (outForce) / (copy[i]->getMass());
        vector2 newVel = (accel)*timeSec + copy[i]->getVelocity();
        newPos = copy[i]->getPosition() + 0.5 * (accel)*timeSec + copy[i]->getVelocity();
        copy[i]->setPosition(newPos);
        copy[i]->setVelocity(newVel);
    }
    swap(copy);
}

/**
 *  Swaps the contents of the provided container with the Universe's Object
 *  store and releases the old Objects.
 */
void Universe::swap(std::vector<Object*>& snapshot)
{
    std::swap(snapshot, objects);
    release(snapshot);
}

/**
 *  Registers an Object with the universe. The Universe will clean up this
 *  object when it deems necessary.
 */
Object* Universe::addObject(Object* ptr)
{
    if (ptr != nullptr) {
        objects.emplace_back(ptr);
    }
    return objects[objects.size() - 1];
}
/**
 *  Calls delete on each pointer and removes it from the container.
 */
void Universe::release(std::vector<Object*>& objects)
{

    //    std::for_each(objects.rbegin(), objects.rend(), objects.pop_back());

    for (uint32_t i = objects.size(); i > 0; --i) {
        //        delete objects[i];
        objects.pop_back();
    }
}

Universe* Universe::inst;
