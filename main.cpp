#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <random>

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 780

std::mt19937 mt_rand;



sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");

void drawLine(int x1, int y1, int x2, int y2) {
    sf::Vertex Line[2];
    Line[0] = sf::Vector2f(x1, y1);
    Line[1] = sf::Vector2f(x2, y2);
    Line[0].color = sf::Color::Red;
    Line[1].color = sf::Color::Red;
    window.draw(Line, 2, sf::Lines);
}




class Gene {
    int par[12] = {-12, -16, 36, 
                   -25, 74, -21, 
                   86, -34, 64, 
                   -23, 21, 65};
    
   public:

    void mutation() {
        int index= mt_rand() % 12;
        int mutation_value = 5-rand() % 11;
        par[index] += mutation_value;
    }

    friend class Form;
};

class Form {

    Gene m_gene;


    void shiftChoicer(int &NshiftX, int &NshiftY, int deepRec) {
        switch (deepRec) {
        case (6):
            NshiftX = m_gene.par[0];
            NshiftY = m_gene.par[1];
            break;
        case (5):
            NshiftX = m_gene.par[2];
            NshiftY = m_gene.par[3];
            break;
        case (4):
            NshiftX = m_gene.par[4];
            NshiftY = m_gene.par[5];
            break;
        case (3):
            NshiftX = m_gene.par[6];
            NshiftY = m_gene.par[7];
            break;
        case (2):
            NshiftX = m_gene.par[8];
            NshiftY = m_gene.par[9];
            break;
        case (1):
            NshiftX = m_gene.par[10];
            NshiftY = m_gene.par[11];
            break;
        default:
           std::cerr << "error\n shift choicer\n";
            return;
        }
    }

    public: 
        Form() : m_gene() {  }
        Form(Gene gene) : m_gene(gene)  {}
        Gene getGene() const {
            return m_gene;
        }
        Form(Form& f) {
            m_gene = f.m_gene;
            m_gene.mutation();
        }
    
        void draw(int x1, int y1, int deepRec = 5) {
            if (deepRec < 1) return;
            int NshiftX;
            int NshiftY;
            shiftChoicer(NshiftX, NshiftY, deepRec);
            --deepRec;
            drawLine(x1, y1, x1 + NshiftX, y1 + NshiftY);
            draw(x1 + NshiftX, y1 + NshiftY, deepRec);
            drawLine(x1, y1, x1 - NshiftX, y1 + NshiftY);
            draw(x1 - NshiftX, y1 + NshiftY, deepRec);
        }
};




int main()
{
    mt_rand.seed(time(0));
    const size_t child_count = 4;
  
    Form p;
    Form c[child_count];
    for (int i = 0; i < child_count; i++)
    {
        c[i] = Form(p);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
        {
            p = c[0];
            for (int i = 0; i < child_count; i++) {
                c[i] = Form(p);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
        {
            p = c[1];
            for (int i = 0; i < child_count; i++) {
                c[i] = Form(p);
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
        {
            p = c[2];
            for (int i = 0; i < child_count; i++) {
                c[i] = Form(p);
            }

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
        {
            p = c[3];
            for (int i = 0; i < child_count; i++) {
                c[i] = Form(p);
            }
        }


        window.clear();
        p.draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

        c[0].draw(SCREEN_WIDTH / 4 , SCREEN_HEIGHT * 5/6 );
        c[1].draw(SCREEN_WIDTH * 5 / 7, SCREEN_HEIGHT * 5/6);
        c[2].draw(SCREEN_WIDTH  / 4, SCREEN_HEIGHT/6);
        c[3].draw(SCREEN_WIDTH * 5 / 7, SCREEN_HEIGHT/6);
        window.display();
        Sleep(150);
    }
            
    return 0;
}