#include <cstdlib>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "Boids.hpp"

//nota bene: ////////////////////////////////////////
    //faire passer des methodes avec des references 
    // name your boolean functions IfFunctionName
/////////////////////////////////////////////////////

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
    glm::vec2 vel1(1.0f, 1.0f);
    boid_test.set_velocity(vel1);

    // Random coordinates
    glm::vec2 pos_min(-2.0f, -1.0f);
    glm::vec2 pos_max(2.0f, 1.0f);
    glm::vec2 vel_min(-2.0f, -2.0f);
    glm::vec2 vel_max(2.0f, 2.0f);



    //Initiate boid vector
    const int num_boids = 5;
    std::vector<Boid> boids;
    for (int i = 0; i < num_boids; i++)
    {   
        boid.set_position(p6::random::point(pos_min, pos_max));
        boid.set_velocity(p6::random::point(vel_min, vel_max)); 
        boids.push_back(boid); // add the boid to the vector
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {

        

        ctx.background(p6::NamedColor::BallBlue);
        ctx.stroke_weight = 0.005f;
        ctx.use_stroke    = false;
        ctx.use_fill      = true;

        boid_test.draw_Boid(ctx);
       // glm::to_string(pos1);
        boid_test.update_Boid_position(0.0001f);
       // glm::to_string(pos1);

        //no modification of boids and less costly to copy
        for (auto& boid : boids)
        {
            boid.draw_Boid(ctx);
            boid.update_Boid_position(0.01f);
        }

        


    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}


/*
    ctx.circle(
    p6::Center{ctx.mouse()},
    p6::Radius{0.05f}
);
*/