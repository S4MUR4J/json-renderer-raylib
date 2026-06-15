#include "component_utils.h"

#include <string>

#include "raylib.h"

auto HexToColor(const std::string& hex, float opacity) -> Color {
  const unsigned long rgb = std::stoul(hex.substr(1), nullptr, 16);
  return Color{
      .r = static_cast<unsigned char>(rgb >> 16 & 0xFF),
      .g = static_cast<unsigned char>(rgb >> 8 & 0xFF),
      .b = static_cast<unsigned char>(rgb & 0xFF),
      .a = static_cast<unsigned char>(opacity * 255.0F),
  };
}

auto DrawShape(const std::string& geometry, const Vector3& pos, const Vector3& scale, const Color& color) -> void {
  if (geometry == "Sphere") {
    DrawSphere(pos, scale.x * 0.5F, color);
    DrawSphereWires(pos, scale.x * 0.5F, 8, 16, GRAY);
  } else if (geometry == "Cylinder") {
    const Vector3 bottom = {.x=pos.x, .y=pos.y - (scale.y * 0.5F), .z=pos.z};
    const Vector3 top    = {.x=pos.x, .y=pos.y + (scale.y * 0.5F), .z=pos.z};
    DrawCylinderEx(bottom, top, scale.x * 0.5F, scale.x * 0.5F, 16, color);
    DrawCylinderWiresEx(bottom, top, scale.x * 0.5F, scale.x * 0.5F, 16, GRAY);
  } else if (geometry == "Cone") {
    const Vector3 bottom = {.x=pos.x, .y=pos.y - (scale.y * 0.5F), .z=pos.z};
    const Vector3 top    = {.x=pos.x, .y=pos.y + (scale.y * 0.5F), .z=pos.z};
    DrawCylinderEx(bottom, top, scale.x * 0.5F, 0.0F, 16, color);
    DrawCylinderWiresEx(bottom, top, scale.x * 0.5F, 0.0F, 16, GRAY);
  } else if (geometry == "Capsule") {
    const Vector3 start = {.x=pos.x, .y=pos.y - (scale.y * 0.5F), .z=pos.z};
    const Vector3 end   = {.x=pos.x, .y=pos.y + (scale.y * 0.5F), .z=pos.z};
    DrawCapsule(start, end, scale.x * 0.5F, 8, 8, color);
    DrawCapsuleWires(start, end, scale.x * 0.5F, 8, 8, GRAY);
  } else if (geometry == "Plane") {
    DrawPlane(pos, {.x=scale.x, .y=scale.z}, color);
  } else if (geometry == "Torus") {
    static Model model = LoadModelFromMesh(GenMeshTorus(0.3F, 1.0F, 16, 32));
    DrawModelEx(model, pos, {.x=0, .y=1, .z=0}, 0, scale, color);
    DrawModelWiresEx(model, pos, {.x=0, .y=1, .z=0}, 0, scale, GRAY);
  } else if (geometry == "Hemisphere") {
    static Model model = LoadModelFromMesh(GenMeshHemiSphere(0.5F, 8, 16));
    DrawModelEx(model, pos, {.x=0, .y=1, .z=0}, 0, scale, color);
    DrawModelWiresEx(model, pos, {.x=0, .y=1, .z=0}, 0, scale, GRAY);
  } else {
    DrawCube(pos, scale.x, scale.y, scale.z, color);
    DrawCubeWires(pos, scale.x, scale.y, scale.z, GRAY);
  }
}
