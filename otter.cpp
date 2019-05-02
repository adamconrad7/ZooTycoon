#include "otter.hpp"
#include "animal.hpp"

Otter::Otter() : Animal(1095, 5000, 2, 2, 250, "Sea Otter") {}

Otter::Otter(int age) : Animal(age, 5000, 2, 2, 250, "Sea Otter") {}
