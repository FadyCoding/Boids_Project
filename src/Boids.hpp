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
		glm::vec2 _position;
        glm::vec2 _velocity;
        int             _id;



    public:

        //Default construcor
        Boid()
            : _position(glm::vec2(0.0f)), _velocity(glm::vec2(0.0f)),_id(int(0)){};
        

        // Constructor
        Boid(glm::vec2 pos, glm::vec2 vel, int boidID)
            : _position(pos), _velocity(vel), _id(boidID){};
            

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
        void alignment(std::vector<Boid> neighbors_list, float protected_dist, const int num_boids, float modifier);

};


#endif // !BOIDS_CLASS_H
