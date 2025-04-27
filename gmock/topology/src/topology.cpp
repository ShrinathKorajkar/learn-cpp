
#include "topology.h"

using namespace std;

Topology::Topology(const Listener& listener)
  : m_listener(listener)
{
}

void Topology::requestTopology(size_t width, size_t height)
{
    m_listener(width, height);
}
