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

    virtual void onMouseMove(sf::Event& event) {};
    virtual void onMouseEnter() {};
    virtual void onMouseLeave() {};
    virtual void onMouseClick() {};
    virtual void onMouseUp(sf::Event& event) {};

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

    bool click(sf::Event& event)
    {
        bool affected = false;
        for (auto& p : m_observers)
        {
            if (isIntersects(event, p->getMouseCatchOffset(),
                    p->getMouseCatchSize()))
            {
                affected = true;
                p->onMouseClick();
                break;
            }
        }
        return affected;
    }

    bool clickRelease(sf::Event& event)
    {
        bool affected = false;
        for (auto& p : m_observers)
        {
            if (isIntersects(event, p->getMouseCatchOffset(),
                    p->getMouseCatchSize()))
            {
                affected = true;
                p->onMouseUp(event);
                break;
            }
        }
        return affected;
    }

    bool fire(sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::MouseMoved:
            return mouseMove(event);
            break;
        case sf::Event::MouseButtonPressed:
            return click(event);
            break;
        case sf::Event::MouseButtonReleased:
            return clickRelease(event);
            break;
        }
        return false;
    }

    void lostFocus()
    {
        for (auto& p : m_observers)
        {
            if (p->m_hover == true)
            {
                p->m_hover = false;
                p->onMouseLeave();
                p->m_mouseWithin = false;
            }
        }
    }

    bool mouseMove(sf::Event& event)
    {
        bool affected = false;
        bool top = false;
        for (auto& p : m_observers)
        {
            if (isIntersects(event, p->getMouseCatchOffset(),
                    p->getMouseCatchSize()))
            {
                affected = true;

                if (!top) // trigger
                {
                    top = true;

                    if (p->m_mouseWithin == false)
                    {
                        p->m_mouseWithin = true;
                        p->onMouseEnter();
                    }

                    p->m_hover = true;
                    p->onMouseMove(event);
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

        return affected;
    }

    void erase()
    {
        m_observers.clear();
    }

    std::vector<MouseEventObserver *> m_observers;

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
};

#endif // MOUSE_EVENT_HPP
