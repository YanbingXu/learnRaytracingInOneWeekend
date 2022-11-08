//
//  moving_sphere.h
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/8.
//

#ifndef moving_sphere_h
#define moving_sphere_h

#include "hittable.h"
#include "utils.h"

/*
 create a sphere class that has its center move linearly from center0 at time0 to center1 at time1. Outside that time interval it continues on, so those times need not match up with the camera aperture open and close.
 */
class moving_sphere : public hittable {
public:
    moving_sphere() {}
    moving_sphere(point3 cen0, point3 cen1, double tim0, double tim1, double r, shared_ptr<material>material):center0(cen0),center1(cen1), time0(tim0), time1(tim1), radius(r),mat(material) {};
    
    point3 center(double time) const;
    
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    
public:
    point3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<material>mat;
    
};

point3 moving_sphere::center(double time) const {
    return center0 + ((time-time0) / (time1-time0))*(center1-center0);
}

bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center(r.time());
    // simplify the hit sphere computation
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b * half_b-a*c;
    
    if (discriminant < 0) return false;
    
    // find the nearest root that lies in the acceptable range
    auto sqrt_discriminant = sqrt(discriminant);
    auto root = (-half_b - sqrt_discriminant) / a;
    if (root < t_min || t_max < root) {
        root =(-half_b + sqrt_discriminant) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
    auto outward_normal= (rec.p - center(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat;
    
    return true;
}


#endif /* moving_sphere_h */
