#ifndef SCENE_OBJECT_LIST_H
#define SCENE_OBJECT_LIST_H

#include "sceneObject.h"
#include <memory>
#include <vector>

class sceneObjectList : public sceneObject
{
    public :
        sceneObjectList(){};
        sceneObjectList(std::shared_ptr<sceneObject> object) { add(object);};

        void clear() {objects.clear();}
        void add(std::shared_ptr<sceneObject> object) {objects.push_back(object);}

        virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;
    public :
        std::vector<std::shared_ptr<sceneObject>> objects;
};

#endif