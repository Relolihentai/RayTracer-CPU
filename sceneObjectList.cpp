#include "sceneObjectList.h"

bool sceneObjectList::hit(const ray& r, double tmin, double tmax, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = tmax;

    for (const auto& object : objects) {
        if (object->hit(r, tmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}