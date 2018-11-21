/** Name: Christopher Glenn
 *  vunetid: glennca1
 *  email: christopher.a.glenn@vanderbilt.edu
 *  Honor code: I have neither given nor received unauthorized aid on this assignment.
 *  file: Visitor.cpp
 */
#include "Visitor.h"
#include "Object.h"
/**
 *  Construct a visitor that prints to the provided ostream.
 */
PrintVisitor::PrintVisitor(std::ostream& os)
    : os(os)
{
}

/**
 *  Prints the object's name.
 */
void PrintVisitor::visit(Object& object)
{
    os << object.getName();
}