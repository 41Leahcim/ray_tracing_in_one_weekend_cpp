#pragma once

#include <memory>
#include <vector>

#include "Hittable.hpp"

struct HittableList : public Hittable {
    std::vector<std::shared_ptr<Hittable>> objects;

    inline HittableList() {}
    
    inline HittableList(std::shared_ptr<Hittable> object) : objects{object} {}

    inline void clear() {
        objects.clear();
    }

    inline void add(std::shared_ptr<Hittable> object){
        objects.push_back(object);
    }

    inline bool hit(const Ray& ray, const Interval ray_time, HitRecord& record) const override {
        bool hit_anything = false;
        double closest_so_far = ray_time.max;

        for(const std::shared_ptr<Hittable>& object : objects){
            HitRecord temp_record;
            if(object->hit(ray, Interval(ray_time.min, closest_so_far), temp_record)){
                hit_anything = true;
                closest_so_far = temp_record.time;
                record = temp_record;
            }
        }

        return hit_anything;
    }
};
