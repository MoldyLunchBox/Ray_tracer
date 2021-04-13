#include "../header/rt.h"

t_sol intersection_box(t_obj *box, t_ray ray)
{
t_sol t;
box->position = (t_vect){0,0,0};
    t_vect  close_corner = (t_vect){box->position.x + box->size, box->position.y + box->size, box->position.z - box->size};
    t_vect far_corner = (t_vect){box->position.x - box->size, box->position.y - box->size, box->position.z +box->size};
t.tmin = -1;
    double t1_x = (close_corner.x - ray.origine.x) / ray.direction.x;
    double t2_x = (far_corner.x - ray.origine.x) / ray.direction.x;
    double tx_min =  fmin(t1_x, t2_x);
    double tx_max =  fmax(t1_x, t2_x);

    double t1_y = (close_corner.y - ray.origine.y) / ray.direction.y;
    double t2_y = (far_corner.y - ray.origine.y) / ray.direction.y;
    double ty_min =  fmin(t1_y, t2_y);
    double ty_max =  fmax(t1_y, t2_y);

    double t1_z = (close_corner.z - ray.origine.z) / ray.direction.z;
    double t2_z = (far_corner.z - ray.origine.z) / ray.direction.z;
    double tz_min =  fmin(t1_z, t2_z);
    double tz_max =  fmax(t1_z, t2_z);

    if (fmin(fmin(tx_max, ty_max), tz_max) - fmax(fmax(tx_max, ty_max), tz_max) <= 0)
        return t;
        t.tmin = fmin(fmin(tx_max, ty_max), tz_max);
    t.tmin = -1;
    return (t);

}

