//
//  material.h
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/4.
//

#ifndef material_h
#define material_h

#include "utils.h"

struct hit_record;

class material {
public:
    virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered)const=0;
};

class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {}
    
    virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_dir = rec.normal + random_on_unit_sphere();
        if (scatter_dir.near_zero()) {
            scatter_dir = rec.normal;
        }
        scattered = ray(rec.p, scatter_dir);
        attenuation = albedo;
        
        return true;
    }
    
public:
    color albedo;
};

class metal : public material {
public:
    metal(const color& a) : albedo(a) {}
    
    virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto reflect_dir = reflect(unit_vector(ray_in.direction()), rec.normal);
        
        scattered = ray(rec.p, reflect_dir);
        attenuation = albedo;
        
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    
public:
    color albedo;
};


#endif /* material_h */
