#pragma once

#include <functional>

class Topology
{
public:
    using Listener = std::function<void(size_t, size_t)>;
    Topology(const Listener& listener);

    void requestTopology(size_t width, size_t height);

private:
    Listener m_listener;
};
