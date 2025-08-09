#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>

int Frame_limit = 0;
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
    sf::Vector2f n = sf::Vector2f(A.y - B.y,B.x - A.x);
    float dv = (float)std::sqrt(n.x * n.x + n.y * n.y);
    n = (n * do_day) / (2 * dv);

    sf::Vertex diem [4] = {
        sf::Vertex(sf::Vector2f(A + n)),
        sf::Vertex(sf::Vector2f(B + n)),
        sf::Vertex(sf::Vector2f(B - n)),
        sf::Vertex(sf::Vector2f(A - n))
    };
    for(int i = 0;i <= 3;++i)   diem[i].color = color_code;
    x.draw(diem,4,sf::Quads);
}
namespace setting{
void logo(sf::RenderWindow &windows,sf::Event &event){
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
    sf::RenderWindow tab_setting(sf::VideoMode(200,150),"Setting");
    if(Frame_limit == 0)    tab_setting.setVerticalSyncEnabled(true);
    else    tab_setting.setFramerateLimit(Frame_limit);

    while(tab_setting.isOpen()){
        sf::Event event_in_tab;
        if(tab_setting.pollEvent(event_in_tab) && event_in_tab.type == sf::Event::Closed) tab_setting.close();
        if(windows.pollEvent(event) && event.type == sf::Event::Closed){
            tab_setting.close();
            windows.close();
        }

        tab_setting.clear(sf::Color::White);

        

        tab_setting.display();
    }
}
}
int n,m;
signed main()
{
    n = sf::VideoMode::getDesktopMode().width / 2;
    m = sf::VideoMode::getDesktopMode().height / 2;
    sf::RenderWindow windows(sf::VideoMode(n,m),"MyTab");
    
    if(Frame_limit == 0)    windows.setVerticalSyncEnabled(true); // Đồng bộ với tần số làm mới màn hình (VSync)
    else    windows.setFramerateLimit(Frame_limit);

    std::cout << n << " " << m << std::endl;
    
    while(windows.isOpen()){
        sf::Event event;
        while(windows.pollEvent(event)){
            if(event.type == sf::Event::Closed) windows.close();
            if(event.type == sf::Event::MouseButtonPressed){
                float x = sf::Mouse::getPosition(windows).x;
                float y = sf::Mouse::getPosition(windows).y;
                std::cout << x << " " << y << std::endl;
                if(735.f <= x && x <= 785.f && 15.f <= y && y <= 65.f)  setting::tab(windows,event);
            }
        }
        windows.clear(sf::Color::Black);
        
        draw_circle(sf::Vector2f(25.f,25.f),200.f,sf::Color(105,105,105),2000,windows);// vẽ hình tròn lớn
        draw_circle(sf::Vector2f(50.f,50.f),175.f,sf::Color::White,2000,windows);// vẽ hình tròn nhỏ
        draw_reg(sf::Vector2f(450.f,0.f),sf::Vector2f(350.f,450.f),sf::Color::White,windows);// vẽ hình chữ nhật bên phải
        draw_line(sf::Vector2f(225.f,225.f),sf::Vector2f(225.f,60.f),10.0,sf::Color::Red,windows);
        draw_line(sf::Vector2f(225.f,225.f),sf::Vector2f(225.f,100.f),20,sf::Color::Black,windows);
        setting::logo(windows,event);

        windows.display();
    }
    return 0;
}