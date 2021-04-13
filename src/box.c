#include "../header/rt.h"

t_sol intersection_box(t_obj *box, t_ray ray)
{
    t_obj plane;
    t_vect p1;
    t_vect d1;
    t_vect d2;
    double intersection;
    t_sol t;
     box->position= (t_vect){0,0,0};
    d1 = (t_vect){0,0,1};
    d2 = (t_vect){0,1,0};
    plane.direction = d1;
    p1 = add_vect(vect_mult_val(d2, box->size), box->position);
    plane.position = p1;

    t_vect hit_to_point;
    t = intersection_ray_plan(&plane, ray);
        plane.hit = add_vect(ray.origine, vect_mult_val(ray.direction,t.tmin));
    if (t.tmin != -1)
    {
        hit_to_point = sub_vect(p1,plane.hit);
    intersection = vect_scal(d2, hit_to_point);
    if (intersection < 0)
    {
        t.tmin = -1;
        return (t);
    }
    }



    return(t);





}

