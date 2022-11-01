////
////  main3.cpp
////  raytracingInOneWeekend
////
////  Created by 徐雁冰edith on 2022/11/1.
////
//
//#include <iostream>
//
//#include "color.h"
//#include "vec3.hpp"
//
//int main(int argc, const char * argv[]) {
//
//    // Image
//    const int image_width = 64;
//    const int image_height = 64;
//
//    // Render
//    std::cout<<"P3\n"<<image_width<<' ' <<image_height<<"\n255\n";
//
//    for (int j = image_height-1; j>=0; --j) {
//        std::cerr<<"\rScanlines remaining: " << j << ' ' << std::flush;
//        for (int i=0; i<image_width; ++i) {
//            auto r = double(i)/(image_width-1);
//            auto g = double(j)/(image_height-1);
//            auto b = 0.25;
//
////            int ir = static_cast<int>(255.999 * r);
////            int ig = static_cast<int>(255.999 * g);
////            int ib = static_cast<int>(255.999 * b);
////
////            std::cout<< ir <<' ' << ig <<' '<< ib <<'\n';
//
//            color pixel_color(r,g,b);
//            write_color(std::cout, pixel_color);
//        }
//    }
//    std::cerr << "\nDone.\n";
//
//    return 0;
//}
