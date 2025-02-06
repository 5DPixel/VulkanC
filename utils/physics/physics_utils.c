#include "physics_utils.h"

PhysicsRaycastResult physicsRaycast(vec3 position, vec3 direction, uint32_t rowCol, GameObject* objects){
    PhysicsRaycastResult result;
    result.result = RAYCAST_COULD_NOT_COMPLETE;

    vec3 rayDir = normalize(direction);

    vec3 currentPos = position;

    for(uint32_t i = 0; i < pow(rowCol, 2); i++){
        vec3 aabbMin = subtract(objects[i].position, objects[i].scale);
        vec3 aabbMax = add(objects[i].position, objects[i].scale);

        if (checkAABBIntersection(currentPos, direction, aabbMin, aabbMax)) {
            objects[i].position.z = 1000.0f;
            result.result = RAYCAST_SUCCESSFUL;
            result.resultPosition = currentPos;
            break;
        }

        currentPos = add(currentPos, scale(rayDir, 0.2f));
    }

    result.resultPosition = currentPos;

    return result;
}