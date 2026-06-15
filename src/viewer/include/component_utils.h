#ifndef COMPONENT_UTILS_H
#define COMPONENT_UTILS_H

#include <string>

#include "raylib.h"

auto HexToColor(const std::string& hex, float opacity) -> Color;
auto DrawShape(const std::string& geometry, const Vector3& pos, const Vector3& scale, const Color& color) -> void;

#endif /* COMPONENT_UTILS_H */
