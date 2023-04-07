#ifndef BOIDS_CLASS_H
#define BOIDS_CLASS_H

#include<Windows.h>
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
        int             id;



    public:

        //Default construcor
        Boid()
            : position(glm::vec2(0.0f)), velocity(glm::vec2(0.0f)),id(int(0)){};
        

        // Constructor
        Boid(glm::vec2 pos, glm::vec2 vel, int boidID)
            : position(pos), velocity(vel), id(boidID){};
            

        // Destructor
        ~Boid() {}

    //Methods
        //getters
        glm::vec2 get_position();
        glm::vec2 get_velocity();
        std::size_t      getID();

        //setters
        void set_position(glm::vec2 pos);
        void set_velocity(glm::vec2 vel);
        void set_ID(int boidID);

        //draw method
        void draw_Boid(p6::Context& ctx);

        //update method
        void update_Boid_position(float dTime);
        void separation(std::vector<Boid> boids_list, float protected_dist, const int num_boids);

};


#endif // !BOIDS_CLASS_H
