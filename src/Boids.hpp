#ifndef BOIDS_CLASS_H
#define BOIDS_CLASS_H


#include "commonh.hpp"
#include "Obstacle.hpp"


class Boid 
{
	private:
		glm::vec2 _position;
        glm::vec2 _velocity;
        int             _id;
        //float     _turnfactor = 0.f;



    public:

        //Default construcor
        Boid()
            : _position(glm::vec2(0.0f)), _velocity(glm::vec2(0.0f)), _id(int(0)){};//, _turnfactor(float(0.0f)){};
        

        // Constructor
        Boid(glm::vec2 pos, glm::vec2 vel, int boidID, float boid_turnfactor)
            : _position(pos), _velocity(vel), _id(boidID){}; //, _turnfactor(boid_turnfactor){};
            

        // Destructor
        ~Boid() {}

    //  Methods
        //  Getters
        glm::vec2 get_position();
        glm::vec2 get_velocity();
        std::size_t      getID();
        //float       get_turnfactor();

        //  Setters
        void set_position(glm::vec2 pos);
        void set_velocity(glm::vec2 vel);
        void set_ID(const int boidID);
        //void set_turnfactor(float boid_turnfactor);

        //  Draw method
        void draw_Boid(p6::Context& ctx);
        void draw_Shark(p6::Context& ctx);

 

    //  Update method
        void update_Boid_position(const float dTime);
        // Pass the boid and neighbors list with a reference so we don't copy everytime the list
        void separation(std::vector<Boid>& boids_list, const float protected_dist); 
        void alignment(std::vector<Boid>& neighbors_list, const float protected_dist, const float modifier, const float max_speed);
        void cohesion(const std::vector<Boid>& neighbors_list, const float protected_dist, const float centering);

        //  Other behaviors
        void avoid_object(Obstacle* obst_ptr, float avoidance_distance, float max_speed, float avoidance_strength);

        //  Maths functions that depends on the boid class 
        static float euclidian_distance(const Boid& b1, const Boid& b2) {
            float distance = std::sqrt(std::pow(b1._position.x - b2._position.x, 2) + std::pow(b1._position.y - b2._position.y, 2));
            return distance;
        }

                
};



#endif // !BOIDS_CLASS_H
