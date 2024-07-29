#ifndef PE_CORE_PARTICULE_EVENT_HPP
#define PE_CORE_PARTICULE_EVENT_HPP

#include <ParticuleEssential/Types/List.hpp>

namespace Particule::Core
{

    class IEvent
    {
    public:
        virtual ~IEvent() {}
        virtual void Invoke() = 0;
    };


    // Classe template pour stocker et appeler une méthode membre avec un argument
    template<typename T, typename Arg>
    class ParticuleEvent: public IEvent
    {
    public:
        typedef void (T::*Method)(Arg);

        ParticuleEvent(T* instance, Method method, Arg arg)
            : instance(instance), method(method), arg(arg) {}

        void Invoke() override {
            if (instance && method) {
                (instance->*method)(arg);
            }
        }

    private:
        T* instance;
        Method method;
        Arg arg;
    };

    template<typename T>
    class ParticuleEvent<T, void>: public IEvent
    {
    public:
        typedef void (T::*Method)();

        ParticuleEvent(T* instance, Method method)
            : instance(instance), method(method) {}

        void Invoke() override {
            if (instance && method) {
                (instance->*method)();
            }
        }

    private:
        T* instance;
        Method method;
    };

    class ParticuleEvents
    {
    private:
        List<IEvent*> events;
    public:
        ParticuleEvents() {}

        ~ParticuleEvents() {
            for (ListNode<IEvent *> *cur=nullptr; this->events.ForEach(&cur);)
            {
                delete cur->data;
            }
        }

        void AddEvent(IEvent *event) {
            events.Append(event);
        }

        void Invoke() {
            for (ListNode<IEvent *> *cur=nullptr; this->events.ForEach(&cur);)
            {
                cur->data->Invoke();
            }
        }
    };
}

/*
// Exemple de classes pour illustrer l'utilisation de ParticuleEvent
class Example {
public:
    void PrintMessage(const char* message) {
        printf("%s\n", message);
    }

    void NoArgMethod() {
        printf("No argument method\n");
    }
};

int main() {
    Example example;

    // Création d'un ParticuleEvent avec une méthode de la classe Example
    ParticuleEvent<Example, const char*> event(&example, &Example::PrintMessage, "Hello, World!");
    // Invoquer la méthode stockée
    event.Invoke();

    // Création d'un ParticuleEvent avec une méthode de la classe Example sans argument
    ParticuleEvent<Example, void> event2(&example, &Example::NoArgMethod);
    // Invoquer la méthode stockée
    event2.Invoke();

    ParticuleEvents events;
    events.AddEvent(new ParticuleEvent<Example, const char*>(&example, &Example::PrintMessage, "Test Invoke"));
    events.AddEvent(new ParticuleEvent<Example, void>(&example, &Example::NoArgMethod));
    events.Invoke();

    return 0;
}
*/

#endif // PE_CORE_PARTICULE_EVENT_HPP