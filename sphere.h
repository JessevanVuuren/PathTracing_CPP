#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
  public:
    sphere(const point3 &center, double radius) : center(center), radius(fmax(0, radius)) {}

    bool hit(const ray &r, double ray_t_min, double ray_t_max, hit_record &rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0) return false;

        auto sqrt_d = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrt_d) / a;
        if (root <= ray_t_min || ray_t_max <= root) {
            root = (h + sqrt_d) / a;
            if (root <= ray_t_min || ray_t_max <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

  private:
    point3 center;
    double radius;
};

#endif