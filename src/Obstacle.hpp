#ifndef OBSTACLE_CLASS_H
#define OBSTACLE_CLASS_H

#include "commonh.hpp"


class Obstacle {

    private:
        glm::vec2 _position;
        glm::vec2 _velocity;
        float     _radius;


    public:
        // Default construcor
        Obstacle()
            : _position(glm::vec2(0.0f)), _velocity(glm::vec2(0.0f)), _radius(float(0.0f)){};

        // Constructor
        Obstacle(glm::vec2 pos, glm::vec2 vel, float rad)
            : _position(pos), _velocity(vel), _radius(rad){};

        // Destructor
        ~Obstacle() {}
        
        //  Getters
        glm::vec2 get_position();
        glm::vec2 get_velocity();
        float     get_radius();


        // Methods
        void draw_sphere(p6::Context& ctx);

};

#endif // !OBSTACLE_CLASS_H