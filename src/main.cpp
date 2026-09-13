#include<iostream>
#include<cmath>
#include<sstream>
#include<vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
void processInput(RenderWindow &window);

struct data{

    float time;
    float position;
    float velocity;
    float KE;
    float PE;
};

int main(){

float k,x,m;
float w,f,T,TE;
const float PI = 3.14159;

std::cout <<"########################################################################################\n";
std::cout <<"######################### SIMULATION INPUTS PANEL ######################################\n";
std::cout <<"########################################################################################\n";
std::cout << "\n";
std::cout << "Enter the Spring constant (K) in 'N/m': ";
std::cin >> k;
std::cout << "Enter the Spring initial Elongation (x) in 'm': ";
std::cin >> x;
std::cout << "Enter the Mass of the Block (m) in 'kg': ";
std::cin >> m;
std::cout << "\n";

w = sqrt(k/m);
T = (2.0f*PI)/w;
f = 1/T;
TE = (0.5)*k*(x*x);

std::cout << "########################################################################################\n";
std::cout << "#################################### ASSUMPTIONS ######################################\n";
std::cout << "########################################################################################\n";
std::cout << "\n";
std::cout << "1.We neglect Friction anywhere, for keeping things simple.\n";
std::cout << "2.We assume that, the initial velocity is zero, as we release it after elongation.\n";
std::cout << "3.We assume that, the Spring used is an 'Ideal Spring' case.\n";
std::cout << "4.We assume that, the wall/floor and block to be 'Rigid bodies'.\n";
std::cout << "\n";
std::cout << "########################################################################################\n";
std::cout << "########################## PRE-SIMULATION DATA PREVIEW #################################\n ";
std::cout << "########################################################################################\n";
std::cout << "\n";
std::cout << "[System]: Horizontal Spring-Mass Oscillator\n";
std::cout << "[Orientation]: Wall anchored on Left. Positive displacement (+) = Elongation to Right.\n";
std::cout << "\n";
std::cout << "> Angular Frequency (omega) : "<< w <<" rad/s.\n";
std::cout << "> Natural Frequency (f)     : "<< f <<" Hz.\n";
std::cout << "> Period of Oscillation (T) : "<< T <<" s.\n";
std::cout << "> Total System Energy (E)   : "<< TE <<" J. (Conserved)\n";
std::cout << "\n";
std::cout << "########################################################################################\n";
std::cout << "#################################### USER CONTROLS ######################################\n";
std::cout << "########################################################################################\n";
std::cout << "\n";
std::cout << "---> Press 'ESCAPE' to Exit out of the simulation.\n";
std::cout << "---> Press 'SPACE' to Record Readings into the displayed table (5 data can be recorded)\n";
std::cout << "---> Press 'R' to Reset the simulation.\n";
std::cout << "\n";
std::cout << "PRESS 'S' TO START THE SIMULATION WINDOW! \n";
std::cout << "########################################################################################\n";
std::string start;
std::cin >> start;


    RenderWindow window(VideoMode({800,600}), "Spring-Mass-Simulation", Style::Default);
    // Prevents GPU overheating and limits loop to monitor refresh rate
    window.setVerticalSyncEnabled(true); 

    // to measure time between frames (dt)
    Clock deltaClock;

    RectangleShape wall;
    wall.setFillColor(Color::White);
    wall.setPosition({150,200});
    wall.setSize(Vector2f({10,100}));

    RectangleShape floor;
    floor.setFillColor(Color::White);
    floor.setPosition({160,290});
    floor.setSize(Vector2f({250,10}));

    RectangleShape block;
    block.setFillColor(Color::Red);
    block.setPosition({270,250});
    block.setSize(Vector2f({40,40}));

 
  Font font;
  // Set the font to our message
  Text TimeText(font);
  Text PositionText(font);
  Text VelocityText(font);
  Text KineticText(font);
  Text PotentialText(font);
  if (!font.openFromFile("Fonts/RobotoMono-MediumItalic.ttf"))
  {
    std::cerr << "Failed to load font file!" << std::endl;
    return -1;
  }
  // Assign the actual message
  TimeText.setString("Time passed : ");
  PositionText.setString("Real-time position (x): ");
  VelocityText.setString("Real-time velocity (v): ");
  KineticText.setString("Real-time Kinetic Energy (KE): ");
  PotentialText.setString("Real-time Potential Energy (PE): ");

  TimeText.setCharacterSize(20);
  PositionText.setCharacterSize(15);
  VelocityText.setCharacterSize(15);
  KineticText.setCharacterSize(15);
  PotentialText.setCharacterSize(15);

  TimeText.setFillColor(Color::Yellow);
  PositionText.setFillColor(Color::Yellow);
  VelocityText.setFillColor(Color::Yellow);
  KineticText.setFillColor(Color::Yellow);
  PotentialText.setFillColor(Color::Yellow);
  
  PositionText.setPosition({50.f, 320.f});     
  TimeText.setPosition({50, 70.f}); 
  VelocityText.setPosition({50, 350});
  KineticText.setPosition({50, 380});
  PotentialText.setPosition({50,410});

    
  float totalTime = 0.0f;

    // render Loop
    while (window.isOpen())
    {
        
        // physicalTime is the fraction of a second the last frame took to render
        Time deltaTime = deltaClock.restart();
        float dt = deltaTime.asSeconds();
        totalTime += dt;

    float currentX = x*cos(w*totalTime);
    float currentV = -x*w*sin(w*totalTime);
    float currentKE = (0.5)*m*(currentV*currentV);
    float currentPE = (0.5)*k*(currentX*currentX);

    float pixelTOmeter = 3.f;

    block.move(Vector2f({currentX*pixelTOmeter, 0.0f}));

        // Update the score text
      std::stringstream ssTime, ssPos, ssVel, ssKE, ssPE;

ssTime << "Time passed : " << std::fixed << std::setprecision(2) << totalTime << " s";
ssPos  << "Real-time position (x): " << std::fixed << std::setprecision(2) << currentX << " m";
ssVel  << "Real-time velocity (v): " << std::fixed << std::setprecision(2) << currentV << " m/s";
ssKE   << "Real-time Kinetic Energy (KE): " << std::fixed << std::setprecision(2) << currentKE << " J";
ssPE   << "Real-time Potential Energy (PE): " << std::fixed << std::setprecision(2) << currentPE << " J";

// Bind string to text entities
TimeText.setString(ssTime.str());
PositionText.setString(ssPos.str());
VelocityText.setString(ssVel.str());
KineticText.setString(ssKE.str());
PotentialText.setString(ssPE.str());



        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){ 
             window.close();
            }
        }

        processInput(window);

        window.clear(sf::Color(30, 30, 35)); 

         window.draw(TimeText);
         window.draw(PositionText);
         window.draw(VelocityText);
         window.draw(KineticText);
         window.draw(PotentialText);


        window.draw(wall);
        window.draw(floor);
        window.draw(block);

        window.display();
    }


    return 0;
}
void processInput(RenderWindow &window){
    if(Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
        window.close();
    }
    if(Keyboard::isKeyPressed(Keyboard::Scan::Space)){
        
    }
    if(Keyboard::isKeyPressed(Keyboard::Scan::R)){
        
    }
}