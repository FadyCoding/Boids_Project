#include <Obstacle.hpp>

//  Getters

glm::vec2 Obstacle::get_position()
{
    return this->_position;
}

glm::vec2 Obstacle::get_velocity()
{
    return this->_velocity;
}

float Obstacle::get_radius()
{
    return this->_radius;
}


//  Methods

void Obstacle::draw(p6::Context& ctx)
{
    ctx.stroke_weight = 0.005f;
    ctx.use_stroke    = false;
    ctx.use_fill      = true;

    ctx.circle(p6::Center{this->_position.x, this->_position.y}, p6::Radius{0.1f});
}