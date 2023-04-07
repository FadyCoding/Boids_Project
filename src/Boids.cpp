#include"Boids.hpp"

//size_t Boid::next_id = 0; initialize the static variable to 0

glm::vec2 Boid::get_position()
{
    return this->position;
}

glm::vec2 Boid::get_velocity()
{
    return this->velocity;
}

    std::size_t Boid::getID()
{
    return this->id;
}

void Boid::set_position(glm::vec2 pos)
{
    if (pos.x < -2.0f)
    {
        
        this->position.x = 2.0f - std::abs(pos.x + 2.0f);
    }
    else
    {
        if (pos.x > 2.0f)
        {
            this->position.x = -2.0f + std::abs(pos.x - 2.0f);
        }
        else
        {
            this->position.x = pos.x;
        }
    }

    if (pos.y < -1.0f)
    {
        this->position.y = 1.0f - std::abs(pos.y + 1.0f);
    }
    else
    {
        if (pos.y > 1.0f)
        {
            this->position.y = -1.0f + std::abs(pos.y - 1.0f);
        }
        else
        {
            this->position.y = pos.y;
        }
    }

    
}

void Boid::set_velocity(glm::vec2 vel)
{
    this->velocity = vel;
}

void Boid::set_ID(int boidID)
{
    this->id = boidID;
}


void Boid::draw_Boid(p6::Context& ctx)
{

    ctx.stroke_weight = 0.005f;
    ctx.use_stroke    = false;
    ctx.use_fill      = true;

    ctx.equilateral_triangle(
        p6::Center{this->position.x, this->position.y},
        p6::Radius{0.05f}
    );

}

void Boid::update_Boid_position(float dTime)
{
    set_position(this->position + this->velocity * dTime);
    //this->position += this->velocity * dTime; //cette merde
   
  
}

void Boid::separation(std::vector<Boid> boids_list, float protected_dist, const int num_boids)
{
    
    //std::cout << boids_list[10].get_id() << std::endl;
    std::cout << this->id << std::endl;

    for (size_t i = 0; i < num_boids; i++)
    {

        //if (this != &boids_list[i])
        if (this->id != boids_list[i].getID())
        {

            float dist_euclid = std::sqrt(std::pow(this->position.x - boids_list[i].get_position().x, 2) + std::pow(this->position.y - boids_list[i].get_position().y, 2));
            if (this->id == 0)
            {
                std::cout << dist_euclid << std::endl;
            }
            if (dist_euclid < protected_dist)
            {
                //Sleep(100);
                this->set_velocity(- boids_list[i].get_velocity());
                boids_list[i].set_velocity(- this->get_velocity());
            }

        }

    }
}
