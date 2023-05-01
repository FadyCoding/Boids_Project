#ifndef BOIDS_CLASS_H
#define BOIDS_CLASS_H

#include<Windows.h>
#include<cstdlib>
#include<vector>
#include<cmath>
#include <p6/p6.h>
#include<glm/glm.hpp>
#include<glm/gtx/string_cast.hpp>

//typedef float(*distance_func_ptr)(glm::vec2, glm::vec2);

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
        void set_ID(const int boidID);

        //draw method
        void draw_Boid(p6::Context& ctx);
        void draw_Shark(p6::Context& ctx);
        void obstacle(p6::Context& ctx);
 

        //update method
        void update_Boid_position(const float dTime);
        // Pass the boid and neighbors list with a reference so we don't copy everytime the list
        void separation(std::vector<Boid>& boids_list, const float protected_dist); 
        void alignment(std::vector<Boid>& neighbors_list, const float protected_dist, const float modifier, const float max_speed); //, distance_func_ptr dist_func); 
        void cohesion(const std::vector<Boid>& neighbors_list, const float protected_dist, const float centering);

        
};

//Maths functions
//float euclidian_dist(glm::vec2 pos1, glm::vec2 pos2)
//{
//    return std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
//}


#endif // !BOIDS_CLASS_H
