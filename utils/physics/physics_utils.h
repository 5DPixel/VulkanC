#pragma once

#include "../../math/math_utils.h"
#include "../constants_and_arrays/constants_and_arrays.h"

typedef enum {
    RAYCAST_SUCCESSFUL,
    RAYCAST_COULD_NOT_COMPLETE,
    RAYCAST_UNSUCCESSFUL
} RaycastResult;

typedef struct {
    RaycastResult result;
    vec3 resultPosition;
} PhysicsRaycastResult;

PhysicsRaycastResult physicsRaycast(vec3 position, vec3 direction, uint32_t rowCol, GameObject* objects);