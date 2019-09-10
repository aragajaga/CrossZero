#ifndef MOUSE_EVENT_HPP
#define MOUSE_EVENT_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MouseEventObserver {
friend class MouseEventSubject;
public:
    MouseEventObserver()
    : m_hover(false),
      m_mouseWithin(false) {};
      
    virtual void onMouseMove() {};
    virtual void onMouseEnter() {};
    virtual void onMouseLeave() {};
    virtual void onMouseClick() {};
    virtual void onMouseUp() {};
    
    void setMouseCatchOffset(sf::Vector2f newCatch)
    {
        m_mouseCatchOffset = newCatch;
    }
    
    void setMouseCatchSize(sf::Vector2f newCatchSize)
    {
        m_mouseCatchSize = newCatchSize;
    }
    
    sf::Vector2f getMouseCatchOffset() const
    {
        return m_mouseCatchOffset;
    }
    
    sf::Vector2f getMouseCatchSize() const
    {
        return m_mouseCatchSize;
    }
protected:
    bool m_hover;
    bool m_mouseWithin;
private:
    sf::Vector2f m_mouseCatchOffset;
    sf::Vector2f m_mouseCatchSize;
};

class MouseEventSubject {
public:   
    void subscribe(MouseEventObserver* obs)
    {
        m_observers.insert(m_observers.begin(), obs);
    }
    
    void click(sf::Event& event)
    {
        for (auto& p : m_observers)
        {
            if (isIntersects(event, p->getMouseCatchOffset(),
                    p->getMouseCatchSize()))
            {
                p->onMouseClick();
                break;
            }
        }
    }
    
    void clickRelease(sf::Event& event)
    {
        for (auto& p : m_observers)
        {
            if (isIntersects(event, p->getMouseCatchOffset(),
                    p->getMouseCatchSize()))
            {
                p->onMouseUp();
                break;
            }
        }
    }
    
    void mouseMove(sf::Event& event)
    {
        bool top = false;
        for (auto& p : m_observers)
        {
            if (isIntersects(event, p->getMouseCatchOffset(),
                    p->getMouseCatchSize()))
            {
                if (!top) // trigger
                {
                    top = true;
                    
                    if (p->m_mouseWithin == false)
                    {
                        p->m_mouseWithin = true;
                        p->onMouseEnter();
                    }
                    
                    p->m_hover = true;
                    p->onMouseMove();
                // TODO
                } else if (p->m_hover == true) {
                    p->m_hover = false;
                    p->onMouseLeave();
                    p->m_mouseWithin = false;
                }
            } else if (p->m_hover == true) {
                p->m_hover = false;
                p->onMouseLeave();
                p->m_mouseWithin = false;
            }
        }
    }
    
    void erase()
    {
        m_observers.clear();
    }
    
private:
    static bool isIntersects(float x, float y, float cx1, float cy1, float cx2,
            float cy2)
    {
        return x >= cx1 && y >= cy1 && x < cx2 && y < cy2;
    }

    static bool isIntersects(sf::Event& event, sf::Vector2f mouseCatch,
            sf::Vector2f mouseCatchSize)
    {
        switch (event.type)
        {
        case sf::Event::EventType::MouseMoved:
            return isIntersects(
                    event.mouseMove.x,      event.mouseMove.y,
                    mouseCatch.x,           mouseCatch.y,
                    mouseCatch.x+mouseCatchSize.x,
                    mouseCatch.y+mouseCatchSize.y);
            break;
        
        case sf::Event::EventType::MouseButtonReleased:
        case sf::Event::EventType::MouseButtonPressed:
            return isIntersects(
                    event.mouseButton.x,    event.mouseButton.y,
                    mouseCatch.x,           mouseCatch.y,
                    mouseCatch.x+mouseCatchSize.x,
                    mouseCatch.y+mouseCatchSize.y);
            break;

        default:
            throw "TODO";
            break;
        }
    }
    
    std::vector<MouseEventObserver *> m_observers;
};

#endif // MOUSE_EVENT_HPP
