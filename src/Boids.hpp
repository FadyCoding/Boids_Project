#ifndef BOIDS_CLASS_H
#define BOIDS_CLASS_H


#include<cstdlib>
#include<vector>
#include<cmath>
#include <p6/p6.h>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>



class Boid 
{
	private:
		glm::vec2 position;
        glm::vec2 velocity;

    public:
        //Default construcor
        Boid()
            : position(glm::vec2(0.0f)), velocity(glm::vec2(0.0f)) {}

        // Constructor
        Boid(glm::vec2 pos, glm::vec2 vel)
            : position(pos), velocity(vel) {}

        // Destructor
        ~Boid() {}

    //Methods
        //getters
        glm::vec2 get_position();
        glm::vec2 get_velocity();

        //setters
        void set_position(glm::vec2 pos);
        void set_velocity(glm::vec2 vel);

        //draw method
        void draw_Boid(p6::Context& ctx);

        //update method
        void update_Boid_position(float dTime);
        void separation(glm::vec2 neighbors);
};

#endif // !BOIDS_CLASS_H
