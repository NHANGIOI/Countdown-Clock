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
    sf::RenderWindow tab_setting(sf::VideoMode(350,200),"Setting");

    sf::Font Consolas;//thêm font chữ consolas(regular)
    if(Consolas.loadFromFile("Consolas-Regular.ttf") == false){
        exit(-1);
    }
    
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
                std::cout << x << " " << y << std::endl;

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
int n,m;
signed main()
{
    n = sf::VideoMode::getDesktopMode().width / 2;
    m = sf::VideoMode::getDesktopMode().height / 2;
    sf::RenderWindow windows(sf::VideoMode(n,m),"MyTab");
    

    std::cout << n << " " << m << std::endl;
    
    while(windows.isOpen()){
        if(Frame_limit == 0)    windows.setVerticalSyncEnabled(true);
        else    windows.setFramerateLimit(Frame_limit);

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