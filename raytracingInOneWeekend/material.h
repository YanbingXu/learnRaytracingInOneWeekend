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
    metal(const color& a, double fuzz) : albedo(a), fuzzy(fuzz > 1.0 ? 1.0 : fuzz) {}
    
    virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto reflect_dir = reflect(unit_vector(ray_in.direction()), rec.normal);
        
        scattered = ray(rec.p, reflect_dir + fuzzy * random_on_unit_sphere());
        attenuation = albedo;
        
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    
public:
    color albedo;
    double fuzzy;
};

class dielectric : public material {
public:
    dielectric(double index_of_refraction):ior(index_of_refraction){}
    
    virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1,1,1);
        double refraction_ratio = rec.front_face ? (1.0/ior) : ior;
        
        vec3 ray_in_unit = unit_vector(ray_in.direction());
        
        auto cos_theta = fmin(dot(-ray_in_unit, rec.normal),1.0);
        auto sin_theta = sqrt(1.0 - cos_theta*cos_theta);
        
        bool total_internal_reflect = sin_theta * refraction_ratio > 1.0;
        vec3 refract_dir;
        // why schlick > random number
        if(total_internal_reflect || reflectance(cos_theta, refraction_ratio) > random_double()){
            refract_dir = reflect(ray_in_unit, rec.normal);
        }else{
            refract_dir = refract(ray_in_unit, rec.normal, refraction_ratio);
        }
        
        scattered = ray(rec.p, refract_dir);
        return true;
    }
    
public:
    double ior;
private:
    static double reflectance(double cosine, double ior) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ior) / (1+ior);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};


#endif /* material_h */
