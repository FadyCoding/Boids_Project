#include"Boids.hpp"


glm::vec2 Boid::get_position()
{
    return this->position;
}

glm::vec2 Boid::get_velocity()
{
    return this->velocity;
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

void Boid::separation(glm::vec2 neighbors)
{

}
