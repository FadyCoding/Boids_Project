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
    

   //this->_position = pos;
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
}

void Boid::separation(std::vector<Boid> boids_list, float protected_dist, const int num_boids)
{
    
    //std::cout << this->_id << std::endl;

    for (size_t i = 0; i < num_boids; i++)
    {

        //if (this != &boids_list[i])
        if (this->_id != boids_list[i].getID())
        {
            // Calculates the position between this and boid who is neighbor
            float dist_euclid = std::sqrt(std::pow(this->_position.x - boids_list[i].get_position().x, 2) + std::pow(this->_position.y - boids_list[i].get_position().y, 2));
            /*
            if (this->_id == 0)
            {
                std::cout << dist_euclid << std::endl;
            }
            */ 
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

void Boid::alignment(std::vector<Boid> neighbors_list, float protected_dist, const int num_boids, float modifier, float max_speed)
{
    //Initialization of average speed variables
    float _xvel_avg, _yvel_avg;
    _xvel_avg = 0.0;
    _yvel_avg = 0.0;

    //counter
    int neighbors_count = 0;
    

    std::cout << this->get_velocity().x << std::endl;


    for (size_t i = 0; i < num_boids; i++)
    {
        //std::cout << this->_id << std::endl;

        if (this->_id != neighbors_list[i].getID())
        {
            //std::cout << this->_id << std::endl;


            //Calculates the position between this and boid who is neighbor
            float dist_euclid = std::sqrt(std::pow(this->_position.x - neighbors_list[i].get_position().x, 2) + std::pow(this->_position.y - neighbors_list[i].get_position().y, 2));

            if (dist_euclid < protected_dist)
            {

                //We match the neighbor velocity to its neighbor
                
                _xvel_avg += neighbors_list[i].get_velocity().x;
                _yvel_avg += neighbors_list[i].get_velocity().y;
                neighbors_count += 1;

            }
            
        }
    }
    //std::cout << neighbors_count << std::endl;
    //std::cout << _xvel_avg << std::endl;
    //std::cout << _yvel_avg << std::endl;

    if (neighbors_count > 0)
    {
        // Match the velocity to the average of the boid group
        _xvel_avg = _xvel_avg / neighbors_count;
        _yvel_avg = _yvel_avg / neighbors_count;

    }

    glm::vec2 temp(this->_velocity.x + std::abs(_xvel_avg - this->_velocity.x) * modifier, this->_velocity.y + std::abs(_yvel_avg - this->_velocity.y) * modifier);


    if (glm::length(temp) > max_speed)
    {
        temp = glm::normalize(temp) * max_speed;
    }

    this->set_velocity(temp);

}

void Boid::cohesion(std::vector<Boid> neighbors_list, float protected_dist, const int num_boids, float centering)
{
    float xpos_avg, ypos_avg;
    xpos_avg = 0.0;
    ypos_avg = 0.0;

    for (size_t i = 0; i < num_boids; i++)
    {
        if (this->_id != neighbors_list[i].getID())
        {
            // Calculates the position between this and boid who is neighbor
            float     dist_euclid = std::sqrt(std::pow(this->_position.x - neighbors_list[i].get_position().x, 2) + std::pow(this->_position.y - neighbors_list[i].get_position().y, 2));

            if (dist_euclid < protected_dist)
            {
                glm::vec2 pos_avg(xpos_avg + neighbors_list[i]._position.x, ypos_avg + neighbors_list[i]._position.y);
                set_position(pos_avg);
            }

        }
    }

    if (neighbors_list.size() > 0)
    {
        xpos_avg = xpos_avg / neighbors_list.size();
        ypos_avg = ypos_avg / neighbors_list.size();

    }

    glm::vec2 temp(this->_velocity.x + (xpos_avg - this->_velocity.x) * centering, this->_velocity.y + (xpos_avg - this->_velocity.y) * centering);
    this->set_velocity(temp);

}