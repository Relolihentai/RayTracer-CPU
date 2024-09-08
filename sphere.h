#ifndef SPHERE_H
#define SPHERE_H

#include "sceneObject.h"
#include "vec3.h"

class sphere : public sceneObject
{
    public : 
        sphere();
        sphere(vec3 center, double radius, std::shared_ptr<material> mat_ptr) 
                : center(center), radius(radius), mat_ptr(mat_ptr){};
        virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;
    public :
        vec3 center;
        double radius;
        std::shared_ptr<material> mat_ptr;
};



#endif