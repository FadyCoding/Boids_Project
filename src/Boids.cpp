#include"Boids.hpp"

//size_t Boid::next_id = 0; initialize the static variable to 0

glm::vec2 Boid::get_position()
{
    return this->_position;
}

glm::vec2 Boid::get_velocity()
{
    return this->_velocity;
}

    std::size_t Boid::getID()
{
    return this->_id;
}

void Boid::set_position(glm::vec2 pos)
{
    if (pos.x < -2.0f)
    {
        
        this->_position.x = 2.0f - std::abs(pos.x + 2.0f);
    }
    else
    {
        if (pos.x > 2.0f)
        {
            this->_position.x = -2.0f + std::abs(pos.x - 2.0f);
        }
        else
        {
            this->_position.x = pos.x;
        }
    }

    if (pos.y < -1.0f)
    {
        this->_position.y = 1.0f - std::abs(pos.y + 1.0f);
    }
    else
    {
        if (pos.y > 1.0f)
        {
            this->_position.y = -1.0f + std::abs(pos.y - 1.0f);
        }
        else
        {
            this->_position.y = pos.y;
        }
    }

    
}

void Boid::set_velocity(glm::vec2 vel)
{
    this->_velocity = vel;
}

void Boid::set_ID(int boidID)
{
    this->_id = boidID;
}


void Boid::draw_Boid(p6::Context& ctx)
{

    ctx.stroke_weight = 0.005f;
    ctx.use_stroke    = false;
    ctx.use_fill      = true;

    ctx.equilateral_triangle(
        p6::Center{this->_position.x, this->_position.y},
        p6::Radius{0.05f}
    );

}

void Boid::update_Boid_position(float dTime)
{
    set_position(this->_position + this->_velocity * dTime);
    //this->position += this->velocity * dTime; //cette merde
   
  
}

void Boid::separation(std::vector<Boid> boids_list, float protected_dist, const int num_boids)
{
    
    std::cout << this->_id << std::endl;

    for (size_t i = 0; i < num_boids; i++)
    {

        //if (this != &boids_list[i])
        if (this->_id != boids_list[i].getID())
        {

            float dist_euclid = std::sqrt(std::pow(this->_position.x - boids_list[i].get_position().x, 2) + std::pow(this->_position.y - boids_list[i].get_position().y, 2));
            if (this->_id == 0)
            {
                std::cout << dist_euclid << std::endl;
            }
            if (dist_euclid < protected_dist)
            {

                //Calculate separation vector 
                glm::vec2 separation = this->_position - boids_list[i].get_position();

                //Normalize the previous vector
                separation = separation / dist_euclid;

                // Scale separation vector based on distance and apply to velocity
                this->_velocity += separation * (protected_dist - dist_euclid) / protected_dist;

            }

        }

    }
}

void Boid::alignment(std::vector<Boid> boids_list, float protected_dist, const int num_boids, float matchingfactor)
{
    //each boid tries to match the velocity of other boids inside its visible range
    for (size_t i = 0; i < num_boids; i++)
    {
        if (this->_id != boids_list[i].getID())
        {
            float dist_euclid = std::sqrt(std::pow(this->_position.x - boids_list[i].get_position().x, 2) + std::pow(this->_position.y - boids_list[i].get_position().y, 2));

            if (dist_euclid < protected_dist)
            {
                this->_velocity += boids_list[i]._velocity;

            }

        }

    }
}
