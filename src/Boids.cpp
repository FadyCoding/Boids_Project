#include"Boids.hpp"


//Getters
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

//Setters

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
    

   //this->_position = pos;
}

void Boid::set_velocity(glm::vec2 vel)
{
    this->_velocity = vel;
}

void Boid::set_ID(const int boidID)
{
    this->_id = boidID;
}

//Drawing
void Boid::draw_Boid(p6::Context& ctx)
{

    ctx.stroke_weight = 0.005f;
    ctx.use_stroke    = false;
    ctx.use_fill      = true;

    ctx.equilateral_triangle(
        p6::Center{this->_position.x, this->_position.y},
        p6::Radius{0.03f}
    );

}

//Update methods
void Boid::update_Boid_position(const float dTime)
{
    set_position(this->_position + this->_velocity * dTime);   
}

void Boid::separation(std::vector<Boid>& boids_list, const float protected_dist)
{
    // no modification of boids and less costly to copy
    for (const auto&boid : boids_list)
    {
        //if (this != &boids_list[i])
        if (this->_id != boid._id)
        {
            // Calculates the position between this and boid who is neighbor
            float dist_euclid = std::sqrt(std::pow(this->_position.x - boid._position.x, 2) + std::pow(this->_position.y - boid._position.y, 2));

            if (dist_euclid < protected_dist)
            {

                //Calculate separation vector 
                glm::vec2 separation = this->_position - boid._position;

                //Normalize the previous vector
                separation = separation / dist_euclid;

                // Scale separation vector based on distance and apply to velocity
                this->_velocity += separation * (protected_dist - dist_euclid) / protected_dist;

            }

        }

    }
}

void Boid::alignment(std::vector<Boid>& neighbors_list, const float protected_dist, float modifier, const float max_speed)//, distance_func_ptr dist_func)
{
    //Initialization of average speed variables
    float _xvel_avg, _yvel_avg;
    _xvel_avg = 0.0;
    _yvel_avg = 0.0;

    // counter for neighbors in protected distance
    int neighbors_count = 0;
    
    // no modification of boids and less costly to copy
    for (const auto& neighbor : neighbors_list)
    {
        //std::cout << this->_id << std::endl;

        if (this->_id != neighbor._id)
        {
            //std::cout << this->_id << std::endl;


            //Calculates the position between this and boid who is neighbor
           // double dist_euclid = dist_func(this->_position, neighbor._position);

            float dist_euclid = std::sqrt(std::pow(this->_position.x - neighbor._position.x, 2) + std::pow(this->_position.y - neighbor._position.y, 2));

            if (dist_euclid < protected_dist)
            {
                //We match the neighbor velocity to its neighbor
                
                _xvel_avg += neighbor._velocity.x;
                _yvel_avg += neighbor._velocity.y;
                neighbors_count += 1;

            }
            
        }
    }
    //Debug test
    
    //std::cout << neighbors_count << std::endl;
    //std::cout << _xvel_avg << std::endl;
    //std::cout << _yvel_avg << std::endl;

    if (neighbors_count > 0)
    { 

        // Match the velocity to the average of the boid group
        _xvel_avg = _xvel_avg / static_cast<float>(neighbors_count);
        _yvel_avg = _yvel_avg / static_cast<float>(neighbors_count);

    }

    glm::vec2 temp(this->_velocity.x + std::abs(_xvel_avg - this->_velocity.x) * modifier, this->_velocity.y + std::abs(_yvel_avg - this->_velocity.y) * modifier);


    if (glm::length(temp) > max_speed)
    {
        temp = glm::normalize(temp) * max_speed;
    }

    this->set_velocity(temp);

}


void Boid::cohesion(const std::vector<Boid>& neighbors_list, const float protected_dist, const float centering)
{
    glm::vec2 center_of_mass(0.0f, 0.0f);
    int       neighbors_count = 0;

    // no modification of boids and less costly to copy
    for (const auto& neighbor : neighbors_list)
    {
        const float distance = glm::distance(this->_position, neighbor._position);
        if (distance > 0.0f && distance < protected_dist)
        {
            center_of_mass += neighbor._position;
            neighbors_count++;
        }
    }

    if (neighbors_count > 0)
    {
        center_of_mass /= static_cast<float>(neighbors_count);
        glm::vec2 cohesion_vector = (center_of_mass - this->_position) * centering;
        this->set_velocity(this->_velocity + cohesion_vector);
    }
}

void Boid::draw_Shark(p6::Context& ctx)
{
    ctx.stroke_weight = 0.005f;
    ctx.use_stroke    = false;
    ctx.use_fill      = true;

    ctx.equilateral_triangle(
        p6::Center{this->_position.x, this->_position.y},
        p6::Radius{0.06f}
    );

}

void Boid::obstacle(p6::Context& ctx)
{


}



