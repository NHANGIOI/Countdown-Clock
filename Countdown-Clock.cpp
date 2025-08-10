#include<iostream>
#include<cmath>
#include <SFML/Graphics.hpp>
const float PI = 3.141592653589793f;
int Frame_limit = 0;
sf::Font Consolas;

void draw_circle(sf::Vector2f pos,float R,sf::Color color_code,int Point_Count,sf::RenderWindow &x){
    sf::CircleShape cir;
    cir.setPointCount(Point_Count);
    cir.setFillColor(color_code);
    cir.setRadius(R);
    cir.setPosition(pos);
    x.draw(cir);
}
void draw_reg(sf::Vector2f pos,sf::Vector2f sz,sf::Color color_code,sf::RenderWindow &x){
    sf::RectangleShape reg;
    reg.setSize(sz);
    reg.setPosition(pos);
    reg.setFillColor(color_code);
    x.draw(reg);
}
void draw_line(sf::Vector2f A,sf::Vector2f B,float do_day,sf::Color color_code,sf::RenderWindow &x){
    sf::Vector2f vn = sf::Vector2f(A.y - B.y,B.x - A.x);
    float dv = (float)std::sqrt(vn.x * vn.x + vn.y * vn.y);
    vn = (vn * do_day) / (2 * dv);

    sf::Vertex diem [4] = {
        sf::Vertex(sf::Vector2f(A + vn)),
        sf::Vertex(sf::Vector2f(B + vn)),
        sf::Vertex(sf::Vector2f(B - vn)),
        sf::Vertex(sf::Vector2f(A - vn))
    };
    for(int i = 0;i <= 3;++i)   diem[i].color = color_code;
    x.draw(diem,4,sf::Quads);
}
void draw_text(std::string vanban,sf::Font &FontU,int sz,sf::Vector2f pos,sf::Color color_code,sf::RenderWindow &windows){
    sf::Text tx;
    tx.setString(vanban);
    tx.setFont(FontU);
    tx.setCharacterSize(sz);
    tx.setPosition(pos);
    tx.setFillColor(color_code);
    windows.draw(tx);
}
namespace setting{
bool check_limit(float x,float y){
    if(x < 735.f || x > 785.f || y < 15.f || y > 65.f)  return false;
    return true;
}
void logo(sf::RenderWindow &windows){
    sf::Texture pic;
    if(pic.loadFromFile("logo_setting.png") == false){
        exit(-1);
    }
    sf::Sprite sp;
    sp.setTexture(pic);
    sp.setScale(0.1,0.1);
    sp.setPosition(sf::Vector2f(735.f,15.f));
    windows.draw(sp);
}
void tab(sf::RenderWindow &windows,sf::Event &event){
    sf::RenderWindow tab_setting(sf::VideoMode(350,200),"Setting");
    
    while(tab_setting.isOpen()){
        if(Frame_limit == 0)    tab_setting.setVerticalSyncEnabled(true);
        else    tab_setting.setFramerateLimit(Frame_limit);

        sf::Event event_in_tab;
        if(windows.pollEvent(event) && event.type == sf::Event::Closed){
            tab_setting.close();
            windows.close();
        }
        while(tab_setting.pollEvent(event_in_tab)){
            if(event_in_tab.type == sf::Event::Closed) tab_setting.close();
            if(event_in_tab.type == sf::Event::MouseButtonPressed){
                float x = sf::Mouse::getPosition(tab_setting).x;
                float y = sf::Mouse::getPosition(tab_setting).y;
                //std::cout << x << " " << y << std::endl;

                if(25.f <= x && x <= 150.f && 11.f <= y && y <= 63.f){ //(25,125) / (11,63) (Button fps 35)
                    Frame_limit = 35;
                }
                if(25.f <= x && x <= 150.f && 73.f <= y && y <= 125.f){ //(25,125) / (73,125)
                    Frame_limit = 60;
                }
                if(25.f <= x && x <= 150.f && 135.f <= y && y <= 187.f){ // (25,125) / (135,187)
                    Frame_limit = 0;
                }
            }
        }

        tab_setting.clear(sf::Color::White);

        draw_reg(sf::Vector2f(25,11),sf::Vector2f(125,52),(Frame_limit == 35 ? sf::Color(0,128,0) : sf::Color::Black),tab_setting);
        draw_reg(sf::Vector2f(25,73),sf::Vector2f(125,52),(Frame_limit == 60 ? sf::Color(0,128,0) : sf::Color::Black),tab_setting);
        draw_reg(sf::Vector2f(25,135),sf::Vector2f(125,52),(Frame_limit == 0 ? sf::Color(0,128,0) : sf::Color::Black),tab_setting);

        draw_text("35",Consolas,50,sf::Vector2f(60.f,3.f),sf::Color::White,tab_setting);
        draw_text("60",Consolas,50,sf::Vector2f(60.f,65.f),sf::Color::White,tab_setting);
        draw_text("auto",Consolas,50,sf::Vector2f(32.5f,125.f),sf::Color::White,tab_setting);
        tab_setting.display();
    }
}
}
namespace see_digit{
void draw(bool running,int sec,int min,int remain_time,sf::RenderWindow &windows){
    int remain_min,remain_sec;

    if(running == true){
        remain_min = remain_time / 60;
        remain_sec = remain_time % 60;
    }
    else{
        remain_min = min;
        remain_sec = sec;
    }
    draw_reg(sf::Vector2f(537.5,100),sf::Vector2f(175,65),sf::Color::Black,windows);
    draw_reg(sf::Vector2(543.75f,106.25f),sf::Vector2f(162.5f,52.5f),sf::Color(105,105,105),windows);
    draw_text((remain_min < 10 ? "0" : "") + std::to_string(remain_min) + ":" + (remain_sec < 10 ? "0" : "") + std::to_string(remain_sec)
    ,Consolas,45,sf::Vector2f(561.f,102.5f),sf::Color::Red,windows);
}
}
namespace Control_sec_button{
bool check_limit_minus(float x,float y){
    // x : 525 - 546
    // y : 229 - 247
    if(x < 525.f || x > 546.f || y < 229.f || y > 247.f)    return false;
    return true;
}
bool check_limit_plus(float x,float y){
    // x : 704 - 724
    // y : 227 - 249
    if(x < 704.f || x > 724.f || y < 227.f || y > 249.f)    return false;
    return true;
}
void draw(int &mask,sf::Clock &root_time,sf::Time checkpoint_time,sf::RenderWindow &windows){
    //draw minus button
    if(mask == 1){
        draw_line(sf::Vector2f(525.f,237.f),sf::Vector2f(548.f,237.f),4.f,sf::Color(0,128,0),windows);
        int delta = (root_time.getElapsedTime() - checkpoint_time).asMilliseconds();
        if(delta >= 500)   mask = 0;
    }
    else{
        draw_line(sf::Vector2f(525.f,237.f),sf::Vector2f(548.f,237.f),4.f,sf::Color::Black,windows);
    }
    //draw plus button
    if(mask == 2){
        draw_text("+",Consolas,50,sf::Vector2f(700,200),sf::Color(0,128,0),windows);
        int delta = (root_time.getElapsedTime() - checkpoint_time).asMilliseconds();
        if(delta >= 500)   mask = 0;
    }
    else{
        draw_text("+",Consolas,50,sf::Vector2f(700,200),sf::Color::Black,windows);
    }
    //write "sec"
    draw_text("sec",Consolas,50,sf::Vector2f(585,200),sf::Color::Black,windows);
}
}
namespace Control_min_button{
bool check_limit_minus(float x,float y){
    // x : 526 - 546
    // y : 303 - 322
    if(x < 525.f || x > 546.f || y < 303.f || y > 322.f)    return false;
    return true;
}
bool check_limit_plus(float x,float y){
    // x : 702 - 722
    // y : 301 - 324
    if(x < 704.f || x > 724.f || y < 301.f || y > 324.f)    return false;
    return true;
}
void draw(int &mask,sf::Clock &root_time,sf::Time checkpoint_time,sf::RenderWindow &windows){
    //draw minus button
    if(mask == 1){
        draw_line(sf::Vector2f(525.f,312.f),sf::Vector2f(548.f,312.f),4.f,sf::Color(0,128,0),windows);
        int delta = (root_time.getElapsedTime() - checkpoint_time).asMilliseconds();
        if(delta >= 500)   mask = 0;
    }
    else{
        draw_line(sf::Vector2f(525.f,312.f),sf::Vector2f(548.f,312.f),4.f,sf::Color::Black,windows);
    }
    //draw plus button
    if(mask == 2){
        draw_text("+",Consolas,50,sf::Vector2f(700,275),sf::Color(0,128,0),windows);
        int delta = (root_time.getElapsedTime() - checkpoint_time).asMilliseconds();
        if(delta >= 500)   mask = 0;
    }
    else{
        draw_text("+",Consolas,50,sf::Vector2f(700,275),sf::Color::Black,windows);
    }
    //write "min"
    draw_text("min",Consolas,50,sf::Vector2f(585,275),sf::Color::Black,windows);
}
}
namespace start_button{
bool check_limit_button(float x,float y){
    // x : 490 - 760
    //y : 375 - 400
    if(x < 490.f || x > 760.f || y < 375.f || y > 400.f)    return false;
    return true;
}
void draw(bool running,int total_time,int remain_time,sf::RenderWindow &windows){
    if(running == true){
        float d = (270.0/total_time) * (float)remain_time;
        draw_reg(sf::Vector2f(490,375),sf::Vector2f(d,25),sf::Color(105,105,105),windows);
        draw_text("Running",Consolas,27,sf::Vector2f(577.5f,367),sf::Color::Red,windows);
    }
    else{
        draw_reg(sf::Vector2f(490,375),sf::Vector2f(270,25),sf::Color(105,105,105),windows);
        draw_text("Start",Consolas,27,sf::Vector2f(589,368.5f),sf::Color::Red,windows);
    }
}
}
namespace reset_button{
bool check_limit_button(float x,float y){
    //x : 730 - 768
    //y : 114 - 152
    if(x < 730.f || x > 768.f || y < 114.f || y > 152.f)    return false;
    return true;
}
void draw(bool running,sf::RenderWindow &windows){
    if(running == false)    return;

    sf::Texture pic;
    if(pic.loadFromFile("logo_reset.png") == false){
        exit(-1);
    }
    sf::Sprite sp;
    sp.setTexture(pic);
    sp.setScale(0.1,0.1);
    sp.setPosition(sf::Vector2f(725.f,108.f));
    windows.draw(sp);
}
}
namespace main_clock{
void draw(bool running,int sec,int min,int remain_time,sf::RenderWindow &windows){
    int remain_min = 0,remain_sec = 0;
    if(running == true){
        remain_min = remain_time / 60;
        remain_sec = remain_time % 60;
    }
    else{
        remain_min = min;
        remain_sec = sec;
    }
    float x0 = 225.f;
    float y0 = 225.f;
    float alpha = (float)(2.f * PI / 60.f) * (float)remain_sec;
    float x = x0 + std::sin(alpha) * 165.f;
    float y = y0 - std::cos(alpha) * 165.f;
    draw_line(sf::Vector2f(x0,y0),sf::Vector2f(x,y),10.0,sf::Color::Red,windows);
    draw_circle(sf::Vector2f(x - 5,y - 5),5,sf::Color::Black,2000,windows);

    alpha = (float)(2.f * PI / 60.f) * (float)remain_min;
    x = x0 + std::sin(alpha) * 125.f;
    y = y0 - std::cos(alpha) * 125.f;
    draw_line(sf::Vector2f(x0,y0),sf::Vector2f(x,y),20,sf::Color::Black,windows);
    draw_circle(sf::Vector2f(x - 10,y - 10),10,sf::Color::Black,2000,windows);

    draw_circle(sf::Vector2f(215.f,215.f),10,sf::Color(30,144,255),2000,windows);
}
}
int n,m;
signed main()
{
    sf::Clock root_time;
    n = 800;
    m = 450;
    sf::RenderWindow windows(sf::VideoMode(n,m),"Countdown-Clock (ver 1.0)");

    //thêm font chữ consolas(regular)
    if(Consolas.loadFromFile("Consolas-Regular.ttf") == false){
        exit(-1);
    }

    int min = 0;
    int sec = 0;

    int mask_button_in_sec = 0;
    int mask_button_in_min = 0;
    sf::Time checkpoint_time_sec = root_time.getElapsedTime();
    sf::Time checkpoint_time_min = root_time.getElapsedTime();
    sf::Time start;
    bool running = false;

    while(windows.isOpen()){
        if(Frame_limit == 0)    windows.setVerticalSyncEnabled(true);
        else    windows.setFramerateLimit(Frame_limit);

        sf::Event event;
        while(windows.pollEvent(event)){
            if(event.type == sf::Event::Closed) windows.close();
            if(event.type == sf::Event::MouseButtonPressed){
                float x = sf::Mouse::getPosition(windows).x;
                float y = sf::Mouse::getPosition(windows).y;
                //std::cout << x << " " << y << std::endl;
                if(setting::check_limit(x,y))  setting::tab(windows,event);

                if(Control_sec_button::check_limit_minus(x,y)){
                    checkpoint_time_sec = root_time.getElapsedTime();
                    mask_button_in_sec = 1;
                    sec = (sec - 1 + 60) % 60;
                }
                else if(Control_sec_button::check_limit_plus(x,y)){
                    checkpoint_time_sec = root_time.getElapsedTime();
                    mask_button_in_sec = 2;
                    sec = (sec + 1) % 60;
                }

                if(Control_min_button::check_limit_minus(x,y)){
                    checkpoint_time_min = root_time.getElapsedTime();
                    mask_button_in_min = 1;
                    min = (min - 1 + 60) % 60;
                }
                else if(Control_min_button::check_limit_plus(x,y)){
                    checkpoint_time_min = root_time.getElapsedTime();
                    mask_button_in_min = 2;   
                    min = (min + 1) % 60;
                }
                if(start_button::check_limit_button(x,y) && running == false){
                    running = true;
                    start = root_time.getElapsedTime();
                }
                if(reset_button::check_limit_button(x,y) && running == true){
                    running = false;
                }
            }
        }
        windows.clear(sf::Color::Black);

        int total_time = min * 60 + sec;
        int remain_time = std::max(0,(int)(total_time - (root_time.getElapsedTime() - start).asSeconds()));

        draw_circle(sf::Vector2f(25.f,25.f),200.f,sf::Color(105,105,105),2000,windows);// vẽ hình tròn lớn
        draw_circle(sf::Vector2f(50.f,50.f),175.f,sf::Color::White,2000,windows);// vẽ hình tròn nhỏ
        draw_reg(sf::Vector2f(450.f,0.f),sf::Vector2f(350.f,450.f),sf::Color::White,windows);// vẽ hình chữ nhật bên phải

        see_digit::draw(running,sec,min,remain_time,windows);
        reset_button::draw(running,windows);
        Control_sec_button::draw(mask_button_in_sec,root_time,checkpoint_time_sec,windows);
        Control_min_button::draw(mask_button_in_min,root_time,checkpoint_time_min,windows);

        draw_reg(sf::Vector2f(480,365),sf::Vector2f(290,45),sf::Color::Black,windows);
        draw_reg(sf::Vector2f(490,375),sf::Vector2f(270,25),sf::Color::White,windows);
        start_button::draw(running,total_time,remain_time,windows);

        main_clock::draw(running,sec,min,remain_time,windows);
        setting::logo(windows);

        windows.display();
    }
    return 0;
}