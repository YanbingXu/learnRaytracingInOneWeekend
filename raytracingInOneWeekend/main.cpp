//
//  main.cpp
//  raytracingInOneWeekend
//
//  Created by 徐雁冰edith on 2022/11/1.
//

#include <iostream>

#include "utils.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include "camera.h"

#include "material.h"

// Coloring background
color ray_color(const ray& r, const hittable& world, int depth_num){
    hit_record rec;
    
    if (depth_num <= 0) {
        return color(0.0, 0.0, 0.0);
    }
    
    if (world.hit(r, 0.001, infinity, rec)) {
        color attenuation;
        ray scattered;
        if (rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
            return attenuation * ray_color(scattered, world, depth_num-1);
        }
        return color(0,0,0);
        
    }
    
    vec3 unit_direction = unit_vector(r.direction()); // [-1, 1]
    auto t = 0.5 * (unit_direction.y() + 1.0); // [0,1]
    
    return (1.0 - t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

int main(int argc, const char * argv[]) {
    
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 256;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = 64;
    const int max_depth = 10;
    
    // World
    hittable_list world;
    
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    // auto material_center = make_shared<dielectric>(0.5);
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
    
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 20, aspect_ratio);
    
    // Render
    std::cout<<"P3\n"<<image_width<<' ' <<image_height<<"\n255\n";
    
    for (int j = image_height-1; j>=0; --j) {
        std::cerr<<"\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i=0; i<image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < sample_per_pixel; ++s) {
                auto u = double(i + random_double())/(image_width-1); // 需要随机偏一点
                auto v = double(j + random_double())/(image_height-1);
                ray r = cam.gen_ray(u,v);

                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, sample_per_pixel);
            
            // no aa
//            auto u = double(i )/(image_width-1);
//            auto v = double(j )/(image_height-1);
//            ray r = cam.gen_ray(u,v);
//            pixel_color =ray_color(r, world);
//            write_color(std::cout, pixel_color);
            
        }
    }
    std::cerr << "\nDone.\n";
    
    return 0;
}
