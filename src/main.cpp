#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "Boids.hpp"
#include "Obstacle.hpp"


int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "boids_project"}};
    ctx.maximize_window();

    // Boid instanciation.
    Boid boid, boid_test;
    // Sets position staticaly
    glm::vec2 pos1(-1.8f, 0.0f);
    boid_test.set_position(pos1);
    glm::vec2 vel1(4.0f, 0.0f);
    boid_test.set_velocity(vel1);

    // Position
    glm::vec2 pos_min(-2.0f, -1.0f);
    glm::vec2 pos_max(2.0f, 1.0f);

    // Velocity
    glm::vec2 vel_min(-20.0f, -20.0f);
    glm::vec2 vel_max(20.0f, 20.0f);

    

    //  Initialize boid vector
    const int num_boids = 60;

    //  Initialize boid's ID
    int BoidID = 0;

    //  Protected distance 
    float protected_dist = 0.1f;

    //  Max speed
    float max_speed = 50.0f;

    //  Modifier
    float modifier = 0.1f;

    //  Centering 
    float centering = 2.2f;

    //ptr function var
    //distance_func_ptr distance_func  = &euclidian_dist;


    std::vector<Boid> boids;
    for (int i = 0; i < num_boids; i++)
    {   
        BoidID = i;
        boid.set_position(p6::random::point(pos_min, pos_max)); //  sets a random position to each boid between a minimum and maximum
        boid.set_velocity(p6::random::point(vel_min, vel_max)); //  sets a random velocity to each boid between a minimum and maximum
        boid.set_ID(BoidID);                                    //  sets each boid's id 
        boids.push_back(boid);                                  //  add the boid to the vector
    }

    glm::vec2 sphere_pos(0.0f, 0.0f);
    glm::vec2 sphere_vel(0.0f, 0.0f);
    float     sphere_rad = 1.0f;
    /*
    //  Uncomment to have a obstacle
    Obstacle* sphere = new Obstacle(sphere_pos, sphere_vel, sphere_rad);

    */ 

    // Declare your infinite update loop.
    ctx.update = [&]() {

        ctx.background(p6::NamedColor::BallBlue);
        ctx.stroke_weight = 0.005f;
        ctx.use_stroke    = false;
        ctx.use_fill      = true;
        
        //  Draw the sphere obstacle
        //sphere->draw(ctx);

        
     
        
        for (auto& boid : boids)                                        //no modification of boids and less costly to copy
        {
           // boid.avoid_object(sphere, 2.0f, max_speed, 1.0f);
            boid.draw_Boid(ctx);
            boid.update_Boid_position(0.0001f);
            boid.separation(boids, protected_dist);
            boid.alignment(boids, protected_dist, modifier, max_speed); //, &euclidian_dist);
            boid.cohesion(boids, protected_dist, centering);
            
        }
    };


    // Should be done last. It starts the infinite loop.
    ctx.start();
}